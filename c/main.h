#ifndef MAIN_H
#define MAIN_H

#include "util.h"

typedef struct {
  u8 is_emulator : 1;
  u8 new_file : 1;
  u8 frame_count;
} main_t;
extern main_t main;

void pre_init(); // before bt initializes
void post_init(); // after bt initializes, next frame should be start of puzzle transition
void pre_loop(); // before after frame
void post_loop(); // after every frame
void pre_load_scene(u16 *scene, u16 *entry); // before a scene load. scene and entry can be changed to load another scene/entry
void post_load_scene(u16 scene, u16 entry); // after a scene load
void pre_load_save(); // during scene load, before save is loaded. bt_save is null
void post_load_save(); // during scene load, after save is loaded
void pre_object_init(); // just after an object is loaded into memory, before it is initialized
void post_object_init(); // just after an object is initialized

#endif // MAIN_H
