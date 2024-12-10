#ifndef AP_MEMORY_PC_H
#define AP_MEMORY_PC_H

#include "items.h"

#define AP_MEMORY_EXIT_MAP_MAX 63

typedef struct {
  u16 on_map;
  u16 og_map;
  u16 to_map;
  u8  og_exit;
  u8  to_exit;
} ap_memory_pc_exit_map_t;

typedef struct {
  struct {
    u8 death_link_us; // if != n64.death_link_us, send death link and increment
    u8 death_link_ap; // increment to send death link to game
    u8 show_message; // only increment if == n64.show_text
  } misc;
  /*
    127 = START
    128 = R
    129 = Z
    130 = C RIGHT
    131 = C UP
    132 = C DOWN
    133 = C LEFT
    134 = B
    135 = A
  */
  u8 message[508];
  struct {
    u32 seed;
    u8 randomize_chuffy;
    u8 randomize_nests;
    u8 skip_puzzles;
    u8 backdoors;
    u8 skip_klungo;
    u8 skip_tower_of_tragedy;
    u8 speed_up_minigames;
    u8 dialog_character;
    u8 max_mumbo_tokens;
    u8 jiggy_requirements[11];
    u8 open_silos[AP_SILO_MAX];
  } settings;
  u8 items[AP_ITEM_MAX];
  ap_memory_pc_exit_map_t exit_map[AP_MEMORY_EXIT_MAP_MAX];
} ap_memory_pc_t;

#endif // AP_MEMORY_PC_H
