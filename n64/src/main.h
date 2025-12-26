#pragma once

#include "n64/types.h"

typedef struct {
	bool is_emulator;
	u32 last_c0_count;
	u32 delta; // milliseconds since last frame
} main_t;
extern main_t main;

void main_init();
void main_loop();
void main_goal_completed();
