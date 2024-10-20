#include "save.h"
#include "main.h"
#include "util.h"
#include "bt.h"

u32 inject_load_scene(u16 scene, u16 entry, u32 _unknown_A2, u32 _unknown_A3) {
  pre_load_scene(&scene, &entry);
  u32 ret;
  asm( // reset registers and run original function
    "MOVE $a0, %1;"
    "MOVE $a1, %2;"
    "MOVE $a2, %3;"
    "MOVE $a3, %4;"
    "ADDIU $sp, $sp, -0x20;"
    "LUI $t6, 0x8012;"
    "JAL 0x800A72AC;"
    "MOVE %0, $v0;"
    : "=X" (ret)
    : "X" (scene), "X" (entry), "X" (_unknown_A2), "X" (_unknown_A3)
    : "a0", "a1", "a2", "a3"
  );
  post_load_scene(scene, entry);
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
    without this, and with the following injects, the game will simply hang after performing the check (a minute or so while in game)
  */
  (*(vu8*)0x8007E9B3) = 0x08;

  // replace game's object init function
  util_inject(UTIL_INJECT_FUNCTION, 0x80081F1C, (u32)inject_object_init, 0);

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
