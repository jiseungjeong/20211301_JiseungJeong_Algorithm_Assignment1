#include <string>
#include <iostream>
#include "../general.h"

using namespace std;

// 데이터 배열에서 인덱스 i로 처음부터 맨끝까지 순회 하면서 
// 이 중 반복문으로 인덱스 j는 i 이후부터 맨 끝까지 순회하면서, 그 중 가장 작은 값(general.h의 compare_element 함수를 활용해서 비교)은 min_num 변수에 담고,  맨끝까지 가면 i번째 위치의 원소와 swap!
void selection_sort(void** data, int size, string data_type) {
    for (int i = 0; i < size - 1; i++) {
        int min_i = i;
        
        for (int j = i + 1; j < size; j++) {
            if (!compare_elements(data[min_i], data[j], data_type)) {
                min_i = j;
            }
        }
        
        // 최소값이 바뀌었다면 swap
        if (min_i != i) {
            void* temp = data[i];
            data[i] = data[min_i];
            data[min_i] = temp;
        }
    }
}