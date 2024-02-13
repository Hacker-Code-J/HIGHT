#include "hight_config.h"

#ifndef _HIGHT_UTILS_H
#define _HIGHT_UTILS_H

// Read Time-Stamp Counter
static inline u64 rdtsc(void) {
    u32 lo, hi;
    
    __asm__ __volatile__ (
      "rdtsc" : "=a" (lo), "=d" (hi)
    );
    
    return ((u64)hi << 32) | lo;
}

void stringToByteArray(u8* byteArray, const char* hexString);

u64 measure_keySchedule_cycle(void (*func)(u8*, u8*, const u8*), u8* WK, u8* SK, const u8* MK);
double measure_keySchedule_time(void (*func)(u8*, u8*, const u8*), u8* WK, u8* SK, const u8* MK);

u64 measure_encryption_cycle(void (*func)(u8*, const u8*, const u8*), u8* dst, const u8* src, const u8* MK);
double measure_encryption_time(void (*func)(u8*, const u8*, const u8*), u8* dst, const u8* src, const u8* MK);

#endif /* _HIGHT_UTILS_H */