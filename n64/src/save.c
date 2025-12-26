#include "save.h"
#include "util.h"
#include "ap/ap.h"
#include "ap/version.h"
#include "n64/dma.h"
#include <string.h>

save_t save = {0,};

void save_init_random() {
	u32 ap_seed[5];
	memcpy(ap_seed, ap.seed, 20);
	typedef union {
		u8 bytes[4];
		u32 i;
	} seed_t;
	seed_t seed;
	for (int i = 0; i < 4; i++) {
		csrand(ap_seed[i]);
		seed.bytes[i] = crand()%256;
	}
	csrand(ap_seed[4]);
	for (int i = 0; i < ap.team; i++) crand();
	int iters = crand()%129;
	for (int i = 0; i < ap.slot; i++) crand();
	iters += crand()%128;
	csrand(seed.i);
	for (; iters; iters--) crand();
}

void save_init() {
	const u32 size = sizeof(save.data);
	dma_read_raw_async(&save.data, 0x08000000, size);
	if (save.data.magic_start != SAVE_MAGIC || save.data.magic_end != SAVE_MAGIC || save.data.version != AP_VERSION.as_int) {
		memset(&save.data, 0, size);
		save.data.magic_start = SAVE_MAGIC;
		save.data.magic_end = SAVE_MAGIC;
		save.data.version = AP_VERSION.as_int;
		save.dirty = true;
		save_sram_write();
	}
}

void save_sram_write() {
	if (!save.dirty) return;
	const u32 size = sizeof(save.data);
	dma_write_raw_async(&save.data, 0x08000000, size);
	save.dirty = false;
}

u32 save_eeprom_read(UNUSED u32 _unused, u32 offset, u32 *ramAddr) {
	offset *= 2;
	ramAddr[0] = save.data.eeprom[offset];
	ramAddr[1] = save.data.eeprom[offset+1];
	return 0;
}

u32 save_eeprom_write(UNUSED u32 _unused, u32 offset, u32 *ramAddr) {
	offset *= 2;
	save.data.eeprom[offset] = ramAddr[0];
	save.data.eeprom[offset+1] = ramAddr[1];
	save.dirty = true;
	return 0;
}
