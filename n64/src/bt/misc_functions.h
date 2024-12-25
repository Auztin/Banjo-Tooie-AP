#ifndef BT_FN_INJECTED_H
#define BT_FN_INJECTED_H

typedef u32 (*bt_fnt_init)(u32);
#define bt_fn_init ((bt_fnt_init)0x80012214)

typedef u32 (*bt_fnt_loop)(void);
#define bt_fn_loop ((bt_fnt_loop)0x800123F4)

typedef u32 (*bt_fnt_load_save)(u32);
#define bt_fn_load_save ((bt_fnt_load_save)0x80087A40)

typedef u32 (*bt_fnt_object_init)(bt_object_t*, u32, u32, u32);
#define bt_fn_object_init ((bt_fnt_object_init)0x80082088)

typedef u32 (*bt_fnt_set_bit)(u32, u16, u8);
#define bt_fn_set_bit ((bt_fnt_set_bit)0x800D9F18)

typedef u32 (*bt_fnt_set_save_bit)(u16);
#define bt_fn_set_save_bit ((bt_fnt_set_save_bit)0x800DA544)

typedef u32 (*bt_fnt_get_bit)(u32, u16);
#define bt_fn_get_bit ((bt_fnt_get_bit)0x800D9E60)

typedef u32 (*bt_fnt_get_save_bit)(u16);
#define bt_fn_get_save_bit ((bt_fnt_get_save_bit)0x800DA298)

typedef bt_obj_instance_t* (*bt_fnt_spawn_prop)(u16 id, bt_s32_xyz_t* pos, u16 yrot, bt_obj_setup_t* setup);
#define bt_fn_spawn_prop ((bt_fnt_spawn_prop)0x80108C90)

typedef bool (*bt_fnt_transition_done)();
#define bt_fn_transition_done ((bt_fnt_transition_done)0x800C95D4)

typedef bool (*bt_fnt_sparkle)(bt_xyz_t*, u16 type);
#define bt_fn_sparkle ((bt_fnt_sparkle)0x800888C8)

#endif // BT_FN_INJECTED_H
