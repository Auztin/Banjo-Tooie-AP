#pragma once

#include "util.h"
#include "bt/maps.h"

extern void exits_can_pass_displaced();
u32 exits_can_pass(u16* scene, u16* exit, u16* current_map);
u32 exits_check(bt_exit_info_t* info);
void exits_ccl_bubble(u16 scene, u16 exit);
