#include <string>
#include <iostream>
#include "../general.h"

using namespace std;

// data의 맨 앞에서부터 시작해서 i가 증가하며 순회함.
// 매 바퀴마다 i와 i+1를 비교, 앞의 원소가 더 크면 두 원소를 swap
// 다음 바퀴부터는 맨 뒤 원소를 제외하고 반복,
// 위 과정을 j를 반복 변수로 하는 반복문으로 감싸 총 n-1번 반복해 완전 정렬을 만드는 정렬 방식.
bool optimize = true;

void bubble_sort(void** data, int size, string data_type) {
    for (int j = 0; j < size - 1; j++) {
        bool swapped = false;
        
        for (int i = 0; i < size - j - 1; i++) {
            // 앞 원소가 더 크면 swap
            if (!compare_elements(data[i], data[i+1], data_type)) {
                void* temp = data[i];
                data[i] = data[i+1];
                data[i+1] = temp;
                swapped = true;
            }
        }
        
        // optimize를 사용하면, 교환 없으면 정렬 종료, optimize 없으면, 그냥 항상 N^2
        if (optimize && !swapped) {
            break;
        }
    }
}