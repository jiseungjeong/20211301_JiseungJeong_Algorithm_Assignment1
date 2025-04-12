#include <string>
#include <iostream>
#include "../general.h"

// 파티션 함수 (PARTITION(A, p, r))
int partition(void* data[], int p, int r, std::string data_type) {
    void* x = data[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        if (compare_elements(data[j], x, data_type)) {
            i++;
            void* temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    
    void* temp = data[i + 1];
    data[i + 1] = data[r];
    data[r] = temp;
    
    return i + 1;
}

void quick_sort(void* data[], int p, int r, std::string data_type) {
    if (p < r) {
        int q = partition(data, p, r, data_type);        
        quick_sort(data, p, q - 1, data_type);
        quick_sort(data, q + 1, r, data_type);
    }
}