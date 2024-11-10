#ifndef UTIL_H
#define UTIL_H

#include <ap_memory.h>

extern ap_memory_t ap_memory;

typedef struct {
  u32 pc;
  u32 pc_settings;
  u32 pc_items;
  u32 n64;
  u32 n64_saves_primary;
  u32 n64_saves_secondary;
} ap_memory_ptr_t;
extern ap_memory_ptr_t ap_memory_ptrs;
extern ap_memory_ptr_t* AP_MEMORY_PTR;

enum UTIL_INJECT {
  UTIL_INJECT_RAW,
  UTIL_INJECT_JUMP,
  UTIL_INJECT_FUNCTION,
  UTIL_INJECT_BRANCH,
  UTIL_INJECT_RETVALUE,
};

void util_inject(enum UTIL_INJECT type, u32 addr, u32 data, u8 addNOP);

#endif // UTIL_H
