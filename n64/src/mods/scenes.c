#include "scenes.h"
#include <bt/_unsorted.h>
#include <bt/maps.h>
#include <bt/saves.h>

void scenes_load(u16 scene, u16 exit, u32 _unk_A2, u32 _unk_A3) {
	bt_scenes_load(scene, exit, _unk_A2, _unk_A3);
}

u32 scenes_check_exit(bt_exit_info_t *info) {
	switch (info->type) {
	case 3:
		if (info->scene == 4) {
			u32 scene;
			u32 exit;
			bt_scenes_mt_get_sacred_chamber(info, &scene, &exit);
			info->type = 5;
			info->check_type = 0;
			info->scene = scene - 0xA0;
			info->exit = exit;
		}
		break;
	case 5:
		if (info->check_type == 0x0C) {
			info->check_type = 0;
		check_mumbo_location:
			switch (bt_flags.ccl_mumbo_location) {
			case 1:
				if (bt_current_map == BT_MAP_CCL) {
					if (info->scene == 0x9F) info->scene--;
					else info->scene++;
				}
				break;
			case 3: break;
			default:
				bt_flags.ccl_mumbo_location = (bt_random() % 2) ? 1 : 3;
				goto check_mumbo_location;
			}
		}
		break;
	}
	return info->type;
}
