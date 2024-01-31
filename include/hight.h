#include "hight_config.h"

#ifndef _HIGHT_H
#define _HIGHT_H

void keySchedule(u8 WK[8], u8 SK[128], const u8 MK[16]);
void keySchedule_Dev(u8 WK[8], u8 SK[128], const u8 MK[16]);

static inline u8 F0(u8 byte) {
    return (byte << 1) ^ (byte << 2) ^ (byte << 7);
}

static inline u8 F1(u8 byte) {
    return (byte << 3) ^ (byte << 4) ^ (byte << 6);
}

void HIGHT_Encrypt(u8 dst[8], const u8 src[8], const u8 MK[16]);
void HIGHT_Encrypt_Dev(u8* dst, const u8* src, const u8 MK[16]);

#endif /* _HIGHT_H */