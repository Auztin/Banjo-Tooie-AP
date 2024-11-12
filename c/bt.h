#ifndef BT_H
#define BT_H

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
#include "bt/fn_injected.h"

#define BT_IN_GAME (bt_save_slot != 0xFF && bt_current_map != 0x0158)
#define BT_FPS (*(u8*)0x8007913F)

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
