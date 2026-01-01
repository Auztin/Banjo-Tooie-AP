.align 0x08
bt_scenes_load:
ADDIU SP, SP, -0x20
J 0x800A72AC
LUI T6, 0x8012

.align 0x08
bt_data_load:
LUI V0, 0x8013
J 0x800D5B3C
ADDIU V0, V0, 0xB7E6

.align 0x08
bt_data_get:
ADDIU SP, SP, -0x38
J 0x800D6754
SW RA, 0x0014 (SP)

.align 0x08
bt_gfx_draw_objects:
ADDIU SP, SP, -0x38
J 0x800EB524
SW S0, 0x0018 (SP)

.align 0x08
bt_gfx_draw_hud:
ADDIU SP, SP, -0x38
J 0x800FA510
LUI T6, 0x8013

.align 0x08
bt_objects_spawn:
ADDIU SP, SP, -0x28
J 0x80108C98
SW RA, 0x001C (SP)

.align 0x08
bt_zoombox_new:
LW V0, 0x80087B08
J _to32
ADDIU V1, R0, 0x0001

.align 0x08
bt_zoombox_dialog_options:
LW V0, 0x80087B80
J _to32
ADDIU V1, R0, 0x0003

.align 0x08
bt_file_select_update:
LW V0, objects_jump
ADDIU SP, SP, -0x38
JR V0
SW RA, 0x001C (SP)

.align 0x08
bt_file_select_cursor:
LW V0, objects_jump
ADDIU SP, SP, -0x28
JR V0
SW S0, 0x0018 (SP)

.align 0x08
bt_file_select_kazooie_set_text:
LW V0, objects_jump
ADDIU SP, SP, -0x20
JR V0
SW RA, 0x001C (SP)

.align 0x08
bt_file_select_banjo_update:
LW V0, objects_jump
ADDIU SP, SP, -0x40
JR V0
SW RA, 0x0024 (SP)

.align 0x08
_file_select_banjo_set_text:
LA V0, file_select_banjo_set_text
J _to64
ADDIU V1, R0, 0x0001

.align 0x08
bt_file_select_banjo_set_text:
LA V0, @@displaced
J _to32
ADDIU V1, R0, 0x0001
@@displaced:
LW V0, objects_jump
ADDIU SP, SP, -0x30
JR V0
SW S2, 0x001C (SP)
