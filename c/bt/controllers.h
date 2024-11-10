#ifndef BT_CONTROLLERS_H
#define BT_CONTROLLERS_H

typedef struct {
  u8 a : 1;
  u8 b : 1;
  u8 z : 1;
  u8 start : 1;
  u8 dup : 1;
  u8 ddown : 1;
  u8 dleft : 1;
  u8 dright : 1;

  u8 _unused : 2;
  u8 l : 1;
  u8 r : 1;
  u8 cup : 1;
  u8 cdown : 1;
  u8 cleft : 1;
  u8 cright : 1;
} bt_controller_buttons_t;

typedef struct {
  bt_controller_buttons_t held;
  bt_controller_buttons_t held_delayed;
  bt_controller_buttons_t pressed;
  bt_controller_buttons_t released;
  struct {
    f32 x;
    f32 y;
  } joystick;
} bt_controller_t;
#define bt_controllers ((bt_controller_t*)0x80079AF8)

#endif // BT_CONTROLLERS_H
