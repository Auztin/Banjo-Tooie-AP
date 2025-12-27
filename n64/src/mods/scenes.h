#pragma once

#include <bt/scenes.h>
#include <n64/types.h>

void scenes_load(u16 scene, u16 exit, u32 _unk_A2, u32 _unk_A3);
u32 scenes_check_exit(bt_exit_info_t *info);
