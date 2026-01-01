#pragma once

#include <bt/objects.h>

extern u32 objects_jump;

void objects_jump_now(...);
u32 objects_singleton(u32 addr);
void objects_init(bt_object_t *obj, u32 _unk_A1);
bt_obj_instance_t *objects_spawn(u16 id, bt_s32_xyz_t *pos, u32 yrot, bt_obj_setup_t *setup);
