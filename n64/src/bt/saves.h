#pragma once

#include "flags_save.h"
#include "flags_temp.h"

typedef struct {
	bt_save_flags_t *flags;
	bt_save_temp_flags_t *temp_flags;
} bt_save_t;

#define bt_save_slot (*(u8 *)0x8012B3F1) // will be 0xFF during puzzle challenges, and when not in game. reflects hovered save slot at file select
#define bt_save ((bt_save_t *)0x8012C770)
#define bt_flags (*bt_save->flags)
#define bt_temp_flags (*bt_save->temp_flags)

typedef enum {
	BT_SAVES_TOTALS_JINJOS,
	BT_SAVES_TOTALS_JIGGIES,
	BT_SAVES_TOTALS_HONEYCOMBS,
	BT_SAVES_TOTALS_GLOWBOS,
	BT_SAVES_TOTALS_PAGES,
	BT_SAVES_TOTALS_SACRED_STATUES,
	BT_SAVES_TOTALS_NOTES,
	BT_SAVES_TOTALS_DOUBLOONS,
	BT_SAVES_TOTALS_BIG_TOP_TICKETS,
	BT_SAVES_TOTALS_MAX,
} bt_saves_totals_type_t;

u32 bt_saves_load(u32);
