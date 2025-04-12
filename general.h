#ifndef GENERAL_H
#define GENERAL_H

#include <string>

// 튜플 구조체 정의
struct Tuple {
    int num;
    std::string str;
};

// 두 요소 교환 함수 템플릿
template <typename T>
void swap_elements(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 두 요소 비교 함수 선언
bool compare_elements(void* a, void* b, std::string data_type);

// 최대값 구조체 정의
struct MaxValues {
    static const int INTEGER_MAX;
    static const float FLOAT_MAX;
    static const std::string STRING_MAX;
    static const int TUPLE_NUM_MAX;
    static const std::string TUPLE_STR_MAX;
};

#endif // GENERAL_H 