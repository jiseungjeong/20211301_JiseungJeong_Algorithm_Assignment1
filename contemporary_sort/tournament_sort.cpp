#include <string>
#include <iostream>
#include "../general.h"

using namespace std;

// tournament_sort(arr)
// arr에 대해 각 (값, 인덱스)가 나오도록 전처리
// arr의 길이가 n이라면, n 이상의 최소 2의 제곱수 찾고, 그 길이의 배열에 기존 arr들어가게 하고, 뒷부분 남는 부분은 general.h의 sentinel_value로 꽉채우기.(leaf 생성)
// 그리고 그 어레이의 길이를 2배해서, 기존 값들은 뒷부분에 위치하게 하고, 앞부분은 빈 값으로 나두기.
// 맨 뒤에서(전체 길이-1 과 전체 길이-2) 부터 비교하면서, 부모 위치((인덱스-1)/2)에 더 작은 값 넣기. depth 변수도 하나 만들어서, depth마다 2의 depth 승 개의 노드가 있을테니, 그에 대해서만 루트 구하는 걸 계속 반복하면 됨. (뒤에서 앞으로)
// 이렇게 뒤에서 부터 순환하며 전체 어레이의 맨 앞(루트)이 채워질때 까지 반복.
// 루트의 값은 result array에 append하고, 루트의 인덱스를 참조해서, 해당 리프 노드에 센티널 밸류 넣고, 해당 노드가 영향을 끼친 부모 노드들도 전부 업데이트(비교 하면서 작은 값이 부모로 오게)
// 위 과정을 반복하면서 result array는 정렬된 상태를 유지하고, 마지막 루트가 센티널이 될때까지 반복함.

// 인덱스와 값 쌍으로 토너먼트 노드 표현
struct TournamentNode {
    void* value;
    int original_i;
};

int next_power_of_two(int n) {
    int power = 1;
    while (power < n) {
        power *= 2;
    }
    return power;
}

// 센티널 값 생성 함수
void* create_sentinel(const string& data_type) {
    if (data_type == "INT") {
        return new int(MaxValues::INTEGER_MAX);
    } else if (data_type == "FLOAT") {
        return new float(MaxValues::FLOAT_MAX);
    } else if (data_type == "STRING") {
        return new string(MaxValues::STRING_MAX);
    } else if (data_type == "TUPLE") {
        Tuple* t = new Tuple();
        t->num = MaxValues::TUPLE_NUM_MAX;
        t->str = MaxValues::TUPLE_STR_MAX;
        return t;
    }
    return nullptr;
}

// 트리 경로 업데이트 함수
void update_tournament(TournamentNode* tree, int leaf_i, int size, const string& data_type) {
    int i = leaf_i;
    
    while (i > 0) {
        int parent = (i - 1) / 2;
        int sibling;
        
        if (i % 2 == 0) { // right case
            sibling = i - 1;
        } else {  // left case
            sibling = i + 1;
            if (sibling >= size) { 
                tree[parent] = tree[i];
                i = parent;
                continue;
            }
        }
        
        
        bool is_smaller_than_sibling = compare_elements(
            tree[i].value, 
            tree[sibling].value, 
            data_type
        );
        
        // min value to parent
        tree[parent] = is_smaller_than_sibling ? tree[i] : tree[sibling];
        
        i = parent;
    }
}

void real_tournament_sort(void** data, int size, string data_type) {
    if (size <= 1) return;  
    
    int leaf_size = next_power_of_two(size);
    
    int tree_size = 2 * leaf_size - 1;
    
    int leaf_start = leaf_size - 1;
    
    TournamentNode* tournament_tree = new TournamentNode[tree_size];
    
    for (int i = 0; i < size; i++) {
        tournament_tree[leaf_start + i].value = data[i];
        tournament_tree[leaf_start + i].original_i = i;
    }
    
    // 남은 리프 노드에 센티널 값 채우기
    for (int i = size; i < leaf_size; i++) {
        tournament_tree[leaf_start + i].value = create_sentinel(data_type);
        tournament_tree[leaf_start + i].original_i = -1;  
    }
    
    for (int i = leaf_start - 1; i >= 0; i--) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        bool left_small = compare_elements(
            tournament_tree[left].value,
            tournament_tree[right].value,
            data_type
        );
        
        tournament_tree[i] = left_small ? tournament_tree[left] : tournament_tree[right];
    }
    
    void** result = new void*[size];
    
    for (int i = 0; i < size; i++) {
        result[i] = tournament_tree[0].value;
        
        int root_original_i = tournament_tree[0].original_i;
        
        int leaf_i = leaf_start + root_original_i;
        
        tournament_tree[leaf_i].value = create_sentinel(data_type);
        tournament_tree[leaf_i].original_i = -1;
        
        update_tournament(tournament_tree, leaf_i, tree_size, data_type);
    }
    
    for (int i = 0; i < size; i++) {
        data[i] = result[i];
    }
    
    delete[] tournament_tree;
    delete[] result;
}

void tournament_sort(void** data, int start, int end, string data_type) {
    int size = end - start + 1;
    void** sub_array = &data[start];
    real_tournament_sort(sub_array, size, data_type);
}