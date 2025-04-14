#include <string>
#include <iostream>
#include <algorithm>
#include "../general.h"

using namespace std;

// tim_sort(arr)는 merge 소트와 insertion 소트의 결합.
// merge_sort와 insertion_sort 외부에서 가져와서 사용할거임.
// arr의 길이를 변수 n에 할당. run에는 32 할당, i=0부터, run 단위로 전부 insertion_sort!
// merge_size 변수에 run 할당
// merge_size가 n보다 작은동안 계속, merge_partition_size를 2배씩 늘려가며 그 partition에 대해 merge_sort!

extern void insertion_sort(void** data, int size, string data_type);
extern void merge(void* data[], int start, int mid, int end, string data_type);

void real_tim_sort(void** arr, int n, string data_type) {
    if (n <= 1) return;
    
    const int RUN = 32;
    
    for (int i = 0; i < n; i += RUN) {
        int end = (i + RUN - 1) < (n - 1) ? (i + RUN - 1) : (n - 1);
        int size = end - i + 1;
        insertion_sort(arr + i, size, data_type);
    }

    int merge_size = RUN;
    while (merge_size < n) {
        for (int left = 0; left < n; left += 2 * merge_size) {
            int mid = min(left + merge_size - 1, n - 1);
            int right = min(left + 2 * merge_size - 1, n - 1);
            if (mid < right) {
                merge(arr, left, mid, right, data_type);
            }
        }
        merge_size = merge_size * 2;
    }
}

void tim_sort(void** data, int start, int end, string data_type) {
    int size = end - start + 1;
    void** sub_array = &data[start];
    real_tim_sort(sub_array, size, data_type);
}

