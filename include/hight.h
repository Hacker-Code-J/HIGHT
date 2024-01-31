#include "hight_config.h"

#ifndef _HIGHT_H
#define _HIGHT_H


void keySchedule(u8 WK[8], u8 SK[128], const u8 MK[16]);
void keySchedule_Std(u8 WK[8], u8 SK[128], const u8 MK[16]);
void keySchedule_Dev(u8 WK[8], u8 SK[128], const u8 MK[16]);

#endif /* _HIGHT_H */