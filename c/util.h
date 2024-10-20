#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define s8 int8_t
#define s16 int16_t
#define s32 int32_t
#define s64 int64_t

#define vu8 volatile uint8_t
#define vu16 volatile uint16_t
#define vu32 volatile uint32_t
#define vu64 volatile uint64_t

#define vs8 volatile int8_t
#define vs16 volatile int16_t
#define vs32 volatile int32_t
#define vs64 volatile int64_t

#define f32 float
#define f64 double

enum UTIL_INJECT {
  UTIL_INJECT_NOP,
  UTIL_INJECT_RETVALUE,
  UTIL_INJECT_JUMP,
  UTIL_INJECT_FUNCTION,
};

void util_inject(enum UTIL_INJECT type, u32 addr, u32 data, u8 addNOP);

#endif // UTIL_H
