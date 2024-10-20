#include "util.h"

void util_inject(enum UTIL_INJECT type, u32 addr, u32 data, u8 addNOP) {
  u32 op = 0;
  u32 extra = 0;
  switch (type) {
    case UTIL_INJECT_NOP:
      (*(vu32*)addr) = 0;
      return;
    case UTIL_INJECT_RETVALUE:
      op = 0x24020000;
      extra = data & 0xFFFF;
      break;
    case UTIL_INJECT_JUMP:
      op = 0x08000000;
      extra = (data & 0x01FFFFFF)/4;
      break;
    case UTIL_INJECT_FUNCTION:
      op = 0x0C000000;
      extra = (data & 0x01FFFFFF)/4;
      break;
  }
  if (op) {
    (*(vu32*)addr) = op | extra;
    if (addNOP) (*(vu32*)(addr + 4)) = 0;
  }
}
