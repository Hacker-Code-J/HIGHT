#include "hight_config.h"

#ifndef _HIGHT_H
#define _HIGHT_H

void encKeySchedule(u8 enc_WK[8], u8 enc_SK[128], const u8 MK[16]);
void decKeySchedule(u8 dec_WK[8], u8 dec_SK[128], const u8 MK[16]);
void keySchedule_Dev(u8 WK[8], u8 SK[128], const u8 MK[16]);

static inline u8 ROTL(u8 byte, u8 shift) {
    return (byte << shift) | (byte >> (8 - shift));
}

static inline u8 F0(u8 byte) {
    return ROTL(byte, 1) ^ ROTL(byte, 2) ^ ROTL(byte, 7);
}

static inline u8 F1(u8 byte) {
    return ROTL(byte, 3) ^ ROTL(byte, 4) ^ ROTL(byte, 6);
}

void HIGHT_Encrypt(u8 dst[8], const u8 src[8], const u8 MK[16]);
void HIGHT_Decrypt(u8 dst[8], const u8 src[8], const u8 MK[16]);
void HIGHT_Encrypt_Dev(u8 dst[8], const u8 src[8], const u8 MK[16]);

#endif /* _HIGHT_H */