#include "save.h"
#include "dma.h"
#include "bt.h"

Save_Data_t save_data = {0,};
u8 save_dirty = 0;

void save_init() {
  const u32 size = sizeof(save_data);
  dma_read_raw_async(&save_data, 0x08000000, size);
  if (save_data.magic != SAVE_MAGIC) {
    for (int i = 0; i < size; i++) {
      u8 *addr = (u8*)((u32)&save_data + i);
      *addr = 0;
    }
    save_data.magic = SAVE_MAGIC;
    save_sram_write();
  }
}

void save_sram_write() {
  const u32 size = sizeof(save_data);
  dma_write_raw_async(&save_data, 0x08000000, size);
  save_dirty = 0;
}

u32 save_eeprom_read(u32 _unused, u32 offset, u32 *ramAddr) {
  offset *= 2;
  ramAddr[0] = save_data.eeprom[offset];
  ramAddr[1] = save_data.eeprom[offset+1];
  return 0;
}

u32 save_eeprom_write(u32 _unused, u32 offset, u32 *ramAddr) {
  offset *= 2;
  save_data.eeprom[offset] = ramAddr[0];
  save_data.eeprom[offset+1] = ramAddr[1];
  save_dirty = 1;
  return 0;
}
