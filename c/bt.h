#ifndef BT_H
#define BT_H

typedef struct {

} bt_draw_ctx_t;

typedef struct {
  u16 red;
  u16 green;
  u16 blue;
} bt_color_t;

typedef struct {
  float x;
  float y;
  float z;
} bt_xyz_t;

typedef struct {
  s16 x;
  s16 y;
  s16 z;
} bt_s16_xyz_t;

typedef struct {
  s32 x;
  s32 y;
  s32 z;
} bt_s32_xyz_t;

#include "util.h"
#include "bt/flags.h"
#include "bt/items.h"
#include "bt/objects.h"
#include "bt/controllers.h"
#include "bt/ui_numbers.h"
#include "bt/dialog.h"
#include "bt/player_chars.h"
#include "bt/maps.h"
#include "bt/cutscenes.h"
#include "bt/misc_functions.h"
#include "bt/zoombox.h"
#include "bt/text.h"

#define BT_IN_GAME (bt_save_slot != 0xFF && bt_current_map != BT_MAP_FILE_SELECT)
#define BT_FPS    (*(u8 *)0x8007913F)
#define BT_RANDOM (*(u32*)0x8012C7F0)

enum {
  BT_JINJO_WHITE,
  BT_JINJO_ORANGE,
  BT_JINJO_YELLOW,
  BT_JINJO_BROWN,
  BT_JINJO_GREEN,
  BT_JINJO_RED,
  BT_JINJO_BLUE,
  BT_JINJO_PURPLE,
  BT_JINJO_BLACK,
};

typedef struct {
  u8 pause_state;
  u8 current_menu;
  u8 unpause;
  u8 load_state;
  u32 _unknown1[11];
  u16 menu_state;
  u16 _unknown2;
  u32 _unknown3[38];
  float progress1;
  float progress2;
  float progress3;
} bt_pause_ctx_t;
#define bt_pause_ctx (*(bt_pause_ctx_t*)(*(u32*)0x80128AF0))

typedef struct {
  u16 icon;
  u8 string_index;
  u8 _unknown[3];
} bt_pause_main_entry_t;

#endif // BT_H
