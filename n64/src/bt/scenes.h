#pragma once

#include <n64/types.h>

#define bt_current_map (*(u16 *)0x8012B402)

typedef struct {
	s16 x;
	s16 y;
	s16 z;
	u16 _unk1 : 9;
	u16 type : 6;
	u16 _unk2 : 1;
	u16 scene;
	u8 _unk3;
	u8 check_type;
	u32 exit;
} bt_exit_info_t;

void bt_scenes_mt_get_sacred_chamber(bt_exit_info_t *, u32 *scene, u32 *exit);
void bt_scenes_load(u16 scene, u16 exit, u32, u32);

void scenes_load(u16 scene, u16 exit, u32 _unk_A2, u32 _unk_A3);
u32 scenes_check_exit(bt_exit_info_t *info);
