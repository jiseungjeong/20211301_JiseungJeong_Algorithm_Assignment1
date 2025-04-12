#include <string>

// defining sentinel values
struct MaxValues {
    static const int INTEGER_MAX;
    static const float FLOAT_MAX;
    static const std::string STRING_MAX;
    static const int TUPLE_NUM_MAX;
    static const std::string TUPLE_STR_MAX;
};

const int MaxValues::INTEGER_MAX = 2147483647;  // 2^31 - 1
const float MaxValues::FLOAT_MAX = 3.402823466e+38F;  // float 최댓값
const std::string MaxValues::STRING_MAX = "ZZZZZZZZZZZ";
const int MaxValues::TUPLE_NUM_MAX = 2147483647;
const std::string MaxValues::TUPLE_STR_MAX = "ZZZZZZZZZZZ";

struct Tuple {
    int num;
    std::string str;
};

// merge funtion
void merge(void* data[], int start, int mid, int end, std::string data_type) {
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
        bool is_left_smaller = false;
        
        if(data_type == "INT") {
            int left_val = *(int*)temp_left[left_idx];
            int right_val = *(int*)temp_right[right_idx];
            is_left_smaller = (left_val <= right_val);
        }
        else if(data_type == "FLOAT") {
            float left_val = *(float*)temp_left[left_idx];
            float right_val = *(float*)temp_right[right_idx];
            is_left_smaller = (left_val <= right_val);
        }
        else if(data_type == "STRING") {
            std::string left_val = *(std::string*)temp_left[left_idx];
            std::string right_val = *(std::string*)temp_right[right_idx];
            is_left_smaller = (left_val <= right_val);
        }
        else if(data_type == "TUPLE") {
            Tuple left_val = *(Tuple*)temp_left[left_idx];
            Tuple right_val = *(Tuple*)temp_right[right_idx];
            if(left_val.num == right_val.num) {
                is_left_smaller = (left_val.str <= right_val.str);
            } else {
                is_left_smaller = (left_val.num <= right_val.num);
            }
        }
        
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
void merge_sort(void* data[], int start, int end, std::string data_type) {
    if(start < end) {
        int mid = start + (end - start) / 2;  
        merge_sort(data, start, mid, data_type);
        merge_sort(data, mid + 1, end, data_type);
        merge(data, start, mid, end, data_type);
    }
}
