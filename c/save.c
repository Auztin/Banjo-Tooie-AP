#include "save.h"
#include "dma.h"
#include "bt.h"

save_data_t save_data = {0,};
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

u32 save_fake_move_flags(u16 data, u8 setFlag, u8 flagState) {
  if (bt_save_slot > 2) return 0;
  data += 0xC5; // +0xED for move function, -0x28 for bit function
  u32 save = (u32)&(bt_fake_flags);
  if (setFlag) return bt_fn_set_bit(save, data, flagState);
  else return bt_fn_get_bit(save, data);
}

u32 save_fake_has_move(u16 data) {
  return save_fake_move_flags(data, 0, 0);
}

void save_fake_set_move(u16 data, u8 state) {
  save_fake_move_flags(data, 1, state);
}

u32 save_fake_bits(u16 data, u8 setFlag) {
  if (bt_save_slot > 2) return 0;
  switch (data) {
    case 0x0086: // defeated chuffy
    case 0x0095: // levitated train
    case 0x010D: // trex roar
    case 0x0118: // amaze o gaze
    // stop and swop
    case 0x03E2: // used ice key
    case 0x03E3: // collected blue egg
    case 0x03E4: // hatched blue egg
    case 0x03E5: // collected pink egg
    case 0x03E6: // hatched pink egg
    case 0x05A4: // homing eggs cheat received
    case 0x011F: // breegull bash
    // roysten
    case 0x011D: // fast swimming
    case 0x01BF: // extra bubbles
    // train doors
    case 0x0096: // witchy world
    case 0x0163: // grunty industries
    case 0x0164: // terrydactyland
    case 0x01CF: // hailfire peaks (icy side)
    case 0x01D0: // hailfire peaks (fire side)
    case 0x0403: // isle o hags
      data -= 0x28;
      u32 save = (u32)&(bt_fake_flags);
      if (setFlag) return bt_fn_set_bit(save, data, 1);
      else return bt_fn_get_bit(save, data);
    default:
      if (setFlag) return bt_fn_set_save_bit(data);
      else return bt_fn_get_save_bit(data);
  }
}

u32 save_fake_get_bit(u16 data) { // 0x800da298
  return save_fake_bits(data, 0);
}

u32 save_fake_set_bit(u16 data) { // 0x800da544
  return save_fake_bits(data, 1);
}

u32 save_fake_give_fast_swimming() { // 0x800c7074
  return save_fake_bits(0x011D, 1);
}

u32 save_fake_give_bubbles() { // 0x800cf700
  return save_fake_bits(0x01BF, 1);
}

void save_fake_give_move(u16 data) { // 0x8009032C
  save_fake_bits(data+0xED, 1);
}

void save_fake_give_homing_eggs() { // 0x800d3ef4
  save_fake_bits(0x5A4, 1);
}

void save_fake_give_breegull_bash() { // 0x800c7074
  save_fake_bits(0x11F, 1);
}

void save_fake_give_item(u16 data) { // 0x800d1844
  switch (data-0x40) {
    case BT_ITEM_ICE_KEYS:
      save_fake_bits(0x03E2, 1);
      break;
  }
}

u32 save_fake_count_item(u16 data) { // 0x800d1a04
  switch (data-0x40) {
    case BT_ITEM_ICE_KEYS:
      save_fake_bits(0x03E2, 0);
      break;
  }
}

u8 save_has_egg_type(u16 type) {
  switch (type) {
    case 0x0031: {
      if (
           !bt_flags.fire_eggs
        && !bt_flags.grenade_eggs
        && !bt_flags.clockwork_kazooie_eggs
        && !bt_flags.ice_eggs
      ) return 1;
      return bt_flags.blue_eggs;
    }
    case 0x002C: return bt_flags.fire_eggs;
    case 0x002D: return bt_flags.grenade_eggs;
    case 0x002E: return bt_flags.clockwork_kazooie_eggs;
    case 0x002F: return bt_flags.ice_eggs;
    default: return 0;
  }
}

u8 save_worlds_jiggy_requirment(u8 world) {
  if (bt_save_slot > 2 || world > 10) return 99;
  return ap_memory.pc.settings.jiggy_requirements[world];
}

u8 save_jamjar_silo_requirements(bt_jamjar_silos_t* silo_ptr, bt_jamjar_cost_t* silo_cost_ptr) {
  return 0;
}

u16 save_totals(u8 type) {
  if (bt_save_slot > 2 || type > 8) return 0;
  u16 total = 0;
  switch (type) {
    case 0:
      for (int i = 0; i < 9; i++) total += save_jinjo_family_count(i);
      return total;
    case 1: return save_data.custom[bt_save_slot].totals.jiggies;
    case 2: return save_data.custom[bt_save_slot].totals.honeycombs;
    case 3:
      if (bt_flags.mt_mumbo) total++;
      if (bt_flags.gi_mumbo) total++;
      if (bt_flags.ioh_mumbo) total++;
      if (bt_flags.ccl_mumbo) total++;
      if (bt_flags.hfp_mumbo) total++;
      if (bt_flags.tdl_mumbo) total++;
      if (bt_flags.jrl_mumbo) total++;
      if (bt_flags.ww_mumbo) total++;
      if (bt_flags.ggm_mumbo) total++;
      return total;
    case 4: return save_data.custom[bt_save_slot].totals.pages;
    case 5:
      if (bt_flags.mt_sacred_statue_adjacent_big_pillars_room1) total++;
      if (bt_flags.mt_sacred_statue_adjacent_big_pillars_room2) total++;
      if (bt_flags.mt_sacred_statue_near_entrance1) total++;
      if (bt_flags.mt_sacred_statue_near_entrance2) total++;
      if (bt_flags.mt_sacred_statue_small_pillars1) total++;
      if (bt_flags.mt_sacred_statue_small_pillars2) total++;
      if (bt_flags.mt_sacred_statue_small_pillars3) total++;
      if (bt_flags.mt_sacred_statue_sput_sput2) total++;
      if (bt_flags.mt_sacred_statue_sput_sput1) total++;
      if (bt_flags.mt_sacred_statue_sput_sput3) total++;
      if (bt_flags.mt_sacred_statue_sput_sput4) total++;
      if (bt_flags.mt_sacred_statue_adjacent_big_pillars_room3) total++;
      if (bt_flags.mt_sacred_statue_big_pillars4) total++;
      if (bt_flags.mt_sacred_statue_big_pillars3) total++;
      if (bt_flags.mt_sacred_statue_big_pillars1) total++;
      if (bt_flags.mt_sacred_statue_big_pillars2) total++;
      if (bt_flags.mt_sacred_statue_big_pillars5) total++;
      if (bt_flags.mt_sacred_statue_sput_sput5) total++;
      if (bt_flags.mt_sacred_statue_near_sacred_chambers1) total++;
      if (bt_flags.mt_sacred_statue_near_sacred_chambers2) total++;
      if (bt_flags.mt_sacred_statue_passage_near_entrance1) total++;
      if (bt_flags.mt_sacred_statue_passage_near_entrance2) total++;
      if (bt_flags.mt_sacred_statue_passage_near_sacred_chambers1) total++;
      if (bt_flags.mt_sacred_statue_passage_near_sacred_chambers2) total++;
      if (bt_flags.mt_sacred_statue_passage_near_sacred_chambers3) total++;
      return total;
    case 6:
      total += save_data.custom[bt_save_slot].totals.notes * 5;
      total += save_data.custom[bt_save_slot].totals.treble_clefs * 20;
      return total;
    case 7: return save_data.custom[bt_save_slot].totals.doubloons;
    case 8:
      if (bt_flags.ww_ticket_collected_entrance) total++;
      if (bt_flags.ww_ticket_collected_space) total++;
      if (bt_flags.ww_ticket_collected_spooky) total++;
      if (bt_flags.ww_ticket_collected_western) total++;
      return total;
  }
}

u8 save_jinjo_family_count(u8 color) {
  if (bt_save_slot > 2 || color >= 9) return 0;
  return save_data.custom[bt_save_slot].totals.jinjos[color];
}
