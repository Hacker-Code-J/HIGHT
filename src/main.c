#include "hight.h"
#include "hight_utils.h"

void viewKeySchedule(u8* SK) {
    for (int i = 0; i < 32; i++) {
        printf("SK[%03d]||SK[%03d]||SK[%03d]||SK[%03d]: %02x%02x%02x%02x\n",
            4*i+3, 4*i+2, 4*i+1, 4*i, SK[4*i+3], SK[4*i+2], SK[4*i+1], SK[4*i]);
    }
}

int main(void) {

    // u8 MK[16] = { 0xff, 0xee, 0xdd, 0xcc,
    //               0xbb, 0xaa, 0x99, 0x88,
    //               0x77, 0x66, 0x55, 0x44,
    //               0x33, 0x22, 0x11, 0x00};

    u8 MK[16] = { 0x00, 0x11, 0x22, 0x33,
                  0x44, 0x55, 0x66, 0x77,
                  0x88, 0x99, 0xaa, 0xbb,
                  0xcc, 0xdd, 0xee, 0xff };

    // u8 WK[8], SK[128];

    u8 PT[8] = { 0x77, 0x66, 0x55, 0x44,
                 0x33, 0x22, 0x11, 0x00 };
    printf("  PT | ");
    for (int i = 7; i >= 0; i--) {
        printf("%02x:", PT[i]);
    }
    printf("\n");

    u8 CT[8] = { 0x00, };
    u8 myPT[8] = { 0x00, };

    HIGHT_Encrypt(CT, PT, MK);

    printf("myCT | ");
    for (int i = 7; i >= 0; i--) {
        printf("%02x:", CT[i]);
    }
    printf("\n");

    // printf("ENC: %lu cycles\n", measure_encryption_cycle(HIGHT_Encrypt, CT, PT, MK));
    // printf("ENC: %.3f µs\n", measure_encryption_time(HIGHT_Encrypt, CT, PT, MK)*1000000);

    HIGHT_Decrypt(myPT, CT, MK);

    printf("myPT | ");
    for (int i = 7; i >= 0; i--) {
        printf("%02x:", myPT[i]);
    }
    printf("\n");

    // for (int i = 0; i < 8; i++) {
    //     for (int j = 0; j < 8; j++)
    //         printf("SK[%d] = MK[%d] + delta[%d]\n", 16 * i + j + 0, ((j - i) & 7) + 0, 16 * i + j + 0);
    //     for (int j = 0; j < 8; j++)
    //         printf("SK[%d] = MK[%d] + delta[%d]\n", 16 * i + j + 8, ((j - i) & 7) + 8, 16 * i + j + 8);
    // }

    // puts("");

    // for (int i = 7; i >= 0; i--) {
    //     for (int j = 7; j >= 0; j--)
    //         printf("SK[%d] = MK[%d] + delta[%d]\n", 127 - (16 * i + j + 8), ((j - i) & 7) + 8, 16 * i + j + 8);
    //     for (int j = 7; j >= 0; j--)
    //         printf("SK[%d] = MK[%d] + delta[%d]\n", 127 - (16 * i + j + 0), ((j - i) & 7) + 0, 16 * i + j + 0);
    // }

    return 0;
}