#include "save.h"
#include "main.h"
#include "util.h"
#include "bt.h"

extern u32 inject_load_scene_displaced(u16, u16, u32, u32);
u32 inject_load_scene(u16 scene, u16 exit, u32 _unknown_A2, u32 _unknown_A3) {
  pre_load_scene(&scene, &exit);
  u32 ret = inject_load_scene_displaced(scene, exit, _unknown_A2, _unknown_A3);
  post_load_scene(scene, exit);
  return ret;
}

extern u32 inject_get_data_displaced(u16);
u32 inject_get_data(u16 id) {
  pre_get_data(&id);
  u32 data = inject_get_data_displaced(id);
  post_get_data(id, data);
  return data;
}

extern u32 inject_load_data_displaced(u16);
u32 inject_load_data(u16 id) {
  pre_load_data(&id);
  u32 data = inject_load_data_displaced(id);
  post_load_data(id, data);
  return data;
}

extern u32 inject_draw_objects_displaced(u8, bt_draw_ctx_t*);
void inject_draw_objects(u8 type, bt_draw_ctx_t* draw_ctx) {
  /* types
    0 = entities (enemies, nests, npcs, etc)
    1 = static entities (boxes, boulders, mole hills, etc)
    2 = some ui elements (file screen text)
    3 = on screen text (title screen, level names)
    4 = ??
    5 = shadows
    6 = ??
  */
  pre_draw_objects(type, draw_ctx);
  inject_draw_objects_displaced(type, draw_ctx);
  post_draw_objects(type, draw_ctx);
}

extern u32 inject_draw_hud_displaced(bt_draw_ctx_t*);
void inject_draw_hud(bt_draw_ctx_t* draw_ctx) {
  pre_draw_hud(draw_ctx);
  inject_draw_hud_displaced(draw_ctx);
  post_draw_hud(draw_ctx);
}

extern bt_obj_instance_t* inject_spawn_prop_displaced(u16, bt_s32_xyz_t*, u16, bt_obj_setup_t*);
bt_obj_instance_t* inject_spawn_prop(u16 id, bt_s32_xyz_t* pos, u16 yrot, bt_obj_setup_t* setup) {
  bt_obj_setup_t new_setup = pre_spawn_prop(&id, pos, &yrot, setup);
  bt_obj_instance_t* ret = inject_spawn_prop_displaced(id, pos, yrot, &new_setup);
  post_spawn_prop(id, pos, yrot, &new_setup, ret);
  return ret;
}

u32 inject_load_save(u32 _unknown) {
  pre_load_save();
  u32 ret = bt_fn_load_save(_unknown);
  post_load_save();
  return ret;
}

u32 inject_object_init(bt_object_t *obj, u32 _unknown_A1, u32 _unknown_A2, u32 _unknown_A3) {
  pre_object_init(obj);
  u32 ret = bt_fn_object_init(obj, _unknown_A1, _unknown_A2, _unknown_A3);
  post_object_init(obj);
  return ret;
}

u32 inject_init(u32 _unknown) {
  pre_init();
  u32 ret = bt_fn_init(_unknown);

  // replace game's load scene function
  util_inject(UTIL_INJECT_JUMP, 0x800A72A4, (u32)inject_load_scene, 1);

  // replace game's load save function
  util_inject(UTIL_INJECT_FUNCTION, 0x800A731C, (u32)inject_load_save, 0);

  /*
    the game reads most of a section of memory (0x8001E840 - 0x800D2014) during gameplay to verify that nothing has been modified
    setting this convinces the game that it has already successfully verified integrity
    without this, and with some of the following injects, the game will simply hang after performing the check (a minute or so while in game)
  */
  (*(vu8*)0x8007E9B3) = 0x08;

  // replace game's object init function
  util_inject(UTIL_INJECT_FUNCTION, 0x80081F1C, (u32)inject_object_init, 0);

  // replace game's totals function
  util_inject(UTIL_INJECT_JUMP, 0x800D035C, (u32)save_totals, 1);

  // replace game's jinjo totals function
  util_inject(UTIL_INJECT_JUMP, 0x800D1338, (u32)save_jinjo_family_count, 1);

  // replace game's load data function
  util_inject(UTIL_INJECT_JUMP, 0x800D5B34, (u32)inject_load_data, 1);

  // replace game's get data function
  util_inject(UTIL_INJECT_JUMP, 0x800D674C, (u32)inject_get_data, 1);

  // replace game's draw objects function
  util_inject(UTIL_INJECT_JUMP, 0x800EB51C, (u32)inject_draw_objects, 1);

  // replace game's draw hud function
  util_inject(UTIL_INJECT_JUMP, 0x800FA508, (u32)inject_draw_hud, 1);

  // replace game's spawn prop function
  util_inject(UTIL_INJECT_JUMP, 0x80108C90, (u32)inject_spawn_prop, 1);

  post_init();
  return ret;
}

u32 inject_loop() {
  if (save_dirty) save_sram_write();
  pre_loop();
  u32 ret = bt_fn_loop();
  post_loop();
  return ret;
}

u32 inject_hooks() {
  save_init();
  ap_memory_ptrs.version = AP_VERSION.as_int;
  ap_memory_ptrs.pc = (u32)&ap_memory.pc;
  ap_memory_ptrs.pc_message = (u32)&ap_memory.pc.message;
  ap_memory_ptrs.pc_settings = (u32)&ap_memory.pc.settings;
  ap_memory_ptrs.pc_items = (u32)&ap_memory.pc.items;
  ap_memory_ptrs.pc_traps = (u32)&ap_memory.pc.traps;
  ap_memory_ptrs.pc_exit_map = (u32)&ap_memory.pc.exit_map;
  ap_memory_ptrs.n64 = (u32)&ap_memory.n64;
  ap_memory_ptrs.n64_saves_real = (u32)&ap_memory.n64.saves.real;
  ap_memory_ptrs.n64_saves_fake = (u32)&ap_memory.n64.saves.fake;
  ap_memory_ptrs.n64_saves_nests = (u32)&ap_memory.n64.saves.nests;
  ap_memory.pc.settings.dialog_character = 0xFF;
  AP_MEMORY_PTR = &ap_memory_ptrs;

  // replace game's init function
  util_inject(UTIL_INJECT_FUNCTION, 0x800124F4, (u32)inject_init, 0);

  // replace game's loop function
  util_inject(UTIL_INJECT_FUNCTION, 0x800124FC, (u32)inject_loop, 0);

  // convince the game that only eeprom16k is available (we're actually using sram)
  util_inject(UTIL_INJECT_RETVALUE, 0x800166EC, 2, 0);

  // replace game's eeprom read function
  util_inject(UTIL_INJECT_JUMP, 0x80032B10, (u32)save_eeprom_read, 1);

  // replace game's eeprom write function
  util_inject(UTIL_INJECT_JUMP, 0x80032D60, (u32)save_eeprom_write, 1);

  return 0;
}
