#ifndef BT_H
#define BT_H

typedef struct {

} bt_draw_ctx_t;

typedef struct {
  u16 red;
  u16 green;
  u16 blue;
} bt_color_t;

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

#endif // BT_H
