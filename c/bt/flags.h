#ifndef BT_FLAGS_H
#define BT_FLAGS_H

#include <bt/save_flags.h>
#include "temp_flags.h"

typedef struct {
  bt_save_flags_t* flags;
  bt_save_temp_flags_t* temp_flags;
} bt_save_t;

#define bt_save_slot (*(u8*)0x8012B3F1) // will be 0xFF during puzzle challenges, and when not in game. reflects hovered save slot at file select
#define bt_save ((bt_save_t*)0x8012C770)
#define bt_flags (*bt_save->flags)
#define bt_temp_flags (*bt_save->temp_flags)

#endif // BT_FLAGS_H
