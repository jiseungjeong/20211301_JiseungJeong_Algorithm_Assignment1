#include <string>
#include <iostream>
#include "../general.h"

using namespace std;

// 파티션 함수 (PARTITION(A, p, r))
int partition(void* data[], int p, int r, string data_type) {
    // 중간 요소를 피벗으로 선택 / 오름차순이나 내림차순 데이터에서 맨 끝을 피봇으로 선택하는 건 치명적임.
    int mid = p + (r - p) / 2;
    
    // 피벗을 마지막 위치로 이동
    void* temp = data[mid];
    data[mid] = data[r];
    data[r] = temp;
    
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
    
    temp = data[i + 1];
    data[i + 1] = data[r];
    data[r] = temp;
    
    return i + 1;
}

// 퀵소트 함수
void quick_sort(void* data[], int p, int r, string data_type) {
    if (p < r) {
        int q = partition(data, p, r, data_type);        
        quick_sort(data, p, q - 1, data_type);
        quick_sort(data, q + 1, r, data_type);
    }
}