#ifndef BT_DIALOG_H
#define BT_DIALOG_H

typedef struct {
  u32 textObjectPtr; // pointer to current object that keeps track of text print progress
  u32 _unknown1[15];
  u16 _unknown2;
  u16 current_id;
  u16 previous_id;
  u16 previous_id2;
  u32 _unknown3[2];
  u32 callbackPtr; // pointer to function to call when dialog is complete
} bt_dialog_t;
#define bt_dialog (*(bt_dialog_t*)0x801289D0)

typedef struct {
  u32 _unknown;
  u8 character;
  u8 size; // sizeof text
  u8 text[];
  // u8 option; // 0x05 - end dialog
} bt_dialog_data_t;

typedef u32 (*bt_fnt_load_dialog)(u16, u8, u8, u8);
#define bt_fn_load_dialog ((bt_fnt_load_dialog)0x800C0534)

#endif // BT_DIALOG_H
