#ifndef MAIN_H
#define MAIN_H

#include "util.h"
#include "bt.h"

typedef struct {
  u8 is_emulator : 1;
  u8 new_file : 1;
  u8 override_text : 1;
  u8 credits_state;
  bt_zoombox_t* zb_credits[2];
} main_t;
extern main_t main;

void pre_init(); // before bt initializes
void post_init(); // after bt initializes, next frame should be start of puzzle transition
void pre_draw_objects(u8 type, bt_draw_ctx_t* draw_ctx);
void post_draw_objects(u8 type, bt_draw_ctx_t* draw_ctx);
void pre_draw_hud(bt_draw_ctx_t* draw_ctx);
void post_draw_hud(bt_draw_ctx_t* draw_ctx);
void pre_loop(); // before after frame
void post_loop(); // after every frame
void pre_load_scene(u16 *scene, u16 *exit); // before a scene load. scene and exit can be changed to load another scene/exit
void post_load_scene(u16 scene, u16 exit); // after a scene load
void pre_load_save(); // during scene load, before save is loaded. bt_save is null
void post_load_save(); // during scene load, after save is loaded
void pre_object_init(bt_object_t *obj); // just after an object is loaded into memory, before it is initialized
void post_object_init(bt_object_t *obj); // just after an object is initialized
void pre_load_data(u16 *id);
void post_load_data(u16 id, u32 addr);

#endif // MAIN_H
