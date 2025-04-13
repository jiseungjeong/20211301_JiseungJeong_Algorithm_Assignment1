#include "general.h"
#include <string>

using namespace std;

// 최대값 상수 정의
const int MaxValues::INTEGER_MAX = 2147483647;  // 2^31 - 1
const float MaxValues::FLOAT_MAX = 3.402823466e+38F;  // float 최댓값
const string MaxValues::STRING_MAX = "ZZZZZZZZZZZ";
const int MaxValues::TUPLE_NUM_MAX = 2147483647;
const string MaxValues::TUPLE_STR_MAX = "ZZZZZZZZZZZ";

// 두 요소 비교 함수 구현
bool compare_elements(void* a, void* b, string data_type) {
    if (data_type == "INT") {
        return *static_cast<int*>(a) <= *static_cast<int*>(b);
    }
    else if (data_type == "FLOAT") {
        return *static_cast<float*>(a) <= *static_cast<float*>(b);
    }
    else if (data_type == "STRING") {
        return *static_cast<string*>(a) <= *static_cast<string*>(b);
    }
    else if (data_type == "TUPLE") {
        Tuple* t1 = static_cast<Tuple*>(a);
        Tuple* t2 = static_cast<Tuple*>(b);
        
        // 튜플 비교: num 내림차순, 같으면 str 오름차순 for eval stability
        if (t1->num != t2->num) {
            return t1->num >= t2->num; 
        } else {
            return t1->str <= t2->str; 
        }
    }
    return false;
} 