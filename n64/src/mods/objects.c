#include "objects.h"
#include "file_select.h"
#include <bt/_unsorted.h>
#include <bt/maps.h>

u32 objects_singleton(u32 addr) {
	u32 value = (*(u32 *)addr);
	return (value & 0xFFFFFF) * 4 + 0x7FFFFFF0;
}

void objects_init(bt_object_t *obj, u32 _unk_A1) {
	if (BT_IN_GAME || bt_current_map == BT_MAP_FILE_SELECT) {
		switch (obj->objType) {
		case 0x00CD: file_select_init(obj); break;
		}
	}
	bt_objects_init(obj, _unk_A1);
}

bt_obj_instance_t *objects_spawn(u16 id, bt_s32_xyz_t *pos, u32 yrot, bt_obj_setup_t *setup) {
	return bt_objects_spawn(id, pos, yrot, setup);
}
