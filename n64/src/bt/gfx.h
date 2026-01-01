#pragma once

#include <n64/types.h>

typedef struct {

} bt_draw_ctx_t;

typedef struct {
	u16 red;
	u16 green;
	u16 blue;
} bt_color_t;

typedef struct {
	float x;
	float y;
	float z;
} bt_xyz_t;

typedef struct {
	s16 x;
	s16 y;
	s16 z;
} bt_s16_xyz_t;

typedef struct {
	s32 x;
	s32 y;
	s32 z;
} bt_s32_xyz_t;

typedef enum {
	BT_GFX_OBJECTS_ENTITIES,
	BT_GFX_OBJECTS_PROPS,
	BT_GFX_OBJECTS_UI1,
	BT_GFX_OBJECTS_UI2,
	BT_GFX_OBJECTS_UNK1,
	BT_GFX_OBJECTS_SHADOWS,
	BT_GFX_OBJECTS_UNK2,
	BT_GFX_OBJECTS_MAX,
} bt_gfx_objects_t;

void bt_gfx_draw_objects(bt_gfx_objects_t type, bt_draw_ctx_t *draw_ctx);
void bt_gfx_draw_hud(bt_draw_ctx_t *draw_ctx);

void gfx_draw_objects(bt_gfx_objects_t type, bt_draw_ctx_t *draw_ctx);
void gfx_draw_hud(bt_draw_ctx_t *draw_ctx);
