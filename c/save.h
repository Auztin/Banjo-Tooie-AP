#ifndef SAVE_H
#define SAVE_H

#include "util.h"
#include "bt.h"

#define SAVE_MAGIC 0x84070013

typedef struct Save_Data_s {
  u32 magic;
  u32 eeprom[512];
} Save_Data_t;
extern Save_Data_t save_data;
extern u8 save_dirty;

void save_init();
void save_sram_write();
u32 save_eeprom_read(u32 _unused, u32 offset, u32 *ramAddr);
u32 save_eeprom_write(u32 _unused, u32 offset, u32 *ramAddr);

#endif // SAVE_H
