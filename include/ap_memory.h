#ifndef AP_MEMORY_H
#define AP_MEMORY_H

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

#include "ap_memory/n64.h"
#include "ap_memory/pc.h"

typedef struct {
  ap_memory_pc_t pc; // only the pc program should write data here
  ap_memory_n64_t n64; // only the n64 should write data here
} ap_memory_t;

#endif // AP_MEMORY_H