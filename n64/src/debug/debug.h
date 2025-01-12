#ifndef DEBUG_H
#define DEBUG_H

#ifndef NDEBUG

#include "util.h"
#include "bt.h"

void debug_draw(bt_draw_ctx_t* draw_ctx);
void debug_spawn_prop(u16 id, bt_s32_xyz_t* pos, u32 yrot, bt_obj_setup_t* setup, bt_obj_instance_t* obj);
void debug_loop();
void debug_load_scene(u16* scene, u16* exit);

#else

#define debug_draw(draw_ctx)
#define debug_spawn_prop(id, pos, yrot, setup, obj)
#define debug_loop()
#define debug_load_scene(scene, exit)

#endif // NDEBUG

#endif // DEBUG_H
