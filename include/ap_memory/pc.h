#ifndef AP_MEMORY_PC_H
#define AP_MEMORY_PC_H

#include "items.h"

typedef struct {
  struct {
    u8 death_link_us; // if != n64.death_link_us, send death link and increment
    u8 death_link_ap; // increment to send death link to game
    u8 show_text; // only increment if == n64.show_text
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
    u8 text[77]; // currently limited by clockwork tutorial text size
  } misc;
  struct {
    u32 seed; // unused
    u8 randomize_chuffy;
    u8 skip_puzzles;
    u8 skip_klungo;
    u8 skip_tower_of_tragedy;
    u8 speed_up_minigames;
    u8 jiggy_requirements[10];
    u8 open_silos[AP_SILO_MAX];
  } settings;
  u8 items[AP_ITEM_MAX];
} ap_memory_pc_t;

#endif // AP_MEMORY_PC_H
