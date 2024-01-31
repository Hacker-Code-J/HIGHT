#include "hight.h"

void keySchedule(u8 WK[8], u8 SK[128], const u8 MK[16]) {
    u8 buffer[16], temp;
    memcpy(buffer, MK, 16);

    // Generate whitening keys using direct assignments instead of loop
    WK[0] = buffer[12];
    WK[1] = buffer[13];
    WK[2] = buffer[14];
    WK[3] = buffer[15];
    WK[4] = buffer[0];
    WK[5] = buffer[1];
    WK[6] = buffer[2];
    WK[7] = buffer[3];

    // Initialize s array with direct assignments
    u8 s[134] = {0, 1, 0, 1, 1, 0, 1};

    u8 delta = (s[6] << 6) | (s[5] << 5) | (s[4] << 4) |
               (s[3] << 3) | (s[2] << 2) | (s[1] << 1) | s[0];

    for (u8 i = 0; i < 128; ++i) {
        if (i > 0) {
            s[i + 6] = s[i + 2] ^ s[i - 1]; // XOR operation
            delta = (s[i + 6] << 6) | (s[i + 5] << 5) | (s[i + 4] << 4) |
                    (s[i + 3] << 3) | (s[i + 2] << 2) | (s[i + 1] << 1) | s[i];
        }

        u8 n = i % 16;
        if (n == 0 && i > 15) {
            // Simplified rotations with bitwise operations and avoiding memcpy/memmove
            temp = buffer[7];
            for (u8 j = 7; j > 0; j--) buffer[j] = buffer[j - 1];
            buffer[0] = temp;

            temp = buffer[15];
            for (u8 j = 15; j > 8; j--) buffer[j] = buffer[j - 1];
            buffer[8] = temp;
        }
        
        SK[i] = buffer[n] + delta;
    }
}

void keySchedule_Std(u8 WK[8], u8 SK[128], const u8 MK[16]) {
    u8 i, j;
    
    // Generate whitening keys
    for (i = 0; i < 4; i++)
        WK[i] = MK[i + 12];
    for (i = 4; i < 8; i++)
        WK[i] = MK[i - 4];

    // Initialize s array
    u8 s[134]; // 7 + 127
    u8 delta[128];
    s[0] = 0; s[1] = 1; s[2] = 0; s[3] = 1; s[4] = 1; s[5] = 0; s[6] = 1;

    delta[0] = (0  << 7) |
                (s[6] << 6) |
                (s[5] << 5) |
                (s[4] << 4) |
                (s[3] << 3) |
                (s[2] << 2) |
                (s[1] << 1) |
                (s[0] << 0);

    // Generate δ array and subkeys
    for (i = 1; i < 128; i++) {
        s[i + 6] = s[i + 2] ^ s[i - 1]; // XOR operation for s_{i+6}
        delta[i] = (0     << 7) |
                (s[i + 6] << 6) |
                (s[i + 5] << 5) |
                (s[i + 4] << 4) |
                (s[i + 3] << 3) |
                (s[i + 2] << 2) |
                (s[i + 1] << 1) |
                (s[i + 0] << 0);
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            SK[16 * i + j + 0] = MK[((j - i) & 7) + 0] + delta[16 * i + j + 0];
        for (j = 0; j < 8; j++)
            SK[16 * i + j + 8] = MK[((j - i) & 7) + 8] + delta[16 * i + j + 8];
    }
}

void keySchedule_Dev(u8 WK[8], u8 SK[128], const u8 MK[16]) {
    u8 i = 0;
    u8 n = 0;
    
    u8 buffer[16], temp[8];
    memcpy(buffer, MK, 16);
    for (int k = 0; k < 16; k++)
        printf("%02x:", buffer[k]);
    printf("\n");

    // Generate whitening keys
    for (i = 0; i < 4; i++)
        WK[i] = MK[i + 12];
    for (i = 4; i < 8; i++)
        WK[i] = MK[i - 4];

    // Initialize s array
    u8 s[134]; // 7 + 127
    s[0] = 0; s[1] = 1; s[2] = 0; s[3] = 1; s[4] = 1; s[5] = 0; s[6] = 1;

    u8 delta = (0 << 7) |
               (s[6] << 6) |
               (s[5] << 5) |
               (s[4] << 4) |
               (s[3] << 3) |
               (s[2] << 2) |
               (s[1] << 1) |
               (s[0] << 0);

    // Generate δ array and subkeys
    for (i = 0; i < 128; i++) {
        if (i > 0) {
            s[i + 6] = s[i + 2] ^ s[i - 1]; // XOR operation for s_{i+6}
            delta = (0 << 7) |
                    (s[i + 6] << 6) |
                    (s[i + 5] << 5) |
                    (s[i + 4] << 4) |
                    (s[i + 3] << 3) |
                    (s[i + 2] << 2) |
                    (s[i + 1] << 1) |
                    (s[i + 0] << 0);
        }
        // printf("%u: %02x\n", i, delta);

        n = i / 16;
        u8 shift = 1;
        if (i % 16 == 0 && n > 0) {
            // // Rotate the first 8-byte segment
            // memcpy(temp, buffer + n, 8 - n);
            // memmove(buffer + 8 - n, buffer, n);
            // memcpy(buffer, temp, 8 - n);

            // Right rotate the first 8-byte segment
            memcpy(temp, buffer + 8 - shift, shift); // Store the last n bytes of the first segment
            memmove(buffer + shift, buffer, 8 - shift); // Shift the first (8-n) bytes to the right
            memcpy(buffer, temp, shift); // Move the last n bytes to the beginning


            printf("\n\n%d\nFRONT; %u:\n", n, i);
            for (int k = 0; k < 16; k++) {
                if (k == 8) printf(" | ");
                printf("%02x:", buffer[k]);
            }
            printf("\n==============================================================\n");

            // // Rotate the second 8-byte segment
            // memcpy(temp, buffer + 8 + n, 8 - n);
            // memmove(buffer + 16 - n, buffer + 8, n);
            // memcpy(buffer + 8, temp, 8 - n);

            // Right rotate the second 8-byte segment
            memcpy(temp, buffer + 16 - shift, shift); // Store the last n bytes of the second segment
            memmove(buffer + 8 + shift, buffer + 8, 8 - shift); // Shift the first (8-n) bytes of the second segment to the right
            memcpy(buffer + 8, temp, shift); // Move the last n bytes to the beginning of the second segment

            printf(" BACK; %u:\n", i);
            for (int k = 0; k < 16; k++) {
                if (k == 8) printf(" | ");
                printf("%02x:", buffer[k]);
            }
            printf("\n==============================================================\n");
        }
        
        SK[i] = buffer[i % 16] + delta;
        printf("SK[%03d] = %02x = %02x + %02x\n", i, SK[i], buffer[i % 16], delta);

    }
}