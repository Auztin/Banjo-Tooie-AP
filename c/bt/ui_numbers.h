#ifndef BT_UI_NUMBERS_H
#define BT_UI_NUMBERS_H

enum {
  BT_UI_NUMBER_POSITION_TOP_LEFT,
  BT_UI_NUMBER_POSITION_TOP_LEFT_VERTICAL, // used by bubbles. doesn't display correctly with numbers

  // starts top right, each following is below the previous
  BT_UI_NUMBER_POSITION_RIGHT_1,
  BT_UI_NUMBER_POSITION_RIGHT_2,
  BT_UI_NUMBER_POSITION_RIGHT_3,
  BT_UI_NUMBER_POSITION_RIGHT_4,
  BT_UI_NUMBER_POSITION_RIGHT_5,
  BT_UI_NUMBER_POSITION_RIGHT_6,

  // starts bottom right. if in use:
  // goes just above bottom right. if in use:
  // goes bottom left. if in use:
  // goes just above bottom left. if in use, replace bottom right
  BT_UI_NUMBER_POSITION_SHARED_BOTTOM_RIGHT_UPPER,
  // starts bottom right. if in use:
  // goes just below bottom right. if in use:
  // goes bottom left. if in use:
  // goes just below bottom left. if in use, replace bottom right
  BT_UI_NUMBER_POSITION_SHARED_BOTTOM_RIGHT_LOWER,

  BT_UI_NUMBER_POSITION_BOTTOM_CENTER,

  // starts bottom left. if in use:
  // goes just above bottom left. if in use:
  // goes bottom right. if in use:
  // goes just above bottom right. if in use, replace bottom left
  BT_UI_NUMBER_POSITION_SHARED_BOTTOM_LEFT_LOWER,

  BT_UI_NUMBER_POSITION_TOP_P1,
  BT_UI_NUMBER_POSITION_TOP_P2,
  BT_UI_NUMBER_POSITION_TOP_P3,
  BT_UI_NUMBER_POSITION_TOP_P4,
  BT_UI_NUMBER_POSITION_CENTER,
  BT_UI_NUMBER_POSITION_QUIZ_BOTTOM_RIGHT,
  BT_UI_NUMBER_POSITION_QUIZ_BOTTOM_LEFT,
  BT_UI_NUMBER_POSITION_QUIZ_BOTTOM_CENTER,
  BT_UI_NUMBER_POSITION_BOTTOM_P1,
  BT_UI_NUMBER_POSITION_BOTTOM_P4,
  BT_UI_NUMBER_POSITION_BOTTOM_P2,
  BT_UI_NUMBER_POSITION_BOTTOM_P3,
  BT_UI_NUMBER_POSITION_QUIZ_RIGHT,
  BT_UI_NUMBER_POSITION_QUIZ_LEFT,
};

enum {
  BT_UI_NUMBER_FORMAT_NORMAL,
  BT_UI_NUMBER_FORMAT_MAX,
  BT_UI_NUMBER_FORMAT_HEALTH,
  BT_UI_NUMBER_FORMAT_BUBBLES,
  BT_UI_NUMBER_FORMAT_TIME,
  BT_UI_NUMBER_FORMAT_HUGE,
  BT_UI_NUMBER_FORMAT_HUGE_MAX,
};

enum {
  BT_UI_ICONS_NONE,
  BT_UI_ICONS_BANJO_KAZOOIE,
  BT_UI_ICONS_NOTES,
  BT_UI_ICONS_BLUE_EGGS,
  BT_UI_ICONS_FIRE_EGGS,
  BT_UI_ICONS_ICE_EGGS,
  BT_UI_ICONS_GRENADE_EGGS,
  BT_UI_ICONS_CLOCKWORK_EGGS,
  BT_UI_ICONS_JIGGY,
  BT_UI_ICONS_RED_FEATHER,
  BT_UI_ICONS_GOLD_FEATHER,
  BT_UI_ICONS_YELLOW_JINJO,
  BT_UI_ICONS_HONEYCOMB_PIECE,
  BT_UI_ICONS_GLOWBO,
  BT_UI_ICONS_GRUNTY_TIMER,
  BT_UI_ICONS_UNKNOWN1, // displays as ?
  BT_UI_ICONS_BANJO_RIGHT,
  BT_UI_ICONS_MUMBO_RIGHT,
  BT_UI_ICONS_ZUBBA,
  BT_UI_ICONS_BLUE_JINJO,
  BT_UI_ICONS_RED_JINJO,
  BT_UI_ICONS_PURPLE_JINJO,
  BT_UI_ICONS_GREEN_JINJO,
  BT_UI_ICONS_ORANGE_JINJO,
  BT_UI_ICONS_WHITE_JINJO,
  BT_UI_ICONS_BLACK_JINJO,
  BT_UI_ICONS_BROWN_JINJO,
  BT_UI_ICONS_CLOCK,
  BT_UI_ICONS_UNUSED, // cant recognize icon
  BT_UI_ICONS_GRUNTY_RIGHT,
  BT_UI_ICONS_JAMJARS,
  BT_UI_ICONS_BLUE_STONY,
  BT_UI_ICONS_RED_STONY,
  BT_UI_ICONS_YELLOW_STONY,
  BT_UI_ICONS_PURPLE_STONY,
  BT_UI_ICONS_BLUE_DODGEM,
  BT_UI_ICONS_RED_DODGEM,
  BT_UI_ICONS_YELLOW_DODGEM,
  BT_UI_ICONS_PURPLE_DODGEM,
  BT_UI_ICONS_CHILLY_WILLY,
  BT_UI_ICONS_CHILLI_BILLI,
  BT_UI_ICONS_GOLD_EGGS,
  BT_UI_ICONS_TICKET,
  BT_UI_ICONS_DOUBLOON,
  BT_UI_ICONS_BEAN,
  BT_UI_ICONS_BANJO_STONY,
  BT_UI_ICONS_BANJO_DETONATOR,
  BT_UI_ICONS_BANJO_SUB,
  BT_UI_ICONS_BANJO_TREX,
  BT_UI_ICONS_BANJO_BEE,
  BT_UI_ICONS_BANJO_SNOWBALL,
  BT_UI_ICONS_BANJO_HUMBA,
  BT_UI_ICONS_UNKNOWN2, // displays as ?
  BT_UI_ICONS_GOLDEN_GOLIATH,
  BT_UI_ICONS_BANJO_WASHER_RIGHT,
  BT_UI_ICONS_CLOCKWORK_KAZOOIE,
  BT_UI_ICONS_BURGER,
  BT_UI_ICONS_QUIZ_CARD_QUESTION,
  BT_UI_ICONS_QUIZ_CARD_TT,
  BT_UI_ICONS_PAGE,
  BT_UI_ICONS_FRIES,
  BT_UI_ICONS_GOLDEN_SACRED_STATUE,
  BT_UI_ICONS_GREEN_SACRED_STATUE,
  BT_UI_ICONS_FISH,
  BT_UI_ICONS_UFO,
  BT_UI_ICONS_KING_COAL,
  BT_UI_ICONS_TERRY,
  BT_UI_ICONS_MR_PATCH,
  BT_UI_ICONS_TARGITZAN,
  BT_UI_ICONS_MINGY_JONGO,
  BT_UI_ICONS_WELDAR,
  BT_UI_ICONS_LORD_WOO_FAK_FAK,
  BT_UI_ICONS_BLUE_TWINKLIE,
  BT_UI_ICONS_GREEN_TWINKLIE,
  BT_UI_ICONS_RED_TWINKLIE,
  BT_UI_ICONS_TINTOP,
  BT_UI_ICONS_TNT,
  BT_UI_ICONS_CLINKER,
  BT_UI_ICONS_BLUE_MYSTERY_EGG,
  BT_UI_ICONS_ICE_KEY,
  BT_UI_ICONS_HAG1_BATTERY,
  BT_UI_ICONS_MEGA_GLOWBO,
  BT_UI_ICONS_BLOBBELDA,
  BT_UI_ICONS_MINGELLA,
  BT_UI_ICONS_HONEY_B,
  BT_UI_ICONS_JIGGY_WIGGY,
  BT_UI_ICONS_GRUNTY_LEFT,
  BT_UI_ICONS_BANJO_LEFT,
  BT_UI_ICONS_KAZOOIE_LEFT,
  BT_UI_ICONS_MUMBO_LEFT,
  BT_UI_ICONS_BANJO_WASHER_LEFT,
  BT_UI_ICONS_MP_BANJO_KAZOOIE_NORMAL,
  BT_UI_ICONS_MP_BANJO_KAZOOIE_GREEN,
  BT_UI_ICONS_MP_BANJO_KAZOOIE_BLUE,
  BT_UI_ICONS_MP_BANJO_KAZOOIE_YELLOW,
  BT_UI_ICONS_MP_KAZOOIE_NORMAL,
  BT_UI_ICONS_MP_KAZOOIE_GREEN,
  BT_UI_ICONS_MP_KAZOOIE_BLUE,
  BT_UI_ICONS_MP_KAZOOIE_YELLOW,
};

enum {
  BT_UI_NUMBERS_UFO,
  BT_UI_NUMBERS_BANJO_KAZOOIE,
  BT_UI_NUMBERS_KAZOOIE_BOTTOM_RIGHT,
  BT_UI_NUMBERS_PLAYER1,
  BT_UI_NUMBERS_PLAYER2,
  BT_UI_NUMBERS_PLAYER3,
  BT_UI_NUMBERS_PLAYER4,
  BT_UI_NUMBERS_OLD_KING_COAL,
  BT_UI_NUMBERS_TERRY,
  BT_UI_NUMBERS_CLOCKWORK,
  BT_UI_NUMBERS_SUB,
  BT_UI_NUMBERS_KAZOOIE_TALON_TORPEDO,
  BT_UI_NUMBERS_GRUNTY_TIMER_BOTTOM_LEFT,
  BT_UI_NUMBERS_BUBBLES,
  BT_UI_NUMBERS_GOLDEN_GOLIATH,
  BT_UI_NUMBERS_HEALTH,
  BT_UI_NUMBERS_NOTES,
  BT_UI_NUMBERS_BLUE_EGGS,
  BT_UI_NUMBERS_FIRE_EGGS,
  BT_UI_NUMBERS_ICE_EGGS,
  BT_UI_NUMBERS_GRENADE_EGGS,
  BT_UI_NUMBERS_CLOCKWORK_EGGS,
  BT_UI_NUMBERS_JIGGIES_BOTTOM_CENTER,
  BT_UI_NUMBERS_RED_FEATHERS,
  BT_UI_NUMBERS_GOLD_FEATHERS,
  BT_UI_NUMBERS_GLOWBOS,
  BT_UI_NUMBERS_HONEYCOMB_PIECE,
  BT_UI_NUMBERS_PAGE,
  BT_UI_NUMBERS_BURGER,
  BT_UI_NUMBERS_FRIES,
  BT_UI_NUMBERS_TICKET,
  BT_UI_NUMBERS_DOUBLOON,
  BT_UI_NUMBERS_GOLDEN_SACRED_STATUE,
  BT_UI_NUMBERS_WHITE_JINJO,
  BT_UI_NUMBERS_ORANGE_JINJO,
  BT_UI_NUMBERS_YELLOW_JINJO,
  BT_UI_NUMBERS_BROWN_JINJO,
  BT_UI_NUMBERS_GREEN_JINJO,
  BT_UI_NUMBERS_RED_JINJO,
  BT_UI_NUMBERS_BLUE_JINJO,
  BT_UI_NUMBERS_PURPLE_JINJO,
  BT_UI_NUMBERS_BLACK_JINJO,
  BT_UI_NUMBERS_JAMJARS,
  BT_UI_NUMBERS_JIGGIES_BOTTOM_RIGHT,
  BT_UI_NUMBERS_MR_PATCH,
  BT_UI_NUMBERS_BEANS,
  BT_UI_NUMBERS_GREEN_SACRED_STATUE,
  BT_UI_NUMBERS_UNKNOWN,
  BT_UI_NUMBERS_BLUE_TWINKLIE,
  BT_UI_NUMBERS_GREEN_TWINKLIE,
  BT_UI_NUMBERS_RED_TWINKLIE,
  BT_UI_NUMBERS_TARGITZAN,
  BT_UI_NUMBERS_GRUNTY_TIMER_BOTTOM_LEFT2,
  BT_UI_NUMBERS_ZUBBA,
  BT_UI_NUMBERS_GRUNTY_TIMER_CENTER,
  BT_UI_NUMBERS_BANJO_KAZOOIE2,
  BT_UI_NUMBERS_KAZOOIE2,
  BT_UI_NUMBERS_CHILLY_WILLY,
  BT_UI_NUMBERS_CHILLI_BILLI,
  BT_UI_NUMBERS_MINGY_JONGO,
  BT_UI_NUMBERS_SUB2,
  BT_UI_NUMBERS_WELDAR,
  BT_UI_NUMBERS_LORD_WOO_FAK_FAK,
  BT_UI_NUMBERS_ZUBBA2,
  BT_UI_NUMBERS_GRUNTY_TIMER_BOTTOM_LEFT3,
  BT_UI_NUMBERS_TINTOP,
  BT_UI_NUMBERS_TNT,
  BT_UI_NUMBERS_CLANKER,
  BT_UI_NUMBERS_GRUNTY_TIMER_BOTTOM_LEFT4,
  BT_UI_NUMBERS_GOLDEN_EGGS,
  BT_UI_NUMBERS_JIGGYWIGGY,
  BT_UI_NUMBERS_HONEYB,
  BT_UI_NUMBERS_FISH,
  BT_UI_NUMBERS_MYSTERY_EGG,
  BT_UI_NUMBERS_GRUNTY_BOTTOM_RIGHT,
  BT_UI_NUMBERS_HAG1_BATTERY,
  BT_UI_NUMBERS_ICE_KEY,
  BT_UI_NUMBERS_MEGA_GLOWBO,
  BT_UI_NUMBERS_JIGGIES_BOTTOM_RIGHT2,
  BT_UI_NUMBERS_TOT_BLOBELDA,
  BT_UI_NUMBERS_TOT_MINGELLA,
  BT_UI_NUMBERS_TOT_BANJO_KAZOOIE,
  BT_UI_NUMBERS_UNKNOWN_MUMBO,
  BT_UI_NUMBERS_UNKNOWN_HUMBA,
  BT_UI_NUMBERS_UNKNOWN_JAMJARS,
  BT_UI_NUMBERS_UNKNOWN_BANJO_KAZOOIE,
  BT_UI_NUMBERS_TOT_CARD_RIGHT,
  BT_UI_NUMBERS_TOT_CARD_LEFT,
  BT_UI_NUMBERS_TOT_GRUNTY,
};

typedef struct {
  u8 position;
  u8 icon;
  u8 format;
  u8 _unused;
  u16 amount;
  u16 max;
  float _unknown; // likely used to smoothly increment the number
} bt_ui_number_t;
#define bt_ui_numbers ((bt_ui_number_t*)0x8011AFB0)

typedef u32 (*bt_fnt_ui_show_number)(u16, u16, u16);
#define _bt_fn_ui_show_number ((bt_fnt_ui_show_number)0x800D24E8)
#define bt_fn_ui_show_number(id, amount, max) _bt_fn_ui_show_number(id+0xC0, amount, max)

typedef u32 (*bt_fnt_ui_hide_number)(u16);
#define _bt_fn_ui_hide_number ((bt_fnt_ui_hide_number)0x800D284C)
#define bt_fn_ui_hide_number(id) _bt_fn_ui_hide_number(id+0xC0)

typedef s8 (*bt_fnt_ui_showing_number)(u16, u8);
#define _bt_fn_ui_showing_number ((bt_fnt_ui_showing_number)0x800D21F0)
#define bt_fn_ui_showing_number(id, amount, max) _bt_fn_ui_showing_number(id+0xC0, amount, max)

// bt_ui_numbers[54].icon = BT_UI_ICONS_PAGE;
// bt_ui_numbers[54].position = BT_UI_NUMBER_POSITION_SHARED_BOTTOM_LEFT_LOWER;
// bt_fn_ui_show_number(54, 5, 0);

#endif // BT_UI_NUMBERS_H
