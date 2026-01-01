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

