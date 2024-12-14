#ifndef BT_MAPS_H
#define BT_MAPS_H

#define bt_current_map (*(u16*)0x8012B402)

typedef struct {
  u16 map;
  u8 loading;
  u8 exit;
} bt_loading_map_t;
#define bt_loading_map (*(bt_loading_map_t*)0x80127640)

typedef struct {
  u16 map;
  u16 exit;
} bt_respawn_point_t;
#define bt_respawn_point ((bt_respawn_point_t*)0x80127050)

#define BT_MAP_CUTSCENE_OPENING       0x00A1
#define BT_MAP_SPIRAL_MOUNTAIN        0x00AF
#define BT_MAP_CLOUD_CUCKOOLAND       0x0136
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
#define BT_MAP_CK_GUN_CHAMBER         0x0160
#define BT_MAP_FILE_SELECT            0x0158
#define BT_MAP_TITLE_SCREEN           0x018B
#define BT_MAP_IOH_PLATEAU            0x0152
#define BT_MAP_IOH_PINE_GROVE         0x0154
#define BT_MAP_IOH_CLIFF_TOP          0x0155
#define BT_MAP_IOH_WASTELAND          0x015A
#define BT_MAP_MT_KICKBALL_LOBBY      0x00BB
#define BT_MAP_TDL_OOGLE_BOOGLE_CAVE  0x0115
#define BT_MAP_DIGGER_TUNNEL          0x0141
#define BT_MAP_ANOTHER_DIGGER_TUNNEL  0x015B
#define BT_MAP_IOH_MUMBO              0x0156
#define BT_MAP_MT_MUMBO               0x00B7
#define BT_MAP_GGM_MUMBO              0x00D9
#define BT_MAP_WW_MUMBO               0x0176
#define BT_MAP_JRL_MUMBO              0x00EF
#define BT_MAP_TDL_MUMBO              0x0171
#define BT_MAP_GI_MUMBO               0x0172
#define BT_MAP_HFP_MUMBO              0x0134
#define BT_MAP_CCL_MUMBO              0x013E
#define BT_MAP_CCL_MINGY_JONGO        0x013F
#define BT_MAP_MT_HUMBA               0x00B6
#define BT_MAP_GGM_HUMBA              0x00E9
#define BT_MAP_WW_HUMBA               0x00D5
#define BT_MAP_JRL_HUMBA              0x0120
#define BT_MAP_TDL_HUMBA_ENLARGED     0x0122
#define BT_MAP_TDL_HUMBA              0x011E
#define BT_MAP_GI_HUMBA               0x011F
#define BT_MAP_HFP_HUMBA              0x0135
#define BT_MAP_CCL_HUMBA              0x0140

typedef u32 (*bt_fnt_load_scene)(u16, u16, u8);
#define bt_fn_load_scene ((bt_fnt_load_scene)0x800A7990)

#endif // BT_MAPS_H
