#ifndef BT_OBJECTS_H
#define BT_OBJECTS_H

typedef struct {
  u32 _unknown_0x00_0x04[2];
  u16 objPointerArrayLength;
  u16 _unknown_0x0A;
  u16 _unknown_0x0C;
  u8  objInternalNameLength;
  u8  _unknown_0x0F;
  u32 _unknown_0x10_0x28[7];
  u16 objType;
  u16 _unknown_0x2E;
  u32 _unknown_0x30;
  u32 objPointer;
  u32 objPointers[]; // of size objPointerArrayLength
  // char *objInternalName; // null terminated
} bt_object_t;

#define BT_OBJ_PAGE                 0x00DF
#define BT_OBJ_GLOWBO               0x019E
#define BT_OBJ_JINJO                0x01A9
#define BT_OBJ_HONEYCOMB_PIECE      0x01B6
#define BT_OBJ_MOVE_SILO            0x0320 // jamjar move silos (also shared by bottles' mole hills)
#define BT_OBJ_SWITCH               0x00B0
#define BT_OBJ_ROYSTEN              0x024A
#define BT_OBJ_NESTS                0x00BF
#define BT_OBJ_BOTTLES_FAMILY       0x014B
#define BT_OBJ_BARGASAURUS          0x0111
#define BT_OBJ_CHUFFY               0x01B0
#define BT_OBJ_CHUFFY_CABIN         0x01B1
#define BT_OBJ_TRAIN_SIGN           0x0195
#define BT_OBJ_HEGGY                0x026E
#define BT_OBJ_ICE_KEY              0x026D
#define BT_OBJ_BK_CART              0x0270
#define BT_OBJ_MYSTERY_EGGS         0x0272
#define BT_OBJ_JIGGYWIGGY_TEMPLE    0x00C8
#define BT_OBJ_JIGGYWIGGY_INFO      0x0351
#define BT_OBJ_JIGGYWIGGY_POST      0x00CB
#define BT_OBJ_PAUSE_MENU           0x02A3
#define BT_OBJ_DOUBLOON             0x023C
#define BT_OBJ_JIGGY                0x00B2
#define BT_OBJ_CAPTAIN_BLACKEYE     0x01C8
#define BT_OBJ_FILE_SELECT          0x00CD

typedef struct {
  u32 _unknown1[6];
  u32 operation_state;
  u32 selection1;
  u32 selection2;
  u32 _unknown2[16];
  u8 _unknown3;
  u8 _unknown4 : 3;
  u8 block_selection : 1;
  u8 _unknown5 : 4;
  u16 _unknown6;
  u32 _unknown7[2];
  u16 _unknown8;
  u8 cursor_state;
} bt_obj_file_select_ctx_t;

typedef struct {
} bt_obj_data_t;

typedef bt_obj_data_t* (*bt_fnt_object_get_data)(void);
typedef struct {
  u32 _unknown[4];
  bt_fnt_object_get_data fn_obj_init;
} bt_obj_instance_t;

typedef void (*bt_fnt_world_door_play_anim)(bt_obj_instance_t*, u32 anim, u32 speed);
typedef struct {
  u32 _unknown[16];
  bt_fnt_world_door_play_anim fn_play_anim;
} bt_obj_world_door_t;

typedef void (*bt_fnt_object_count)(u32*);
#define bt_fn_object_count ((bt_fnt_object_count)0x801067C4)

typedef bt_obj_instance_t* (*bt_fnt_object_instance)(u32*);
#define bt_fn_object_instance ((bt_fnt_object_instance)0x8010682C)

#endif // BT_OBJECTS_H
