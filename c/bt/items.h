#ifndef BT_ITEMS_H
#define BT_ITEMS_H

enum {
  BT_ITEM_BLUE_EGGS,
  BT_ITEM_FIRE_EGGS,
  BT_ITEM_ICE_EGGS,
  BT_ITEM_GRENADE_EGGS,
  BT_ITEM_CLOCKWORK_EGGS,
  BT_ITEM_UNKNOWN,
  BT_ITEM_RED_FEATHERS,
  BT_ITEM_GOLD_FEATHERS,
  BT_ITEM_GLOWBOS,
  BT_ITEM_EMPTY_HONEYCOMBS,
  BT_ITEM_PAGES,
  BT_ITEM_BURGERS,
  BT_ITEM_FRIES,
  BT_ITEM_TICKETS,
  BT_ITEM_DOUBLOONS,
  BT_ITEM_GOLDEN_SACRED_STATUE,
  BT_ITEM_BEANS,
  BT_ITEM_FISH,
  BT_ITEM_MYSTERY_EGGS,
  BT_ITEM_ICE_KEYS,
  BT_ITEM_MEGA_GLOWBOS,
};
#define bt_items ((u16*)(*(u32*)0x8012B250))

typedef struct {
  u16 key;
  u16 _unknown[3];
} bt_item_keys_t;
#define bt_item_keys ((bt_item_keys_t*)0x800D1A04)

typedef struct {
  u16 _unknown;
  u16 value;
} bt_items_max_t;
#define bt_items_max ((bt_items_max_t*)0x8011AF50)

typedef u32 (*bt_fnt_increase_item)(u16, s32);
#define _bt_fn_increase_item ((bt_fnt_increase_item)0x800D175C)
#define bt_fn_increase_item(id, amount) _bt_fn_increase_item(id+0x40, amount)

//   bt_items_max[BT_ITEM_BLUE_EGGS].value = 20 ^ bt_item_keys[BT_ITEM_BLUE_EGGS].key;
//   bt_items[BT_ITEM_BLUE_EGGS] = bt_items_max[BT_ITEM_BLUE_EGGS].value;
//   bt_fn_increase_item(BT_ITEM_BLUE_EGGS, 0);

#endif // BT_ITEMS_H
