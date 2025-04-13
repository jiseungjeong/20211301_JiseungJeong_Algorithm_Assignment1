#include <string>
#include <iostream>
#include "../general.h"

using namespace std;

extern void heap_sort(void** data, int start, int end, string data_type);
extern int partition(void* data[], int p, int r, string data_type);
extern void insertion_sort(void** data, int size, string data_type);

int cal_log2(int n) {
    int log = 0;
    while (n > 1) {
        n = int(n / 2); 
        log++;
    }
    return log;
}

// 인트로 소트
void introsort(void** data, int start, int end, int depth_limit, string data_type) {
    int length = end - start + 1;
    
    // 배열 크기가 작으면 삽입 정렬 
    if (length < 16) {
        void** array_start = &data[start];
        insertion_sort(array_start, length, data_type);
        return;
    }
    
    // depth_limit 0이면 heap 정렬
    if (depth_limit == 0) {
        heap_sort(data, start, end, data_type);
        return;
    }
    
    // 그 외에는 퀵정렬
    int p = partition(data, start, end, data_type);
    
    if (p - 1 > start) {
        introsort(data, start, p - 1, depth_limit - 1, data_type);
    }
    
    if (end > p + 1) {
        introsort(data, p + 1, end, depth_limit - 1, data_type);
    }
}


void intro_sort(void** data, int start, int end, string data_type) {
    if (start >= end) {
        return;
    }
    
    int n = end - start + 1;
    int max_depth = 2 * cal_log2(n);
    introsort(data, start, end, max_depth, data_type);
}