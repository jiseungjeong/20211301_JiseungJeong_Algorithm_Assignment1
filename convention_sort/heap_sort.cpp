#include <string>
#include <iostream>
#include "../general.h"

using namespace std;


int left_child(int i) {
    return 2 * i + 1;
}
int right_child(int i) {
    return 2 * i + 2;
}

void max_heapify(void** data, int heap_size, int i, string data_type) {
    int left_i = left_child(i);
    int right_i = right_child(i);
    int largest = i;
    
    if (left_i < heap_size && !compare_elements(data[left_i], data[i], data_type)) {
        largest = left_i;
    }

    if (right_i < heap_size && !compare_elements(data[right_i], data[largest], data_type)) {
        largest = right_i;
    }
    
    if (largest != i) {
        // swap!
        void* temp = data[i];
        data[i] = data[largest];
        data[largest] = temp;
        
        max_heapify(data, heap_size, largest, data_type);
    }
}

void build_max_heap(void** data, int size, string data_type) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        max_heapify(data, size, i, data_type);
    }
}

void heap_sort(void** data, int start, int end, string data_type) {
    int size = end - start + 1;

    if (size <= 1) {
        return;
    }
    
    void** sub_data = &data[start];
    
    build_max_heap(sub_data, size, data_type);
    
    for (int i = size - 1; i > 0; i--) {
        void* temp = sub_data[0];
        sub_data[0] = sub_data[i];
        sub_data[i] = temp;
        
        max_heapify(sub_data, i, 0, data_type);
    }
}