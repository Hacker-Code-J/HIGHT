#include "hight_config.h"

#ifndef _HIGHT_H
#define _HIGHT_H

void keySchedule(u8 whiteningKeys[8], u8 subKeys[128], const u8 master_key[16]);

#endif /* _HIGHT_H */