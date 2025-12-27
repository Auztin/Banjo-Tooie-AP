#include "main.h"
#include "save.h"
#include "util.h"
#include <ap/ap.h>
#include <ap/commands.h>
#include <ap/states.h>
#include <ap/version.h>
#include <string.h>

ap_t ap = {0};
extern ap_packet_t *AP_INPUT_PTR;
extern ap_packet_t *AP_OUTPUT_PTR;

void ap_init() {
	AP_INPUT_PTR = &ap.input;
	AP_OUTPUT_PTR = &ap.output;
}

void ap_input() {
	ap.ping.timer += main.delta;
	if (ap.ping.timer >= 1000) ap.ping.timer = 0;
	int state = ap.state & ~APS_PINGED;
	if (state != APS_CONNECTED) ap.client_state = APS_DISCONNECTED;
	switch (state) {
	case APS_DISCONNECTED:
		switch (ap.input.cmd) {
		case APC_NONE:
			if (!ap.ping.timer) {
				ap.output.cmd = APC_HANDSHAKE;
				ap.output.handshake.version = AP_VERSION.as_int;
				memcpy(ap.output.handshake.msg, "HELO", 4);
				ap.output.size = 10;
			}
			break;
		case APC_HANDSHAKE:
			if (!memcmp(ap.input.handshake.msg, "'LO!", 4) && ap.input.handshake.version == AP_VERSION.as_int) {
				ap.state = APS_CONNECTING;
				ap.output.cmd = APC_PING;
				ap.output.size = 2;
			}
			break;
		}
		break;
	case APS_CONNECTING:
		if (!ap.ping.timer) ap.state = APS_DISCONNECTED;
		switch (ap.input.cmd) {
		case APC_NONE:
			break;
		case APC_PONG:
			ap.state = APS_CONNECTED;
			break;
		default:
			ap.state = APS_DISCONNECTED;
		}
		break;
	case APS_CONNECTED:
		switch (ap.input.cmd) {
		case APC_NONE:
			goto skip_ping_reset;
		case APC_PING:
			ap.ping.reply = true;
			break;
		case APC_PONG:
			ap.ping.timer = 1;
			break;
		case APC_STATE:
			ap.client_state = ap.input.client.state;
			switch (ap.client_state) {
			case APS_DISCONNECTED:
			case APS_CONNECTING:
				ap.team = 0;
				ap.slot = 0;
				memset(&ap.seed, 0, sizeof(ap.seed));
				memset(&ap.out.locations, 0, sizeof(ap.out.locations));
				memset(&ap.in.locations, 0, sizeof(ap.in.locations));
				memset(&ap.in.items, 0, sizeof(ap.in.items));
				break;
			case APS_CONNECTED:
				save_init_random();
				break;
			default: break;
			}
			break;
		case APC_INFO:
			ap.team = ap.input.info.team;
			ap.slot = ap.input.info.slot;
			memcpy(ap.seed, ap.input.info.seed, sizeof(ap.seed));
			break;
		case APC_OPTIONS:
			for (u32 i = 0; i < (ap.input.size - 2) / sizeof(*ap.input.options); i++) {
				ap_packet_option_t *option = &ap.input.options[i];
				ap_options_set(option->name, option->value);
			}
			break;
		case APC_LOCATIONS:
			for (u32 i = 0; i < (ap.input.size - 2) / sizeof(*ap.input.locations); i++) {
				u32 location = ap.input.locations[i];
				if (location >= APL_MAX) break;
				set_bit(ap.in.locations.raw, location);
			}
			break;
		case APC_ITEMS:
			for (u32 i = 0; i < (ap.input.size - 2) / sizeof(*ap.input.items); i++) {
				u32 item = ap.input.items[i];
				if (item >= API_MAX) break;
				ap.in.items[item]++;
			}
			break;
		case APC_MESSAGE:
			if (ap.input.message[0]) {
				strcpy(ap.in.message, ap.input.message);
			} else ap.out.message = true;
			break;
		case APC_DEATH_LINK:
			ap.in.deathlink++;
			break;
		default:
			ap.state = APS_DISCONNECTED;
			break;
		}
		ap.state &= ~APS_PINGED;
	skip_ping_reset:
		break;
	}
	ap.input.cmd = APC_NONE;
}

void ap_output() {
	switch (ap.state) {
	case APS_CONNECTED:
		if (!ap.ping.timer) {
			ap.output.data[0] = 0;
			ap.output.cmd = APC_PING;
			ap.output.size = 2;
			ap.state |= APS_PINGED;
			return;
		}
		break;
	case APS_CONNECTED | APS_PINGED:
		if (!ap.ping.timer) {
			ap.state = APS_DISCONNECTED;
			return;
		}
		break;
	default:
		return;
	}
	if (ap.output.cmd != APC_NONE) return;
	int ping_timer = ap.ping.timer;
	ap.ping.timer = 0;
	if (ap.ping.reply) {
		ap.output.data[0] = 0;
		ap.output.cmd = APC_PONG;
		ap.output.size = 2;
		ap.ping.reply = false;
		return;
	}
	if (ap.client_state != APS_CONNECTED) goto no_output;
	u32 offset = 0;
	for (int i = 0; i < APL_MAX_BYTES; i++) {
		u8 location = ap_save.locations.raw[i];
		u8 sent_location = ap.out.locations.raw[i];
		if (location == sent_location) continue;
		u32 base = i * 8;
		for (int b = 0; b < 8; b++) {
			u32 id = base + b;
			if (!get_bit(ap_save.locations.raw, id) || set_bit(ap.out.locations.raw, id)) continue;
			ap.output.locations[offset++] = id;
			if (offset >= countof(ap.output.locations)) goto locations;
		}
	}
locations:
	if (offset) {
		ap.output.cmd = APC_LOCATIONS;
		ap.output.size = 2 + offset * sizeof(*ap.output.locations);
		return;
	}
	if (ap.out.deathlink) {
		ap.out.deathlink = 0;
		ap.output.cmd = APC_DEATH_LINK;
		ap.output.size = 2;
		return;
	}
	if (ap.out.taglink) {
		ap.out.taglink = 0;
		ap.output.cmd = APC_TAG_LINK;
		ap.output.size = 2;
		return;
	}
	if (ap.out.message && !ap.in.message[0]) {
		ap.output.cmd = APC_MESSAGE;
		ap.output.size = 2;
		return;
	}
no_output:
	ap.ping.timer = ping_timer;
}
