#include "main.h"
#include "save.h"
#include "util.h"
#include <bt/data.h>
#include <bt/gfx.h>
#include <bt/game.h>
#include <bt/objects.h>
#include <bt/saves.h>
#include <bt/scenes.h>
#include <n64/types.h>

u32 inject_init() {
	u32 ret = bt_init();

	// replace game's load scene function
	util_inject(UTIL_INJECT_JUMP, 0x800A72A4, (u32)scenes_load, 1);

	// replace game's load save function
	util_inject(UTIL_INJECT_FUNCTION, 0x800A731C, (u32)saves_load, 0);

	/*
		the game reads most of a section of memory (0x8001E840 - 0x800D2014) during gameplay to verify that nothing has been modified
		setting this convinces the game that it has already successfully verified integrity
		without this, and with some of the following injects, the game will simply hang after performing the check (a minute or so while in game)
	*/
	(*(vu8 *)0x8007E9B3) = 0x08;

	// replace game's object init function
	util_inject(UTIL_INJECT_FUNCTION, 0x80081F1C, (u32)objects_init, 0);

	// replace game's totals function
	util_inject(UTIL_INJECT_JUMP, 0x800D035C, (u32)saves_totals, 1);

	// replace game's jinjo totals function
	util_inject(UTIL_INJECT_JUMP, 0x800D1338, (u32)saves_jinjo_family_count, 1);

	// replace game's load data function
	util_inject(UTIL_INJECT_JUMP, 0x800D5B34, (u32)data_load, 1);

	// replace game's get data function
	util_inject(UTIL_INJECT_JUMP, 0x800D674C, (u32)data_get, 1);

	// replace game's draw objects function
	util_inject(UTIL_INJECT_JUMP, 0x800EB51C, (u32)gfx_draw_objects, 1);

	// replace game's draw hud function
	util_inject(UTIL_INJECT_JUMP, 0x800FA508, (u32)gfx_draw_hud, 1);

	// replace game's spawn prop function
	util_inject(UTIL_INJECT_JUMP, 0x80108C90, (u32)objects_spawn, 1);

	// replace game's exit check function
	util_inject(UTIL_INJECT_FUNCTION, 0x800D5328, (u32)scenes_check_exit, 0);

	main_game_init();
	return ret;
}

void inject_hooks() {
	main_init();

	// replace game's init function
	util_inject(UTIL_INJECT_FUNCTION, 0x800124F4, (u32)inject_init, 0);

	// replace game's loop function
	util_inject(UTIL_INJECT_FUNCTION, 0x800124FC, (u32)main_loop, 0);

	// convince the game that only eeprom16k is available (we're actually using sram)
	util_inject(UTIL_INJECT_RETVALUE, 0x800166EC, 2, 0);

	// replace game's eeprom read function
	util_inject(UTIL_INJECT_JUMP, 0x80032B10, (u32)save_eeprom_read, 1);

	// replace game's eeprom write function
	util_inject(UTIL_INJECT_JUMP, 0x80032D60, (u32)save_eeprom_write, 1);
}
