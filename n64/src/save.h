#pragma once

#include "n64/types.h"

#define SAVE_MAGIC 0x007001E0

typedef struct {
} save_custom_data_t;

typedef struct __attribute__ ((aligned (16))) {
	u32 magic_start;
	u32 version;
	u32 eeprom[128];
	save_custom_data_t custom[3];
	u32 magic_end;
} save_data_t;

typedef struct {
	save_data_t data;
	bool dirty;
} save_t;
extern save_t save;
#define ap_save (save.data.custom[0])

void save_init_random();
void save_init();
void save_sram_write();
u32 save_eeprom_read(u32 _unused, u32 offset, u32 *ramAddr);
u32 save_eeprom_write(u32 _unused, u32 offset, u32 *ramAddr);
