#ifndef AP_MENU_H
#define AP_MENU_H

#include "util.h"
#include "bt.h"

enum {
  AP_MENU_NONE,
  AP_MENU_TOPAUSE,
  AP_MENU_TOTOTALS,
  AP_MENU_WAITTOTALS,
  AP_MENU_UNPAUSE,
  AP_MENU_MAIN,
  AP_MENU_RECEIVED,
  AP_MENU_RECEIVED_MOVES_BK,
  AP_MENU_RECEIVED_MOVES_BT,
  AP_MENU_RECEIVED_MUMBO_HUMBA,
  AP_MENU_RECEIVED_TRAIN_STATIONS,
  AP_MENU_RECEIVED_WORLDS,
  AP_MENU_ENTRANCES,
  AP_MENU_OPTIONS,
};

enum {
  AP_MENU_STATE_NONE,
  AP_MENU_STATE_INIT,
  AP_MENU_STATE_PAGE_SWITCH,
  AP_MENU_STATE_SHOW,
  AP_MENU_STATE_CLEAR,
};

typedef struct {
  u8 id;
  u8 state;
  u8 last_id;
  u8 last_zb;
  u8 last_y;
  u8 progress;
  u8 column;
  u8 columns;
  u8 selected;
  u8 delay_zb;
  u8 delay_select;
  u8 page;
  u8 page_max;
  char* title;
  s32 title_y;
  bt_zoombox_t* zoombox[30];
} ap_menu_t;
extern ap_menu_t ap_menu;

void ap_menu_draw(bt_draw_ctx_t* draw_ctx);
void ap_menu_update();

#endif // AP_MENU_H
