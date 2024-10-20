#ifndef BT_H
#define BT_H

#include "util.h"
#include "bt_flags.h"

typedef struct {
  u16 blue_eggs;
  u16 fire_eggs;
  u16 ice_eggs;
  u16 grenade_eggs;
  u16 clockwork_eggs;
  u16 _unknown;
  u16 red_feathers;
  u16 gold_feathers;
  u16 glowbos;
  u16 empty_honeycombs;
  u16 pages;
  u16 burgers;
  u16 fries;
  u16 tickets;
  u16 doubloons;
  u16 priceless_relic_thingy;
  u16 beans;
  u16 boggy_fish;
  u16 mystery_eggs;
  u16 ice_keys; // 0 allows jv game pak to spawn
  u16 mega_glowbos;
} bt_items_t;
#define bt_items (*(bt_items_t*)(*(u32*)0x8012B250))

typedef struct {
  u16 blue_eggs;
  u16 _unknown_00[3];
  u16 fire_eggs;
  u16 _unknown_01[3];
  u16 ice_eggs;
  u16 _unknown_02[3];
  u16 grenade_eggs;
  u16 _unknown_03[3];
  u16 clockwork_eggs;
  u16 _unknown_04[3];
  u16 _unknown;
  u16 _unknown_05[3];
  u16 red_feathers;
  u16 _unknown_06[3];
  u16 gold_feathers;
  u16 _unknown_07[3];
  u16 glowbos;
  u16 _unknown_08[3];
  u16 empty_honeycombs;
  u16 _unknown_09[3];
  u16 pages;
  u16 _unknown_0A[3];
  u16 burgers;
  u16 _unknown_0B[3];
  u16 fries;
  u16 _unknown_0C[3];
  u16 tickets;
  u16 _unknown_0D[3];
  u16 doubloons;
  u16 _unknown_0E[3];
  u16 priceless_relic_thingy;
  u16 _unknown_0F[3];
  u16 beans;
  u16 _unknown_10[3];
  u16 boggy_fish;
  u16 _unknown_11[3];
  u16 mystery_eggs;
  u16 _unknown_12[3];
  u16 ice_keys;
  u16 _unknown_13[3];
  u16 mega_glowbos;
  u16 _unknown_14[3];
} bt_item_keys_t;
#define bt_item_keys (*(bt_item_keys_t*)0x800D1A04)

typedef struct {
  u16 _unknown_00;
  u16 blue_eggs;
  u16 _unknown_01;
  u16 fire_eggs;
  u16 _unknown_02;
  u16 ice_eggs;
  u16 _unknown_03;
  u16 grenade_eggs;
  u16 _unknown_04;
  u16 clockwork_eggs;
  u16 _unknown_05;
  u16 _unknown;
  u16 _unknown_06;
  u16 red_feathers;
  u16 _unknown_07;
  u16 gold_feathers;
  u16 _unknown_08;
  u16 glowbos;
  u16 _unknown_09;
  u16 empty_honeycombs;
  u16 _unknown_0A;
  u16 pages;
  u16 _unknown_0B;
  u16 burgers;
  u16 _unknown_0C;
  u16 fries;
  u16 _unknown_0D;
  u16 tickets;
  u16 _unknown_0E;
  u16 doubloons;
  u16 _unknown_0F;
  u16 priceless_relic_thingy;
  u16 _unknown_10;
  u16 beans;
  u16 _unknown_11;
  u16 boggy_fish;
  u16 _unknown_12;
  u16 mystery_eggs;
  u16 _unknown_13;
  u16 ice_keys;
  u16 _unknown_14;
  u16 mega_glowbos;
} bt_items_max_t;
#define bt_items_max (*(bt_items_max_t*)0x8011AF50)

typedef struct {
  u32 _unknown_0x00_0x04[2];
  u16 objPointerArrayLength;
  u16 _unknown_0x0A;
  u32 _unknown_0x0C_0x28[8];
  u16 objType;
  u16 _unknown_0x2E;
  u32 _unknown_0x30;
  u32 objPointer;
  u32 objPointers[]; // of size objPointerArrayLength
  // char *objInternalName; // null terminated
} bt_object_t;

typedef struct {
  u8 a : 1;
  u8 b : 1;
  u8 z : 1;
  u8 start : 1;
  u8 dup : 1;
  u8 ddown : 1;
  u8 dleft : 1;
  u8 dright : 1;

  u8 _unused : 2;
  u8 l : 1;
  u8 r : 1;
  u8 cup : 1;
  u8 cdown : 1;
  u8 cleft : 1;
  u8 cright : 1;
} bt_controller_buttons_t;

typedef struct {
  bt_controller_buttons_t held;
  bt_controller_buttons_t held_delayed;
  bt_controller_buttons_t pressed;
  bt_controller_buttons_t released;
  struct {
    f32 x;
    f32 y;
  } joystick;
} bt_controller_t;
#define bt_controllers ((bt_controller_t*)0x80079AF8)

#define BT_MAP_OPENING_CUTSCENE 0x00A1
#define BT_MAP_SPIRAL_MOUNTAIN  0x00AF

#define bt_save_slot (*(u8*)0x8012B3F1) // will be 0xFF during puzzle challenges, and when not in game. reflects hovered save slot at file select
#define bt_save ((bt_save_t*)0x8012C770)
#define bt_flags (*bt_save->flags)
#define bt_temp_flags (*bt_save->temp_flags)
#define bt_current_scene (*(u16*)0x8012B402)

typedef u32 (*bt_fnt_init)(u32);
#define bt_fn_init ((bt_fnt_init)0x80012214)
typedef u32 (*bt_fnt_loop)(void);
#define bt_fn_loop ((bt_fnt_loop)0x800123F4)
typedef u32 (*bt_fnt_load_save)(u32);
#define bt_fn_load_save ((bt_fnt_load_save)0x80087A40)
typedef u32 (*bt_fnt_object_init)(bt_object_t*, u32, u32, u32);
#define bt_fn_object_init ((bt_fnt_object_init)0x80082088)

#endif // BT_H
