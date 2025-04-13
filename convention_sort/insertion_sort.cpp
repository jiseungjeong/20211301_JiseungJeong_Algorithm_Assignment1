#include <string>
#include <iostream>
#include "../general.h"

using namespace std;

// 2번째 원소부터 원소의 길이까지 j로 순회하며,  i=j-1 으로 초기화 하고, i>0이고 i번째 원소가 j 원소보다 큰 동안 while로 i를 1씩 빼가며 i+1 번째 원소에 i번째 원소 대입, 그리고 while이 끝나면 i+1 번째 원소에 기존 j번째 원소 값 대입.
void insertion_sort(void** data, int size, string data_type) {
    if (size <= 1) {
        return;  
    }
    
    void* key;
    
    for (int j = 1; j < size; j++) {
        key = data[j];
        int i = j - 1;
        
        while (i >= 0 && !compare_elements(data[i], key, data_type)) {
            data[i + 1] = data[i];
            i--;
        }
        
        data[i + 1] = key;
    }
}