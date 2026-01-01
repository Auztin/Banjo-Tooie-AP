#include "main.h"
#include "save.h"
#include "usb.h"
#include "util.h"
#include <ap/ap.h>
#include <bt/game.h>
#include <n64/dma.h>
#include <n64/sys.h>

main_t main = {0};

void main_init() {
	main.is_emulator = io_read(0xA4100010) == 0 ? 1 : 0;
	if (!main.is_emulator) usb_init();
	ap_init();
	save_init();
}

void main_game_init() {
	BT_TITLE_SCREEN = 0x40;
}

void main_loop() {
	bt_loop();
	u32 c0_count = C0_COUNT();
	main.delta = (c0_count - main.last_c0_count) / TICKS_PER_MILLISECOND;
	main.last_c0_count = c0_count;
	if (main.delta >= 250) return;
	save_sram_write();
	if (main.is_emulator) {
		ap_input();
		ap_output();
	} else usb_check();
}

void main_goal_completed() {
	if (!set_bit(ap_save.locations.raw, APL_COMPLETION_CONDITION)) {}
}

// void main_menu_update() {
//   char* text_client = "CLIENT DISCONNECTED";
//   char* text_ap = "AP DISCONNECTED";
//   char version[10];
//   char minor[3];
//   char build[3];
//   itoa(AP_VERSION.major, version, 10);
//   itoa(AP_VERSION.minor, minor, 10);
//   itoa(AP_VERSION.build, build, 10);
//   strcat(version, ".");
//   strcat(version, minor);
//   strcat(version, ".");
//   strcat(version, build);
//   if ((ap.state & ~AP_STATE_PINGED) == AP_STATE_CONNECTED) text_client = "CLIENT CONNECTED";
//   if (ap.ready) text_ap = "AP CONNECTED";
//   sf_fn_main_menu_update();
//   sf_fn_gfx_setup(&sf_gfx, 0x53);
//   sf_fn_gfx_color(0xFF, 0xFF, 0, 0xFF);
//   sf_fn_gfx_draw_text(20, 20, 1, 1, text_client);
//   sf_fn_gfx_draw_text(20, 30, 1, 1, text_ap);
//   sf_fn_gfx_draw_text(SF_GFX_WIDTH-50, 210, 1, 1, version);
// }
