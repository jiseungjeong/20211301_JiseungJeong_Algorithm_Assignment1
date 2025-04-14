#include <string>
#include <iostream>
#include <cmath>
#include "../general.h"

using namespace std;

// NULL 공간을 고려한 이진 검색
int library_binary_search(void* target, void** arr, int start, int end, string data_type) {
    if (start > end) return start;
    
    int left = start;
    int right = end;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        while (mid <= right && arr[mid] == NULL) mid++;
        if (mid > right) {
            mid = left + (right - left) / 2;
            while (mid >= left && arr[mid] == NULL) mid--;
            if (mid < left) {
                return left; 
            }
        }
        
        int cmp = compare_elements(target, arr[mid], data_type);
        
        if (cmp < 0) right = mid - 1;
        else if (cmp > 0) left = mid + 1;
        else return mid;
    }
    
    return left; 
}

// 배열의 요소들을 균등한 간격으로 재배치
void rebalance(void** arr, int cur_size, int new_size) {
    if (cur_size <= 0) return;
    
    void** temp = new void*[cur_size];
    int count = 0;
    
    for (int i = 0; i < new_size; i++) {
        if (arr[i] != NULL) {
            temp[count++] = arr[i];
            arr[i] = NULL;
        }
    }
    
    float gap = (float)new_size / count;
    for (int i = 0; i < count; i++) {
        int new_pos = (int)(i * gap);
        if (new_pos >= new_size) new_pos = new_size - 1;
        arr[new_pos] = temp[i];
    }
    
    delete[] temp;
}

// 요소를 정렬된 위치에 삽입
void library_insert(void* element, void** arr, int cur_size, int max_size, string data_type) {
    if (cur_size == 0) {
        arr[0] = element;
        return;
    }
    
    int pos = library_binary_search(element, arr, 0, cur_size - 1, data_type);
    
    if (pos < max_size && arr[pos] == NULL) {
        arr[pos] = element;
        return;
    }
    
    int i = pos;
    while (i < max_size && arr[i] != NULL) i++;
    
    if (i >= max_size) {
        for (int j = max_size - 2; j >= pos; j--) {
            arr[j + 1] = arr[j];
        }
        arr[pos] = element;
    } else {
        for (int j = i - 1; j >= pos; j--) {
            arr[j + 1] = arr[j];
        }
        arr[pos] = element;
    }
}

// 라이브러리 소트 구현
void real_library_sort(void** arr, int n, string data_type) {
    if (n <= 1) return;
    
    float epsilon = 0.5; 
    
    long long original_size = static_cast<long long>(n);
    long long expanded_size = original_size + static_cast<long long>(original_size * epsilon);
    int new_array_size = (expanded_size > INT_MAX) ? INT_MAX : static_cast<int>(expanded_size);
    
    // 확장된 임시 배열 생성 및 NULL로 초기화
    void** expanded_array = new void*[new_array_size];
    for (int i = 0; i < new_array_size; i++) {
        expanded_array[i] = NULL;
    }
    
    // 첫 번째 요소를 배열의 1/4에!
    int first_element_pos = new_array_size / 4;
    expanded_array[first_element_pos] = arr[0];
    
    // rebalancing 임계값 설정 (2, 4, 8, 16 ...)
    int rebalance_points[32]; 
    int rebalance_count = 0;
    int current_threshold = 2;
    
    while (current_threshold < n) {
        rebalance_points[rebalance_count++] = current_threshold;
        current_threshold *= 2;
    }
    
    // 나머지 요소들 삽입
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < rebalance_count; j++) {
            if (i == rebalance_points[j]) {
                rebalance(expanded_array, i, new_array_size);
                break;
            }
        }
        
        // 현재 요소를 정렬된 위치에 삽입
        library_insert(arr[i], expanded_array, i, new_array_size, data_type);
    }
    
    int result_index = 0;
    for (int i = 0; i < new_array_size && result_index < n; i++) {
        if (expanded_array[i] != NULL) {
            arr[result_index++] = expanded_array[i];
        }
    }
    
    delete[] expanded_array;
}

void library_sort(void** data, int start, int end, string data_type) {
    int size = end - start + 1;
    void** sub_array = &data[start];
    real_library_sort(sub_array, size, data_type);
}


