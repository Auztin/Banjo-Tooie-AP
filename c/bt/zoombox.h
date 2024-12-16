#ifndef BT_ZOOMBOX_H
#define BT_ZOOMBOX_H

typedef struct {
  u32 _unknown0x000_0x16C[92];
  u16 _unknown0x170;
  u16 icon;
} bt_zoombox_t;

extern bt_zoombox_t* bt_fn_zoombox_new(u16 y, u16 icon, u8 unknown, bool flipped); // unknown == 2 == no audio

typedef void (*bt_fnt_zoombox_text_speed)(bt_zoombox_t*, float); // higher is faster
#define bt_fn_zoombox_text_speed ((bt_fnt_zoombox_text_speed)0x80087C28)

typedef void (*bt_fnt_zoombox_background_speed)(bt_zoombox_t*, float); // higher is slower
#define bt_fn_zoombox_background_speed ((bt_fnt_zoombox_background_speed)0x80087C30)

typedef void (*bt_fnt_zoombox_x_size_length)(bt_zoombox_t*, u16 x, float size, float length);
#define bt_fn_zoombox_x_size_length ((bt_fnt_zoombox_x_size_length)0x80087BB0)

// 80087C40(zoombox, bool disabled=0)

typedef void (*bt_fnt_zoombox_set_opacity)(bt_zoombox_t*, u8);
#define bt_fn_zoombox_set_opacity ((bt_fnt_zoombox_set_opacity)0x80087BC0)

typedef u8 (*bt_fnt_zoombox_get_opacity)(bt_zoombox_t*);
#define bt_fn_zoombox_get_opacity ((bt_fnt_zoombox_get_opacity)0x80087BC8)

typedef void (*bt_fnt_zoombox_play_sound)(bt_zoombox_t*, bool);
#define bt_fn_zoombox_play_sound ((bt_fnt_zoombox_play_sound)0x80087B98)

typedef u8 (*bt_fnt_zoombox_state)(bt_zoombox_t*);
#define bt_fn_zoombox_state ((bt_fnt_zoombox_state)0x80087AF8)

typedef void (*bt_fnt_zoombox_init)(bt_zoombox_t*);
#define bt_fn_zoombox_init ((bt_fnt_zoombox_init)0x80087B28)

typedef void (*bt_fnt_zoombox_text_color)(bt_zoombox_t*, bt_color_t*);
#define bt_fn_zoombox_text_color ((bt_fnt_zoombox_text_color)0x80087BB8)

typedef void (*bt_fnt_zoombox_append_text)(bt_zoombox_t*, char*);
#define bt_fn_zoombox_append_text ((bt_fnt_zoombox_append_text)0x80087B20)

typedef void (*bt_fnt_zoombox_append_lines)(bt_zoombox_t*, u8 lines, char**);
#define bt_fn_zoombox_append_lines ((bt_fnt_zoombox_append_lines)0x80087B18)

typedef void (*bt_fnt_zoombox_clear_text)(bt_zoombox_t*);
#define bt_fn_zoombox_clear_text ((bt_fnt_zoombox_clear_text)0x80087BE0)

typedef void (*bt_fnt_zoombox_icon)(bt_zoombox_t*, u16); // instantly changes
#define bt_fn_zoombox_icon ((bt_fnt_zoombox_icon)0x80087C00)

typedef void (*bt_fnt_zoombox_queue_icon)(bt_zoombox_t*, u16); // smoothly changes on close
#define bt_fn_zoombox_queue_icon ((bt_fnt_zoombox_queue_icon)0x80087C08)

typedef void (*bt_fnt_zoombox_leave)(bt_zoombox_t*); // wont leave until closed
#define bt_fn_zoombox_leave ((bt_fnt_zoombox_leave)0x80087B30)

typedef void (*bt_fnt_zoombox_open)(bt_zoombox_t*);
#define bt_fn_zoombox_open ((bt_fnt_zoombox_open)0x80087B38)

typedef void (*bt_fnt_zoombox_close)(bt_zoombox_t*);
#define bt_fn_zoombox_close ((bt_fnt_zoombox_close)0x80087BE8)

typedef void (*bt_fnt_zoombox_wobble_text)(bt_zoombox_t*, bool);
#define bt_fn_zoombox_wobble_text ((bt_fnt_zoombox_wobble_text)0x80087C20)

// 80087B90(zoombox) // returns 0 or 1. is_selected?

typedef void (*bt_fnt_zoombox_selected)(bt_zoombox_t*, bool); // smoothly fades
#define bt_fn_zoombox_selected ((bt_fnt_zoombox_selected)0x80087B88)

typedef void (*bt_fnt_zoombox_update)(bt_zoombox_t*);
#define bt_fn_zoombox_update ((bt_fnt_zoombox_update)0x80087B00)

typedef void (*bt_fnt_zoombox_draw)(bt_zoombox_t*, bt_draw_ctx_t*);
#define bt_fn_zoombox_draw ((bt_fnt_zoombox_draw)0x80087AF0)

typedef void (*bt_fnt_zoombox_free)(bt_zoombox_t*);
#define bt_fn_zoombox_free ((bt_fnt_zoombox_free)0x80087AE0)

typedef void (*bt_fnt_zoomboxdata_play_sound)(u16 icon);
#define bt_fn_zoomboxdata_play_sound ((bt_fnt_zoomboxdata_play_sound)0x80088410)

enum {
  BT_ZOOMBOX_STATE_BUSY,
  BT_ZOOMBOX_STATE_READY,
  BT_ZOOMBOX_STATE_OPENED, // or printing text
  BT_ZOOMBOX_STATE_TEXT_PRINTED,
  BT_ZOOMBOX_STATE_CLOSED,
  BT_ZOOMBOX_STATE_OFFSCREEN,
  BT_ZOOMBOX_STATE_DONE,
};

enum {
  BT_ZOOMBOX_ICON_GLOWBO,
  BT_ZOOMBOX_ICON_JIGGY,
  BT_ZOOMBOX_ICON_HONEYCOMB,
  BT_ZOOMBOX_ICON_SUB,
  BT_ZOOMBOX_ICON_WASHER,
  BT_ZOOMBOX_ICON_NEST_BLUE_EGGS, // no voice
  BT_ZOOMBOX_ICON_NEST_FIRE_EGGS, // no voice
  BT_ZOOMBOX_ICON_NEST_MINE_EGGS, // no voice
  BT_ZOOMBOX_ICON_NEST_CLOCKWORK_EGGS, // no voice
  BT_ZOOMBOX_ICON_NEST_GRENADE_EGGS, // no voice
  BT_ZOOMBOX_ICON_NEST_RED_FEATHERS, // no voice
  BT_ZOOMBOX_ICON_NEST_GOLD_FEATHERS, // no voice
  BT_ZOOMBOX_ICON_BANJO,
  BT_ZOOMBOX_ICON_KAZOOIE,
  BT_ZOOMBOX_ICON_KAZOOIE_HIGH_PITCHED,
  BT_ZOOMBOX_ICON_BOTTLES,
  BT_ZOOMBOX_ICON_MUMBO,
  BT_ZOOMBOX_ICON_JINJO_YELLOW,
  BT_ZOOMBOX_ICON_JINJO_GREEN,
  BT_ZOOMBOX_ICON_JINJO_BLUE,
  BT_ZOOMBOX_ICON_JINJO_PURPLE,
  BT_ZOOMBOX_ICON_JINJO_ORANGE,
  BT_ZOOMBOX_ICON_BEEHIVE = 31, // voice lingers
  BT_ZOOMBOX_ICON_GRUNTY = 34,
  BT_ZOOMBOX_ICON_ZUBBA = 36,
  BT_ZOOMBOX_ICON_JAMJARS = 40,
  BT_ZOOMBOX_ICON_BOTTLES2,
  BT_ZOOMBOX_ICON_BOVINA,
  BT_ZOOMBOX_ICON_MINJO_WHITE,
  BT_ZOOMBOX_ICON_MINJO_ORANGE,
  BT_ZOOMBOX_ICON_MINJO_YELLOW,
  BT_ZOOMBOX_ICON_MINJO_BROWN,
  BT_ZOOMBOX_ICON_UNOGOPAZ = 48,
  BT_ZOOMBOX_ICON_CHIEF_BLOATAZIN,
  BT_ZOOMBOX_ICON_DILBERTA,
  BT_ZOOMBOX_ICON_STONIES1,
  BT_ZOOMBOX_ICON_STONIES2,
  BT_ZOOMBOX_ICON_STONIES3,
  BT_ZOOMBOX_ICON_CANARY_MARY,
  BT_ZOOMBOX_ICON_CHEATO,
  BT_ZOOMBOX_ICON_GOBI,
  BT_ZOOMBOX_ICON_DINO_KID1,
  BT_ZOOMBOX_ICON_MR_PATCH,
  BT_ZOOMBOX_ICON_MOGGY,
  BT_ZOOMBOX_ICON_SOGGY,
  BT_ZOOMBOX_ICON_GROGGY,
  BT_ZOOMBOX_ICON_MRS_BOGGY,
  BT_ZOOMBOX_ICON_PROSPECTOR,
  BT_ZOOMBOX_ICON_HUMBA,
  BT_ZOOMBOX_ICON_UFO,
  BT_ZOOMBOX_ICON_OLD_KING_COAL,
  BT_ZOOMBOX_ICON_GRUNTY2,
  BT_ZOOMBOX_ICON_SSSLUMBER = 70, // voice lingers
  BT_ZOOMBOX_ICON_BOGGY,
  BT_ZOOMBOX_ICON_GRUNTY3 = 77,
  BT_ZOOMBOX_ICON_BIG_AL = 80,
  BT_ZOOMBOX_ICON_SALTY_JOE,
  BT_ZOOMBOX_ICON_CONGA,
  BT_ZOOMBOX_ICON_PAWNO,
  BT_ZOOMBOX_ICON_TIPTUP,
  BT_ZOOMBOX_ICON_JOLLY,
  BT_ZOOMBOX_ICON_MERRY_MAGGIE,
  BT_ZOOMBOX_ICON_TERRY,
  BT_ZOOMBOX_ICON_BARGASAURUS,
  BT_ZOOMBOX_ICON_BANJO2 = 91,
  BT_ZOOMBOX_ICON_KAZOOIE2,
  BT_ZOOMBOX_ICON_YELLOW_STONY = 96,
  BT_ZOOMBOX_ICON_ALIEN = 98,
  BT_ZOOMBOX_ICON_CHRIS_P_BACON,
  BT_ZOOMBOX_ICON_CAPTAIN_BLUBBER,
  BT_ZOOMBOX_ICON_STYRACOSAURUS_MOM,
  BT_ZOOMBOX_ICON_ROYSTEN = 103,
  BT_ZOOMBOX_ICON_SAFE = 105,
  BT_ZOOMBOX_ICON_GUFFO,
  BT_ZOOMBOX_ICON_MR_FIT,
  BT_ZOOMBOX_ICON_ZUBBA2 = 109, // has bottles' voice
  BT_ZOOMBOX_ICON_CAPTAIN_BLACKEYE,
  BT_ZOOMBOX_ICON_JAMJARS2,
  BT_ZOOMBOX_ICON_JINJO_RED,
  BT_ZOOMBOX_ICON_JINJO_WHITE = 114,
  BT_ZOOMBOX_ICON_JINJO_BLACK,
  BT_ZOOMBOX_ICON_JINJO_BROWN,
  BT_ZOOMBOX_ICON_CHILLY_WILLY,
  BT_ZOOMBOX_ICON_CHILLI_BILLI,
  BT_ZOOMBOX_ICON_MINGY_JONGO,
  BT_ZOOMBOX_ICON_YELLOW_DODGEM,
  BT_ZOOMBOX_ICON_MUMBO2,
  BT_ZOOMBOX_ICON_BANJO3,
  BT_ZOOMBOX_ICON_KAZOOIE3,
  BT_ZOOMBOX_ICON_BOTTLES3,
  BT_ZOOMBOX_ICON_MINGELLA,
  BT_ZOOMBOX_ICON_BLOBBELDA,
  BT_ZOOMBOX_ICON_KLUNGO,
  BT_ZOOMBOX_ICON_GRUNTY_ECHO,
  BT_ZOOMBOX_ICON_BOTTLES_DEAD = 132,
  BT_ZOOMBOX_ICON_MINJO_GREEN = 134,
  BT_ZOOMBOX_ICON_MINJO_RED,
  BT_ZOOMBOX_ICON_MINJO_BLUE,
  BT_ZOOMBOX_ICON_MINJO_PURPLE,
  BT_ZOOMBOX_ICON_MINJO_BLACK,
  BT_ZOOMBOX_ICON_RABBIT_WORKER1 = 142,
  BT_ZOOMBOX_ICON_RABBIT_WORKER2,
  BT_ZOOMBOX_ICON_UNGA_BUNGA = 150,
  BT_ZOOMBOX_ICON_JIGGYWIGGY,
  BT_ZOOMBOX_ICON_JIGGYWIGGY_DISCIPLE,
  BT_ZOOMBOX_ICON_ZUBBA3,
  BT_ZOOMBOX_ICON_JIGGYWIGGY2,
  BT_ZOOMBOX_ICON_HONEY_B,
  BT_ZOOMBOX_ICON_BANJO_KAZOOIE = 157,
  BT_ZOOMBOX_ICON_BOTTLES_DEAD2,
  BT_ZOOMBOX_ICON_GRUNTY_TIMER, // no voice
  BT_ZOOMBOX_ICON_PIG1,
  BT_ZOOMBOX_ICON_PIG2,
  BT_ZOOMBOX_ICON_OOGLE_BOOGLE,
  BT_ZOOMBOX_ICON_GI_ANNOUNCER,
  BT_ZOOMBOX_ICON_DINGPOT,
  BT_ZOOMBOX_ICON_KING_JINGALING_DEAD,
  BT_ZOOMBOX_ICON_ROCKNUT,
  BT_ZOOMBOX_ICON_MILDRED,
  BT_ZOOMBOX_ICON_BIGGA_FOOT,
  BT_ZOOMBOX_ICON_GEORGE,
  BT_ZOOMBOX_ICON_SABREMAN,
  BT_ZOOMBOX_ICON_KLUNGO2,
  BT_ZOOMBOX_ICON_DIPPY,
  BT_ZOOMBOX_ICON_LOGGO,
  BT_ZOOMBOX_ICON_KING_JINGALING,
  BT_ZOOMBOX_ICON_MRS_BOTTLES,
  BT_ZOOMBOX_ICON_SPECCY,
  BT_ZOOMBOX_ICON_GOGGLES,
  BT_ZOOMBOX_ICON_TARGITZAN,
  BT_ZOOMBOX_ICON_CHOMPA,
  BT_ZOOMBOX_ICON_LORD_WOO_FAK_FAK,
  BT_ZOOMBOX_ICON_WELDAR,
  BT_ZOOMBOX_ICON_ALIEN_CHILD = 183,
  BT_ZOOMBOX_ICON_EVIL_BOTTLES = 187, // ??
  BT_ZOOMBOX_ICON_ALIEN_CHILD2 = 198,
  BT_ZOOMBOX_ICON_ALIEN_CHILD3,
  BT_ZOOMBOX_ICON_DINO_KID2,
  BT_ZOOMBOX_ICON_DINO_SCRIT_SMALL,
  BT_ZOOMBOX_ICON_DINO_SCRIT_BIG,
  BT_ZOOMBOX_ICON_HEGGY,
};

#endif // BT_ZOOMBOX_H
