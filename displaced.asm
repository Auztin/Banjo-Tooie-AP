.align 0x08
inject_load_scene_displaced:
ADDIU SP, SP, -0x20
J 0x800A72AC
LUI T6, 0x8012

.align 0x08
inject_load_data_displaced:
ADDIU SP, SP, -0x38
SW RA, 0x0014 (SP)
J 0x800D6754
NOP

.align 0x08
main_bt_paused_displaced:
ADDIU SP, SP, -0x08
SW RA, 0x0000 (SP)
JAL main_bt_paused
NOP
LW RA, 0x0000 (SP)
ADDIU SP, SP, 0x08
LW A2, 0x001C (SP)
ADDIU A1, R0, 0x0007
JR RA
NOP

.align 0x08
main_bt_file_select_cursor_displaced:
ADDIU SP, SP, -0x18
SW RA, 0x0000 (SP)
SW AT, 0x0004 (SP)
SW A0, 0x0008 (SP)
SW A1, 0x000C (SP)
SW A2, 0x0010 (SP)
SW A3, 0x0014 (SP)
JAL main_bt_file_select_cursor
NOP
LW AT, 0x0000 (SP)
LW RA, 0x0004 (SP)
LW A0, 0x0008 (SP)
LW A1, 0x000C (SP)
LW A2, 0x0010 (SP)
LW A3, 0x0014 (SP)
ADDIU SP, SP, 0x18
BNEZ V0, .+16
NOP
JR RA
NOP
; displaced code
ADDIU SP, SP, -0x28
SW S0, 0x0018 (SP)
JR AT
ADDIU AT, R0, 0x0007

.align 0x08
main_bt_file_select_bottom_text_displaced:
ADDIU SP, SP, -0x18
SW RA, 0x0000 (SP)
SW AT, 0x0004 (SP)
SW A0, 0x0008 (SP)
SW A1, 0x000C (SP)
SW A2, 0x0010 (SP)
SW A3, 0x0014 (SP)
JAL main_bt_file_select_bottom_text
NOP
LW AT, 0x0000 (SP)
LW RA, 0x0004 (SP)
LW A0, 0x0008 (SP)
LW A1, 0x000C (SP)
LW A2, 0x0010 (SP)
LW A3, 0x0014 (SP)
ADDIU SP, SP, 0x18
BNEZ V0, .+16
NOP
JR RA
NOP
; displaced code
ADDIU SP, SP, -0x30
SW S2, 0x001C (SP)
JR AT
OR S2, A0, R0
