#include "hight.h"

int main(void) {
    for (i8 i = 0; i < 8; i++) {
        for (i8 j = 0; j < 8; j++)
            printf("%d, %d: SK[%03d] <- MK[%03d] + delta[%03d]\n", i, j, 16*i+j, (j >= i ) ? (j-i) : j-i+8, 16*i+j);
        for (i8 j = 0; j < 8; j++)
            printf("%d, %d: SK[%03d] <- MK[%03d] + delta[%03d]\n", i, j, 16*i+j+8, (j >= i ) ? (j-i)+8 : (j-i+8)+8, 16*i+j+8);
        puts("");
    }
    return 0;
}