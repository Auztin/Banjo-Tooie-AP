#ifndef BT_MAPS_H
#define BT_MAPS_H

#define bt_current_map (*(u16*)0x8012B402)

typedef struct {
  u16 map;
  u16 exit;
} bt_respawn_point_t;
#define bt_respawn_point (*(bt_respawn_point_t*)0x80127050)

#define BT_MAP_CUTSCENE_OPENING       0x00A1
#define BT_MAP_SPIRAL_MOUNTAIN        0x00AF
#define BT_MAP_CHUFFYS_CAB            0x00D0
#define BT_MAP_TRAIN_STATION_GGM      0x00D7
#define BT_MAP_TRAIN_STATION_WW       0x00EC
#define BT_MAP_TRAIN_STATION_IOH      0x0155
#define BT_MAP_TRAIN_STATION_TDL      0x0114
#define BT_MAP_TRAIN_STATION_GI       0x0102
#define BT_MAP_TRAIN_STATION_HFP_LAVA 0x0129
#define BT_MAP_TRAIN_STATION_HFP_ICY  0x012A
#define BT_MAP_TOT_QUIZ_ROOM          0x015F
#define BT_MAP_CUTSCENE_REVIVAL       0x0194
#define BT_MAP_JINJO_VILLAGE          0x0142

typedef u32 (*bt_fnt_load_scene)(u16, u16, u8);
#define bt_fn_load_scene ((bt_fnt_load_scene)0x800A7990)

#endif // BT_MAPS_H
