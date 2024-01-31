#include "hight.h"
#include "hight_utils.h"

void viewKeySchedule(u8* SK) {
    for (int i = 0; i < 32; i++) {
        printf("SK[%03d]||SK[%03d]||SK[%03d]||SK[%03d]: %02x%02x%02x%02x\n",
            4*i+3, 4*i+2, 4*i+1, 4*i, SK[4*i+3], SK[4*i+2], SK[4*i+1], SK[4*i]);
    }
}

int main(void) {
    // u64 start, end, start2, end2;

    u8 MK[16] = { 0xff, 0xee, 0xdd, 0xcc,
                  0xbb, 0xaa, 0x99, 0x88,
                  0x77, 0x66, 0x55, 0x44,
                  0x33, 0x22, 0x11, 0x00};
    // u8 MK[16] = { 0x00, 0x11, 0x22, 0x33,
    //               0x44, 0x55, 0x66, 0x77,
    //               0x88, 0x99, 0xaa, 0xbb,
    //               0xcc, 0xdd, 0xee, 0xff};

    u8 WK[8], SK[128];

    // start = rdtsc();
    // keySchedule(WK, SK, MK);
    // end = rdtsc();
    printf("DEV: %.3f cycles\n", measure_keySchedule_cycle(keySchedule, WK, SK, MK));
    printf("DEV: %.3f µs\n", measure_keySchedule_time(keySchedule, WK, SK, MK)*1000000);

    viewKeySchedule(SK);

    return 0;
}