#ifndef SAVE_H
#define SAVE_H

#include "util.h"
#include "bt.h"

#define SAVE_MAGIC 0x84070013

typedef struct {
  u8 jinjos[9];
  u8 jiggies;
  u8 honeycombs;
  u8 pages;
  u8 green_relics; // unused
  u8 notes;
  u8 treble_clefs;
  u8 doubloons;
  u8 tickets; // unused
  u8 mumbo_tokens;
} save_data_totals_t;

typedef struct Save_Data_s {
  u32 magic;
  u32 version;
  u32 eeprom[512];
  struct {
    u32 seed;
    bt_save_flags_t fake_flags;
    save_data_totals_t totals;
    u8 traps[AP_TRAP_MAX];
    u8 nests[60];
    u8 golden_egg_nests;
    u8 egg_nests;
    u8 feather_nests;
  } custom[3];
} save_data_t;

extern save_data_t save_data;
extern u8 save_dirty;
#define bt_custom_save (save_data.custom[bt_save_slot])
#define bt_fake_flags (bt_custom_save.fake_flags)

void save_init();
void save_sram_write();
u32 save_eeprom_read(u32 _unused, u32 offset, u32 *ramAddr);
u32 save_eeprom_write(u32 _unused, u32 offset, u32 *ramAddr);
u32 save_fake_has_move(u16 data);
void save_fake_set_move(u16 data, u8 state);
u32 save_fake_get_bit(u16 data);
u32 save_fake_set_bit(u16 data);
u32 save_fake_give_fast_swimming();
u32 save_fake_give_bubbles();
void save_fake_give_move(u16 data);
void save_fake_give_item(u16 data);
void save_fake_give_homing_eggs();
void save_fake_give_breegull_bash();
u32 save_fake_count_item(u16 data);
bool save_custom_get_bit(u8* data, u16 id);
bool save_custom_set_bit(u8* data, u16 id);
u8 save_has_egg_type(u16 type);
u8 save_worlds_jiggy_requirment(u8 world);
u16 save_jamjar_silo_requirements(bt_move_silo_t* silo_ptr, bt_move_silo_data_t* silo_data_ptr);
u16 save_totals(u8 type);
u8 save_jinjo_family_count(u8 color);

#endif // SAVE_H
