#include "hight_utils.h"

double measure_keySchedule_cycle(void (*func)(u8*, u8*, const u8*), u8* WK, u8* SK, const u8* MK) {
    u64 start, end;

    func(WK, SK, MK);
    start = rdtsc();
    for (int i = 0; i < 10000; i++) {
        func(WK, SK, MK);
    }
    end = rdtsc();
    
    return (double)((end - start) / 10000);
}

double measure_keySchedule_time(void (*func)(u8*, u8*, const u8*), u8* WK, u8* SK, const u8* MK) {
    struct timespec start, end;
    double cpu_time_used;
    const int num_runs = 1000;
    
    func(WK, SK, MK);
    clock_gettime(1, &start);
    for (int i = 0; i < num_runs; i++) {
        func(WK, SK, MK);
    }
    clock_gettime(1, &end);
    
    cpu_time_used = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return cpu_time_used / num_runs;
}