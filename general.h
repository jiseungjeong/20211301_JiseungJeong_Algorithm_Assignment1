#ifndef GENERAL_H
#define GENERAL_H

#include <string>

struct Tuple {
    int num;
    std::string str;
};

template <typename T>
void swap_elements(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

bool compare_elements(void* a, void* b, std::string data_type);

struct MaxValues {
    static const int INTEGER_MAX;
    static const float FLOAT_MAX;
    static const std::string STRING_MAX;
    static const int TUPLE_NUM_MAX;
    static const std::string TUPLE_STR_MAX;
};

#endif 