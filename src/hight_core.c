#include "hight.h"

void keySchedule(u8 whiteningKeys[8], u8 subKeys[128], const u8 masterKey[16]) {
    // Generate whitening keys
    for (int i = 0; i < 4; i++)
        whiteningKeys[i] = masterKey[i + 12];
    for (int i = 4; i < 8; i++)
        whiteningKeys[i] = masterKey[i - 4];

    // Initialize s array
    u8 s[134]; // 7 + 127
    s[0] = 0; s[1] = 1; s[2] = 0; s[3] = 1; s[4] = 1; s[5] = 0; s[6] = 1;

    // Generate δ array and subkeys
    for (int i = 1; i <= 127; i++) {
        s[i + 6] = s[i + 2] ^ s[i - 1];
        uint8_t delta = 0;
        for (int j = 0; j < 7; j++) {
            delta |= s[i + 6 - j] << j;
        }

        for (int j = 0; j < 8; j++) {
            int index = (16 * i + j) % 128;
            if (j < 8) {
                subKeys[index] = masterKey[(j - i) & 7] + delta;
            } else {
                subKeys[index] = masterKey[((j - i) & 7) + 8] + delta;
            }
        }
    }
}