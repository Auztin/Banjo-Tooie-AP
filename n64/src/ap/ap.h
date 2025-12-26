#pragma once

#include "n64/types.h"
#include "options.h"
#include "locations.h"
#include "items.h"

#define PACKET_SIZE (512-4)
extern u32 AP_ASSETS;
extern u32 ASSET_AP_LOGO;

typedef struct {
	u32 name;
	s32 value;
} ap_packet_option_t;

typedef struct __attribute__ ((aligned (16))) {
	u16 size;
	u16 cmd;
	union {
		struct {
			char header[4];
			char data[PACKET_SIZE-4];
		};
		struct {
			u32 version;
			char msg[4];
		} handshake;
		struct {
			u8 state;
		} client;
		struct {
			u16 team;
			u16 slot;
			char seed[20];
		} info;
		ap_packet_option_t options[PACKET_SIZE/sizeof(ap_packet_option_t)];
		u32 locations[PACKET_SIZE/4];
		u32 items[PACKET_SIZE/4];
		char message[PACKET_SIZE];
	};
} ap_packet_t;

typedef struct {
	ap_packet_t input;
	ap_packet_t output;
	ap_options_t options;
	u16 team;
	u16 slot;
	char seed[20];
	u8 state;
	u8 client_state;
	struct {
		s16 reply : 1;
		s16 timer : 15;
	} ping;
	struct {
		u8 deathlink;
		char message[PACKET_SIZE];
		u8 locations[APL_MAX_BYTES];
		u32 items[API_MAX];
	} in;
	struct {
		u8 message : 1;
		u8 deathlink;
		u8 locations[APL_MAX_BYTES];
	} out;
	u8 locations[APL_MAX_BYTES];
	u32 items[API_MAX];
} ap_t;
extern ap_t ap;

void ap_init();
void ap_input();
void ap_output();
