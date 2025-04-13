#include <string>
#include <iostream>
#include "../general.h"

using namespace std;

// comb_sort(arr)은 gap 변수에 어레이 사이즈를 저장하고, shrink 변수에 1.3을 저장하고, swap_flag를 트루로 설정함.
// while 루프로 gap이 1보다 크거나 swap_flag가 트루인 동안
// gap은 1, int(gap/shrink) 중 맥스 값으로 할당. swap_flag를 false로 할당.
// 0부터 (arr 길이 -gap-1) 까지 i로 순회하며, i번째 원소가 i+gap 번째 원소보다 크면, 둘이 swap, 그리고 swap_flag 트루 할당.
// 이렇게 while 루프 반복.

void real_comb_sort(void** data, int len, string type) {
    int gap = len;  
    float shrink = 1.3;  
    bool swap_flag = true; 

    if (len <= 1) {
        return;
    }
    
    while (gap > 1 || swap_flag) {
        gap = (gap > 1) ? int(gap / shrink) : 1;
        swap_flag = false;
        
        for (int i = 0; i < len - gap; i++) {
            int j = i + gap;
            if (!compare_elements(data[i], data[j], type)) {
                void* tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
                swap_flag = true;
            }
        }
    }
}

void comb_sort(void** arr, int start, int end, string data_type) {
    int size = end - start + 1;
    void** subarray = &arr[start];
    real_comb_sort(subarray, size, data_type);
}