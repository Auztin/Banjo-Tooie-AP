#include "util.h"

ap_memory_t ap_memory = {0, };
ap_memory_ptr_t ap_memory_ptrs = {0, };

void util_inject(enum UTIL_INJECT type, u32 addr, u32 data, u8 addNOP) {
  u32 op = 0;
  u32 extra = 0;
  switch (type) {
    case UTIL_INJECT_RAW:
      (*(vu32*)addr) = data;
      return;
    case UTIL_INJECT_JUMP:
      op = 0x08000000;
      extra = (data & 0x01FFFFFF)/4;
      break;
    case UTIL_INJECT_FUNCTION:
      op = 0x0C000000;
      extra = (data & 0x01FFFFFF)/4;
      break;
    case UTIL_INJECT_BRANCH:
      op = 0x10000000;
      extra = (data & 0x01FFFFFF)/4-1;
      break;
    case UTIL_INJECT_RETVALUE:
      op = 0x24020000;
      extra = data & 0xFFFF;
      break;
  }
  if (op) {
    (*(vu32*)addr) = op | extra;
    if (addNOP) (*(vu32*)(addr + 4)) = 0;
  }
}
