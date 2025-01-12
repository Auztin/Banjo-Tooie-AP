#ifndef NDEBUG

#include "debug.h"
#include "warp_to.h"

void debug_draw(bt_draw_ctx_t* draw_ctx) {
  debug_warp_to_draw(draw_ctx);
}

void debug_spawn_prop(u16 id, bt_s32_xyz_t* pos, u32 yrot, bt_obj_setup_t* setup, bt_obj_instance_t* obj) {
  debug_warp_to_spawn_prop(id, pos, yrot, setup, obj);
}

void debug_loop() {
  debug_warp_to_loop();
}

void debug_load_scene(u16* scene, u16* exit) {
  debug_load_scene(scene, exit);
}

#endif // NDEBUG
