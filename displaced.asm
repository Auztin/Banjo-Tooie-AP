.align 0x08
inject_draw_objects_displaced:
ADDIU SP, SP, -0x38
J 0x800EB524
SW S0, 0x0018 (SP)

.align 0x08
inject_draw_hud_displaced:
ADDIU SP, SP, -0x38
J 0x800FA510
LUI T6, 0x8013

.align 0x08
inject_spawn_prop_displaced:
ADDIU SP, SP, -0x28
J 0x80108C98
SW RA, 0x001C (SP)

.align 0x08
bt_fn_zoombox_new:
ADDIU V0, R0, 0x0000
J 0x80087B08
SW V0, 0x0010 (SP)

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
main_bt_pause_state_change_displaced:
ADDIU SP, SP, -0x30
SD RA, 0x0000 (SP)
SD AT, 0x0008 (SP)
SD A0, 0x0010 (SP)
SD A1, 0x0018 (SP)
SD A2, 0x0020 (SP)
SD A3, 0x0028 (SP)
JAL main_bt_pause_state_change
NOP
LD AT, 0x0000 (SP)
LD RA, 0x0008 (SP)
LD A0, 0x0010 (SP)
LD A1, 0x0018 (SP)
LD A2, 0x0020 (SP)
LD A3, 0x0028 (SP)
ADDIU SP, SP, 0x30
BNEZ V0, .+16
NOP
JR RA
NOP
; displaced code
ADDIU SP, SP, -0x30
SW S0, 0x0018 (SP)
JR AT
SLTIU AT, A3, 0x0006

.align 0x08
main_bt_pause_load_menu_displaced:
ADDIU SP, SP, -0x30
SD RA, 0x0000 (SP)
SD AT, 0x0008 (SP)
SD A0, 0x0010 (SP)
SD A1, 0x0018 (SP)
SD A2, 0x0020 (SP)
SD A3, 0x0028 (SP)
JAL main_bt_pause_load_menu
NOP
LD AT, 0x0000 (SP)
LD RA, 0x0008 (SP)
LD A0, 0x0010 (SP)
LD A1, 0x0018 (SP)
LD A2, 0x0020 (SP)
LD A3, 0x0028 (SP)
ADDIU SP, SP, 0x30
BNEZ V0, .+16
NOP
JR RA
NOP
; displaced code
ADDIU SP, SP, -0x20
SW RA, 0x001C (SP)
JR AT
SW S0, 0x0018 (SP)

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
