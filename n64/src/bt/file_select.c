#include "file_select.h"
#include "audio.h"
#include "controllers.h"
#include "objects.h"
#include "zoombox.h"
#include <ap/ap.h>
#include <ap/states.h>
#include <save.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>

#define LOADER 0x80085BB0
#define UPDATE 0x1424
#define CURSOR 0x0828
#define MOVE_HORIZONTAL 0x1938
#define KAZOOIE_CHECK_TEXT 0x2CE8
#define KAZOOIE_SET_TEXT 0x2D0C
#define BANJO_UPDATE 0x2848
#define BANJO_SET_TEXT 0x4494

typedef struct {
	u8 _unk_000_018[0x018];
	u32 operation_state;
	u32 selection1;
	u32 selection2;
	u8 _unk_024_065[0x041];
	u8 _unk_065_0_2 : 3;
	u8 block_selection : 1;
	u8 _unk_065_4_7 : 4;
	u8 _unk_066_072[0x00C];
	u8 cursor_state;
	u8 _unk_073_079[0x006];
	u8 selected : 4;
} bt_file_select_t;

typedef struct {
	u8 _unk_000_02B[0x02B];
	u32 selected;
} bt_file_select_banjo_t;

struct {
	bool refresh;
} file_select;

void bt_file_select_update(bt_file_select_t *ctx);
void file_select_update(bt_file_select_t *ctx) {
	static u8 last_state;
	static u8 last_client_state;
	u32 singleton = objects_singleton(LOADER);
	if (
		ctx->selected < 3
		&& (ap.state == APS_CONNECTED || ap.state == APS_DISCONNECTED)
		&& (ap.client_state == APS_CONNECTED || ap.client_state == APS_DISCONNECTED)
		&& (ap.state != last_state || ap.client_state != last_client_state)
	) {
		file_select.refresh = true;
		ctx->selected++;
		objects_jump = singleton + MOVE_HORIZONTAL;
		objects_jump_now(ctx, -1);
	}
	last_state = ap.state;
	last_client_state = ap.client_state;
	objects_jump = singleton + UPDATE + 8;
	bt_file_select_update(ctx);
}

u8 bt_file_select_cursor(bt_file_select_t *ctx, u8 operation, u8 selected);
u8 file_select_cursor(bt_file_select_t *ctx, u8 operation, u8 selected) {
	switch (operation) {
	case 0x07: // select
		switch (selected) {
		case 0:
		case 1:
		case 2:
			switch (ctx->cursor_state) {
			case 0x04: // normal
				char *client_seed = ap.seed;
				u32 *game_seed = save.data.custom[selected].seed;
				bool client_blank = client_seed[0] == 0 && !memcmp(client_seed, client_seed + 1, 19);
				bool game_blank = game_seed[0] == 0 && !memcmp(game_seed, game_seed + 1, 19);
				bool match = !memcmp(client_seed, game_seed, 20);
				if (
					(ap.client_state != APS_DISCONNECTED && (client_blank || (!game_blank && !match)))
					|| (ap.client_state == APS_DISCONNECTED && (game_blank || selected != save.data.last_online_slot))
				) {
					if (!(bt_controllers[0].held.l && bt_controllers[0].held.r)) {
						bt_play_sound(BT_SOUND_WRONG, -1, 1, -1);
						file_select.refresh = true;
						return 1;
					}
				}
				save.data.last_online_slot = selected;
				break;
			case 0x0C: // copy
				if (ctx->operation_state == 2) {
					if (ctx->block_selection) break;
					// copy custom save data
					memcpy(&save.data.custom[ctx->selection2], &save.data.custom[ctx->selection1], sizeof(save_custom_data_t));
				}
				break;
			case 0x10: // delete
				if (ctx->operation_state == 1) {
					if (ctx->block_selection) break;
					// delete custom save data
					memset(&save.data.custom[ctx->selection1], 0, sizeof(save_custom_data_t));
				}
				break;
			}
			break;
		}
		break;
	}
	objects_jump = objects_singleton(LOADER) + CURSOR + 8;
	return bt_file_select_cursor(ctx, operation, selected);
}

void bt_file_select_banjo_update(bt_file_select_banjo_t *instance);
void file_select_banjo_update(bt_file_select_banjo_t *instance) {
	if (file_select.refresh) {
		file_select.refresh = false;
		instance->selected--;
	}
	objects_jump = objects_singleton(LOADER) + BANJO_UPDATE + 8;
	bt_file_select_banjo_update(instance);
}

void file_select_kazooie_set_text(bt_zoombox_t *zb, char *text) {
	if (!strcmp(text, "PRESS \x87 TO PLAY THE GAME.")) {
		char *lines[2];
		if (ap.client_state == APS_CONNECTED) lines[0] = "CLIENT: CONNECTED";
		else lines[0] = "CLIENT: DISCONNECTED";
		if (ap.state == APS_CONNECTED) lines[1] = "AP: CONNECTED";
		else lines[1] = "AP: DISCONNECTED";
		bt_zoombox_append_lines(zb, 2, lines);
		return;
	}
	bt_zoombox_append_text(zb, text);
}

void _file_select_banjo_set_text();
void bt_file_select_banjo_set_text(char *text, u16 dialog_id, u8 id, u32 _unk_A3, u32 *slot);
void file_select_banjo_set_text(char *text, u16 dialog_id, u8 id, u32 _unk_A3, u32 *slot) {
	if (dialog_id == 0x18F3) {
		switch (id) {
		case 0: // Empty Game
			memset(&save.data.custom[*slot - 1], 0, sizeof(save_custom_data_t));
			strcpy(text, "NEW GAME. ");
			if (ap.state == APS_CONNECTED && ap.client_state == APS_CONNECTED) strcat(text, "PRESS \x87 TO PLAY THE GAME.");
			else if (ap.state == APS_CONNECTED) strcat(text, "CONNECT CLIENT TO THE ROOM.");
			else strcat(text, "RUN CLIENT AND CONNECTOR.");
			break;
		case 1: { // Game Time
			strcpy(text, "JIGGIES: ");
			char str[3];
			u32 jiggies = save.data.custom[*slot - 1].items[API_JIGGY];
			if (jiggies > 999) jiggies = 999;
			itoa(jiggies, str, 10);
			strcat(text, str);
			strcat(text, ", TIME: ");
			break;
		}
		case 2: // Jiggies
		case 3: // Jiggy
			if (ap.client_state == APS_CONNECTED) {
				if (memcmp(ap.seed, save.data.custom[*slot - 1].seed, 20)) strcpy(text, "SAVE DOESN'T MATCH CLIENT");
				else strcpy(text, "SAVE MATCHES CLIENT");
			} else if (save.data.last_online_slot == *slot - 1) strcpy(text, "CAN BE PLAYED OFFLINE");
			else strcpy(text, "CONNECT CLIENT FIRST.");
			break;
		default: goto vanilla;
		}
		return;
	}
vanilla:
	objects_jump = objects_singleton(LOADER) + BANJO_SET_TEXT + 8;
	bt_file_select_banjo_set_text(text, dialog_id, id, _unk_A3, slot);
}

void file_select_init(bt_object_t *obj) {
	util_inject(UTIL_INJECT_JUMP, (u32)obj + UPDATE, (u32)file_select_update, 1);
	util_inject(UTIL_INJECT_JUMP, (u32)obj + CURSOR, (u32)file_select_cursor, 1);
	util_inject(UTIL_INJECT_RAW, (u32)obj + KAZOOIE_CHECK_TEXT, 0, 0);
	util_inject(UTIL_INJECT_FUNCTION, (u32)obj + KAZOOIE_SET_TEXT, (u32)file_select_kazooie_set_text, 0);
	util_inject(UTIL_INJECT_JUMP, (u32)obj + BANJO_UPDATE, (u32)file_select_banjo_update, 1);
	util_inject(UTIL_INJECT_JUMP, (u32)obj + BANJO_SET_TEXT, (u32)_file_select_banjo_set_text, 1);
}
