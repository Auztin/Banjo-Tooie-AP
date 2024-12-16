#ifndef AP_H
#define AP_H

#include "util.h"
#include "bt.h"

typedef bool (*ap_fnt_trap)(bool checking);

typedef struct {
  u8 load_file : 1;
  u8 death_link : 1;
  u8 death_link_queued : 1;
  u8 smooth_banjo : 1;
  u8 zoombox_ready : 1;
  u8 fake_transform : 1;
  u8 is_internal_message : 1;
  u8 last_icon;
  u8 internal_icon;
  u8 zb_icon;
  u8 message_lines;
  bt_zoombox_t* zoombox;
  char* messages[5];
  char message[508];
  char internal_message[508];
  u8 items[AP_ITEM_MAX];
  ap_fnt_trap fn_trap;
  s32 trap_timer;
} ap_t;
extern ap_t ap;
extern u16 AP_ICON[32][32];

u32 ap_get_health(u32 character);
void ap_increase_health(u32 character, s32 amount);
u32 ap_ground_info(u32 character);
void ap_draw_hud(bt_draw_ctx_t* draw_ctx);
void ap_update();
void ap_check();
void ap_new_file();
void ap_load_file();

#endif // AP_H
