#pragma once

// Automatically generated using gen_constants.py

#include <n64/types.h>

typedef enum {
	APC_INVALID = -1,
	APC_NONE = 0,
	APC_HANDSHAKE = 1,
	APC_PING = 2,
	APC_PONG = 3,
	APC_STATE = 4,
	APC_INFO = 5,
	APC_OPTIONS = 6,
	APC_LOCATIONS = 7,
	APC_ITEMS = 8,
	APC_MESSAGE = 9,
	APC_DEATH_LINK = 10,
	APC_TAG_LINK = 11,
	APC_MAX = 12,
} ap_cmd_t;
