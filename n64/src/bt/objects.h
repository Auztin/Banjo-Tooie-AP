#pragma once

#include "gfx.h"
#include <n64/types.h>

typedef struct {
	u32 _unknown_0x00_0x04[2];
	u16 objPointerArrayLength;
	u16 _unknown_0x0A;
	u16 _unknown_0x0C;
	u8 objInternalNameLength;
	u8 _unknown_0x0F;
	u32 _unknown_0x10_0x28[7];
	u16 objType;
	u16 _unknown_0x2E;
	u32 _unknown_0x30;
	u32 objPointer;
	u32 objPointers[]; // of size objPointerArrayLength

	// char *objInternalName; // null terminated
} bt_object_t;

typedef struct {
} bt_obj_data_t;

typedef struct {
	u32 _unknown1[5];
	s16 type;
	u16 _unknown2;
	u32 _unknown3[3];
	u16 state;
	u16 _unknown4;
	u16 _unknown6;
	u8 collectable;
} bt_obj_instance_data_t;

typedef struct {
	bt_s16_xyz_t pos;
	u16 obj_data : 9;
	u16 _unknown1 : 7;
	u16 type;
	u16 _unknown2;
	u32 _unknown3;
	u32 id : 11;
	u32 _unknown4 : 21;
} bt_obj_setup_t;
typedef struct {
	bt_obj_instance_data_t *data;
	bt_xyz_t pos;
	bt_obj_data_t *(*fn_obj_init)(void);
	u32 _unknown0x14_0x18[2];
	u32 sprite_index;
	u32 _unknown0x20_0x2C[4];
	u32 sprite_mode;
	u32 _unknown0x34_0x40[4];
	struct {
		float x;
		float y;
		float z;
	} rot;
	u32 _unknown0x50_0x54[2];
	float timer;
	u32 _unknown0x5C_0x60[2];
	u8 _unknown0x64;
	u8 _unknown0x65_4 : 4;
	u8 state : 4; // 4 hidden, 5 normal, 7 delete
	u8 _unknown0x66;
	u8 _unknown0x67;
	u32 _unknown0x68;
	u32 id : 11;
	u32 _unknown0x6C_0 : 21;
	u16 _unknown0x70;
	u8 obj_state;
	u8 _unknown0x73;
	u16 _unknown0x74;
	union {
		struct {
			u16 obj_data : 9;
			u16 _unknown0x77_0 : 7;
		};
		struct {
			u8 _unknown0x76;
			u8 respawn : 1;
			u8 _unknown0x77_0 : 7;
		} nests;
	};
	u16 _unknown0x78;
	u8 _unknown0x7A;
	struct {
		u8 _unknown0x7B_7 : 1;
		u8 _unknown0x7B_6 : 1;
		u8 _unknown0x7B_5 : 1;
		u8 _unknown0x7B_4 : 1;
		u8 _unknown0x7B_3 : 1;
		u8 _unknown0x7B_2 : 1;
		u8 blend_color : 1;
		u8 _unknown0x7B_0 : 1;
	};
	u16 _unknown0x7C;
	u8 display_state;
	u8 _unknown0x7F;
	u32 _unknown0x80_0x94[6];
	struct {
		u8 red;
		u8 green;
		u8 blue;
		u8 alpha;
	} color;
} bt_obj_instance_t;

u32 bt_objects_init(bt_object_t *obj, u32);
bt_obj_instance_t *bt_objects_spawn(u16 id, bt_s32_xyz_t *pos, u32 yrot, bt_obj_setup_t *setup);

extern u32 objects_jump;

void objects_jump_now(...);
u32 objects_singleton(u32 addr);
void objects_init(bt_object_t *obj, u32 _unk_A1);
bt_obj_instance_t *objects_spawn(u16 id, bt_s32_xyz_t *pos, u32 yrot, bt_obj_setup_t *setup);
