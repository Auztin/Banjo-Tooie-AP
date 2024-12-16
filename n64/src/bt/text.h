#ifndef BT_TEXT_H
#define BT_TEXT_H

enum {
  BT_TEXT_PLAIN,
  BT_TEXT_TEXTURE_PINK,
  BT_TEXT_GRADIENT_GOLD,
  BT_TEXT_TEXTURE_GOLD,
  BT_TEXT_TEXTURE_BLUE,
  BT_TEXT_GRADIENT_ORANGE,
  BT_TEXT_GRADIENT_GREEN,
  BT_TEXT_GRADIENT_BLUE,
  BT_TEXT_GRADIENT_YELLOW,
};

typedef struct {
  struct {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
  } color;
  u8 wobble;
  u8 _unknown1;
  u8 font; // 0 = smaller, dialog, 1 = bigger, titles
  u8 _unknown2;
  u8 _unknown3;
  u8 appearance;
  u8 _unknown4;
  u8 _unknown5;
  u8 visible;
  u8 _unknown6;
  u16 _unknown7;
  u32 _unknown8;
  float size;
} bt_text_options_t;
#define bt_text_options (*(bt_text_options_t*)0x801282C0)

typedef void (*bt_fnt_text_big_draw)(bt_draw_ctx_t*, s32 x, s32 y, char* text); // forces font = 1
#define bt_fn_text_big_draw ((bt_fnt_text_big_draw)0x80088B10)

typedef void (*bt_fnt_text_big_draw_centered)(bt_draw_ctx_t*, s32 y, char* text); // forces font = 1
#define bt_fn_text_big_draw_centered ((bt_fnt_text_big_draw_centered)0x80088B18)

typedef void (*bt_fnt_text_reset_options)(void);
#define bt_fn_text_reset_options ((bt_fnt_text_reset_options)0x80088B20)

#endif // BT_TEXT_H
