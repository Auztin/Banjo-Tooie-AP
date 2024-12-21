#ifndef BT_PLAYER_CHAR_H
#define BT_PLAYER_CHAR_H

typedef struct {
  u8 unknown[0xE4];
  bt_xyz_t* pos;
} bt_player_t;

typedef struct {
  bt_player_t* loaded[19];
  u32 control_index;
  u16 control_index2; // seems to be a copy?
  u16 control_type;
  u32 _unknown1[5];
  u8 character_state;
  u8 died;
} bt_player_chars_t;
#define bt_player_chars (*(bt_player_chars_t*)0x80135490)
#define bt_current_player_char (bt_player_chars.loaded[bt_player_chars.control_index])

typedef struct {
  u32 _unknown;
  u32 pos_rot;
} bt_cam_pointers_t;
#define bt_cameras ((bt_cam_pointers_t*)(*(u32*)0x80127728))

typedef void (*bt_fnt_set_camera_position)(u32, bt_xyz_t*);
#define bt_fn_set_camera_position ((bt_fnt_set_camera_position)0x80110770)

typedef u32 (*bt_fnt_hurt_player)(u32, u32, u32);
#define _bt_fn_hurt_player ((bt_fnt_hurt_player)0x800F79DC)
#define bt_fn_hurt_player(control_index) _bt_fn_hurt_player(control_index, 4, 0x80132ED0)

typedef u32 (*bt_fnt_get_health)(bt_player_t*);
#define bt_fn_get_health ((bt_fnt_get_health)0x800A1718)

typedef u32 (*bt_fnt_increase_health)(bt_player_t*, s32);
#define bt_fn_increase_health ((bt_fnt_increase_health)0x800A17A8)

typedef u32 (*bt_fnt_refill_air)(u16, u16);
#define bt_fn_refill_air ((bt_fnt_refill_air)0x800CE9E8)

typedef u32 (*bt_fnt_set_character)(bt_player_t*, u16);
#define bt_fn_set_character ((bt_fnt_set_character)0x800A3410)

typedef u32 (*bt_fnt_load_character_model)(bt_player_t*);
#define bt_fn_load_character_model ((bt_fnt_load_character_model)0x80092778)

typedef u32 (*bt_fnt_set_character_animation)(bt_player_t*, u16);
#define bt_fn_set_character_animation ((bt_fnt_set_character_animation)0x8009E5C8)

typedef u32 (*bt_fnt_get_character_animation)(bt_player_t*);
#define bt_fn_get_character_animation ((bt_fnt_get_character_animation)0x8009E6F8)

typedef u32 (*bt_fnt_get_character_last_animation)(bt_player_t*);
#define bt_fn_get_character_last_animation ((bt_fnt_get_character_last_animation)0x8009E710)

typedef u32 (*bt_fnt_get_default_animation)(bt_player_t*);
#define bt_fn_get_default_animation ((bt_fnt_get_default_animation)0x80084750)

typedef u32 (*bt_fnt_character_in_water)(bt_player_t*);
#define bt_fn_character_in_water ((bt_fnt_character_in_water)0x8008E35C)

typedef u32 (*bt_fnt_character_touching_ground)(bt_player_t*);
#define bt_fn_character_touching_ground ((bt_fnt_character_touching_ground)0x8008E078)

typedef u32 (*bt_fnt_character_move_to)(bt_xyz_t*, float speed, u32 callback);
#define bt_fn_character_move_to ((bt_fnt_character_move_to)0x80090358)

typedef bool (*bt_fnt_character_transform_animation)(u32 control_index, u8 character);
#define bt_fn_character_transform ((bt_fnt_character_transform_animation)0x800F8730)

#define bt_fn_change_character(character, type) ({                                  \
  bt_fn_set_character(character, type);                                             \
  bt_fn_load_character_model(character);                                            \
  bt_fn_set_character_animation(character, bt_fn_get_default_animation(character)); \
})

enum {
  BT_PLAYER_CHAR_BANJO_KAZOOIE = 1,
  BT_PLAYER_CHAR_SNOWBALL,
  BT_PLAYER_CHAR_BEE = 6,
  BT_PLAYER_CHAR_WASHER,
  BT_PLAYER_CHAR_STONY,
  BT_PLAYER_CHAR_BREEGULL_BLASTER,
  BT_PLAYER_CHAR_BANJO,
  BT_PLAYER_CHAR_KAZOOIE,
  BT_PLAYER_CHAR_SUB,
  BT_PLAYER_CHAR_MUMBO,
  BT_PLAYER_CHAR_GOLDEN_GOLIATH,
  BT_PLAYER_CHAR_DETONATOR,
  BT_PLAYER_CHAR_VAN,
  BT_PLAYER_CHAR_CLOCKWORK,
  BT_PLAYER_CHAR_TREX,
  BT_PLAYER_CHAR_DADDY_TREX,
};

#endif // BT_PLAYER_CHAR_H
