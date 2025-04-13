#include <string>
#include <iostream>
#include "../general.h"

using namespace std;


static bool optimize = true;  

// cocktial_shaker_sort(arr, n)은 길이가 n인 arr를 정렬하는 함수임. 양방향 버블소트
void cocktail_shaker_sort(void** data, int size, string data_type) {
    if (size <= 1) {
        return;
    }

    int left_end = size - 1;
    int right_end = 0;
    
    for (int k = 0; k < size / 2; k++) {
        bool swap_flag = false; 
        
        // 왼쪽 -> 오른쪽 진행 
        int left_start = 0; 
        for (int i = left_start; i < left_end; i++) {
            if (!compare_elements(data[i], data[i+1], data_type)) {
                void* tmp = data[i];
                data[i] = data[i+1];
                data[i+1] = tmp;
                
                swap_flag = true;  
            }
        }
        left_end--;  
        
        if (optimize && !swap_flag) {
            break;
        }
        
        // 오른쪽 -> 왼쪽 진행
        int right_start = size - 1;  
        for (int i = right_start; i > right_end; i--) {
            if (!compare_elements(data[i-1], data[i], data_type)) {
                void* tmp = data[i-1]; 
                data[i-1] = data[i];
                data[i] = tmp;
                
                swap_flag = true; 
            }
        }
        right_end++; 
        
        if (optimize && !swap_flag) {
            break;
        }
    }
}

void cocktail_sort(void** data, int start, int end, string data_type) {
    int size = end - start + 1;
    void** sub_data = &data[start];
    cocktail_shaker_sort(sub_data, size, data_type);
}