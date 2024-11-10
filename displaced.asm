.align 0x08
inject_load_scene_displaced:
ADDIU SP, SP, -0x20
J 0x800A72AC
LUI T6, 0x8012

.align 0x08
inject_load_data_displaced:
ADDIU SP, SP, -0x38
SW RA, 0x0014 (SP)
J 0x800d6754
NOP
