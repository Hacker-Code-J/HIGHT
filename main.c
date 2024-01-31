#include "hight.h"

void viewKeySchedule(u8* SK) {
    for (int i = 0; i < 32; i++) {
        printf("SK[%03d]||SK[%03d]||SK[%03d]||SK[%03d]: %02x%02x%02x%02x\n",
            4*i+3, 4*i+2, 4*i+1, 4*i, SK[4*i+3], SK[4*i+2], SK[4*i+1], SK[4*i]);
    }
}

int main(void) {

    u8 MK[16] = { 0xff, 0xee, 0xdd, 0xcc,
                  0xbb, 0xaa, 0x99, 0x88,
                  0x77, 0x66, 0x55, 0x44,
                  0x33, 0x22, 0x11, 0x00};
    // u8 MK[16] = { 0x00, 0x11, 0x22, 0x33,
    //               0x44, 0x55, 0x66, 0x77,
    //               0x88, 0x99, 0xaa, 0xbb,
    //               0xcc, 0xdd, 0xee, 0xff};
    u8 WK[8], SK[128];

    // keySchedule_Dev(WK, SK, MK);
    // keySchedule_Std(WK, SK, MK);
    keySchedule(WK, SK, MK);

    viewKeySchedule(SK);

    // for (i8 i = 0; i < 8; i++) {
    //     for (i8 j = 0; j < 8; j++)
    //         printf("%d, %d: SK[%03d] <- MK[%03d] + delta[%03d]\n", i, j, 16*i+j, (j >= i ) ? (j-i) : j-i+8, 16*i+j);
    //     for (i8 j = 0; j < 8; j++)
    //         printf("%d, %d: SK[%03d] <- MK[%03d] + delta[%03d]\n", i, j, 16*i+j+8, (j >= i ) ? (j-i)+8 : (j-i+8)+8, 16*i+j+8);
    //     puts("");
    // }

    // for (i8 i = 0; i < 8; i++) {
        
    //     for (i8 j = 0; j < 8; j++) {
    //         int idx = (16 * i + j);
    //         printf("SK[%03d] <- MK[%03d] + delta[%03d]\n", idx, (j-i) & 7, 16*i+j);
    //     }
    //     for (i8 j = 0; j < 8; j++) {
    //         int idx = (16 * i + j);
    //         printf("SK[%03d] <- MK[%03d] + delta[%03d]\n", idx+8, ((j-i) & 7) + 8, 16*i+j+8);
    //     }
        

    //     puts("");
    // }

    // for (int i = 1; i < 128; i++) {
    
    //     for (int j = 0; j < 8; j++) {
    //         int idx = (16 * i + j) % 128;
    //         printf("SK[%03d] <- MK[%03d] + delta[%03d]\n", idx, (j - (i % 8)) & 7, idx);
    //     }
    //     for (int j = 0; j < 8; j++) {
    //         int idx = (16 * i + j) % 128;
    //         printf("SK[%03d] <- MK[%03d] + delta[%03d]\n", idx + 8, ((j - (i % 8)) & 7) + 8, idx + 8);
    //     }
        
    //     puts("");
    // }

    return 0;
}