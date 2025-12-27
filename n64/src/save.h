#pragma once

#include <ap/ap.h>
#include <ap/items.h>
#include <ap/locations.h>
#include <ap/options.h>
#include <bt/saves.h>
#include <n64/types.h>

#define SAVE_MAGIC 0x00087000

typedef struct {
	u32 seed[5];
	ap_options_t options;
	ap_locations_t locations;
	u32 items[API_MAX];
	ap_exit_map_t exit_map[64];
} save_custom_data_t;

typedef struct __attribute__((aligned(16))) {
	u32 magic_start;
	u32 version;
	u32 eeprom[128];
	u8 signposts[61][150];
	u8 last_online_slot;
	save_custom_data_t custom[3];
	u32 magic_end;
} save_data_t;

typedef struct {
	save_data_t data;
	bool dirty;
} save_t;
extern save_t save;
#define ap_save (save.data.custom[bt_save_slot])

void save_init_random();
void save_init();
void save_sram_write();
u32 save_eeprom_read(u32 _unused, u32 offset, u32 *ramAddr);
u32 save_eeprom_write(u32 _unused, u32 offset, u32 *ramAddr);
