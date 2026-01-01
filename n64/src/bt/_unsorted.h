#include "saves.h"
#include "scenes.h"
#include <n64/types.h>

typedef enum {
	BT_JINJO_WHITE,
	BT_JINJO_ORANGE,
	BT_JINJO_YELLOW,
	BT_JINJO_BROWN,
	BT_JINJO_GREEN,
	BT_JINJO_RED,
	BT_JINJO_BLUE,
	BT_JINJO_PURPLE,
	BT_JINJO_BLACK,
	BT_JINJO_MAX,
} bt_jinjo_t;

u32 bt_random();
u32 bt_init();
u32 bt_loop();

#define BT_TITLE_SCREEN (*(u8 *)0x8012C78D) // set to 0x40 to allow skipping
#define BT_IN_GAME (bt_save_slot != 0xFF && bt_current_map != BT_MAP_FILE_SELECT)
