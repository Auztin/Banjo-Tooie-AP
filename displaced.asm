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
