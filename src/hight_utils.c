#include "hight_utils.h"

void stringToByteArray(u8* byteArray, const char* hexString) {
    size_t length = strlen(hexString);
    for (size_t i = 0; i < length; i += 2) {
        sscanf(&hexString[i], "%2hhx", &byteArray[(length / 2 - 1) - (i / 2)]);
    }
}

u64 measure_keySchedule_cycle(void (*func)(u8*, u8*, const u8*), u8* WK, u8* SK, const u8* MK) {
    u64 start, end;
    const u64 num_runs = 10000;
    func(WK, SK, MK);

    start = rdtsc();
    for (int i = 0; i < num_runs; i++)
        func(WK, SK, MK);
    end = rdtsc();
    
    return (end - start) / num_runs;
}

double measure_keySchedule_time(void (*func)(u8*, u8*, const u8*), u8* WK, u8* SK, const u8* MK) {
    struct timespec start, end;
    double cpu_time_used;
    const double num_runs = 10000;
    
    func(WK, SK, MK);
    clock_gettime(1, &start);
    for (int i = 0; i < num_runs; i++) {
        func(WK, SK, MK);
    }
    clock_gettime(1, &end);
    
    cpu_time_used = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return cpu_time_used / num_runs;
}

u64 measure_encryption_cycle(void (*func)(u8*, const u8*, const u8*), u8* dst, const u8* src, const u8* MK) {
    u64 start, end;
    const u64 num_runs = 10000;
    func(dst, src, MK);

    start = rdtsc();
    for (int i = 0; i < num_runs; i++)
        func(dst, src, MK);
    end = rdtsc();
    
    return (end - start) / num_runs;
}

double measure_encryption_time(void (*func)(u8*, const u8*, const u8*), u8* dst, const u8* src, const u8* MK) {
    struct timespec start, end;
    double cpu_time_used;
    const double num_runs = 10000;
    
    func(dst, src, MK);
    clock_gettime(1, &start);
    for (int i = 0; i < num_runs; i++) {
        func(dst, src, MK);
    }
    clock_gettime(1, &end);
    
    cpu_time_used = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return cpu_time_used / num_runs;
}