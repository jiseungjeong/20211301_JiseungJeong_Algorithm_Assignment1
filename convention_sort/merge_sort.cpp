#include <string>
#include <iostream>
#include "../general.h"

using namespace std;

// merge funtion
void merge(void* data[], int start, int mid, int end, string data_type) {
    int left_size = mid - start + 1;
    int right_size = end - mid;
    
    void* temp_left[left_size];
    void* temp_right[right_size];
    
    for(int i = 0; i < left_size; i++) {
        temp_left[i] = data[start + i];
    }
    for(int i = 0; i < right_size; i++) {
        temp_right[i] = data[mid + 1 + i];
    }
    
    int left_idx = 0, right_idx = 0, current = start;
    
    while(left_idx < left_size && right_idx < right_size) {
        bool is_left_smaller = compare_elements(temp_left[left_idx], temp_right[right_idx], data_type);
        
        if(is_left_smaller) {
            data[current] = temp_left[left_idx];
            left_idx++;
        }
        else {
            data[current] = temp_right[right_idx];
            right_idx++;
        }
        current++;
    }
    
    while(left_idx < left_size) {
        data[current] = temp_left[left_idx];
        left_idx++;
        current++;
    }
    
    while(right_idx < right_size) {
        data[current] = temp_right[right_idx];
        right_idx++;
        current++;
    }
}

// merge_sort
void merge_sort(void* data[], int start, int end, string data_type) {
    if(start < end) {
        int mid = start + (end - start) / 2;  
        merge_sort(data, start, mid, data_type);
        merge_sort(data, mid + 1, end, data_type);
        merge(data, start, mid, end, data_type);
    }
}
