#ifndef AP_MEMORY_N64_H
#define AP_MEMORY_N64_H

#include <bt/save_flags.h>

typedef struct {
  struct {
    u8 show_message; // if != pc.show_text, show pc.text and increment
    u8 death_link_us; // incremented if player dies on their own
    u8 death_link_ap; // if != pc.death_link_ap, kill player and increment
    u16 current_map;
  } misc;
  struct {
    bt_save_flags_t real; // vanilla save flags
    bt_save_flags_t fake; // separated save flags
    u8 nests[60];
  } saves;
} ap_memory_n64_t;

#endif // AP_MEMORY_N64_H
