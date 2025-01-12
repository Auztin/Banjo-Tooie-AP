#ifndef DEBUG_WARP_TO_H
#define DEBUG_WARP_TO_H

#include "util.h"
#include "bt.h"

void debug_warp_to_draw(bt_draw_ctx_t* draw_ctx);
void debug_warp_to_spawn_prop(u16 id, bt_s32_xyz_t* pos, u32 yrot, bt_obj_setup_t* setup, bt_obj_instance_t* obj);
void debug_warp_to_loop();
void debug_warp_to_load_scene(u16* scene, u16* exit);

#endif // DEBUG_WARP_TO_H
