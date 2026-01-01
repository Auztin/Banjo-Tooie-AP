#pragma once

#include "saves.h"
#include "scenes.h"
#include <n64/types.h>

#define BT_TITLE_SCREEN (*(u8 *)0x8012C78D) // set to 0x40 to allow skipping
#define BT_IN_GAME (bt_save_slot != 0xFF && bt_current_map != BT_MAP_FILE_SELECT)

u32 bt_random();
u32 bt_init();
u32 bt_loop();
