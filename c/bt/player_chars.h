#ifndef BT_PLAYER_CHAR_H
#define BT_PLAYER_CHAR_H

typedef struct {
  u32 loaded[19];
  u32 control_index;
  u16 control_index2; // seems to be a copy?
  u16 control_type;
  u32 _unknown1[5];
  u8 total_loaded;
  u8 died;
} bt_player_chars_t;
#define bt_player_chars (*(bt_player_chars_t*)0x80135490)
#define bt_current_player_char (bt_player_chars.loaded[bt_player_chars.control_index])

#define BT_PLAYER_CHAR_CLOCKWORK 0x11

typedef u32 (*bt_fnt_hurt_player)(u32, u32, u32);
#define _bt_fn_hurt_player ((bt_fnt_hurt_player)0x800F79DC)
#define bt_fn_hurt_player(control_index) _bt_fn_hurt_player(control_index, 4, 0x80132ED0)

typedef u32 (*bt_fnt_get_health)(u32);
#define bt_fn_get_health ((bt_fnt_get_health)0x800A1718)

typedef u32 (*bt_fnt_increase_health)(u32, s32);
#define bt_fn_increase_health ((bt_fnt_increase_health)0x800A17A8)

typedef u32 (*bt_fnt_refill_air)(u16, u16);
#define bt_fn_refill_air ((bt_fnt_refill_air)0x800CE9E8)

#endif // BT_PLAYER_CHAR_H
