#pragma once

// Automatically generated using gen_constants.py

#include <n64/types.h>

typedef enum {
	APS_INVALID = -1,
	APS_DISCONNECTED = 0,
	APS_CONNECTING = 1,
	APS_CONNECTED = 2,
	APS_PINGED = 4,
	APS_MAX = 5,
} ap_state_t;
