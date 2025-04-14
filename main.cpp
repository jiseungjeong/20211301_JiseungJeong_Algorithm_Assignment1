#include <iostream>
#include <string>
#include <map>
#include <functional>
using namespace std;

typedef void (*SortFunction)(void**, int, int, string);

extern void merge_sort(void** data, int start, int end, string data_type);

extern void quick_sort(void** data, int start, int end, string data_type);

extern void selection_sort(void** data, int size, string data_type);

extern void bubble_sort(void** data, int size, string data_type);

extern void insertion_sort(void** data, int size, string data_type);

extern void heap_sort(void** data, int start, int end, string data_type);

extern void cocktail_sort(void** data, int start, int end, string data_type);

extern void intro_sort(void** data, int start, int end, string data_type);

extern void comb_sort(void** data, int start, int end, string data_type);

extern void tournament_sort(void** data, int start, int end, string data_type);

extern void tim_sort(void** data, int start, int end, string data_type);

extern void library_sort(void** data, int start, int end, string data_type);

extern void run_eval(SortFunction sort_func, const string& sort_func_name, const string& specific_file = "", int iter_num = 10);

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 4) {
        return 1;
    }

    string sort_func_name = argv[1];
    string specific_file = (argc > 2) ? argv[2] : "";
    int iter_num = (argc > 3) ? stoi(argv[3]) : 10;
    
    map<string, SortFunction> sorting_functions = {
        {"merge_sort", merge_sort},
        {"quick_sort", quick_sort},
        {"selection_sort", [](void** data, int start, int end, string data_type) {
            selection_sort(data, end - start + 1, data_type);
        }},
        {"bubble_sort", [](void** data, int start, int end, string data_type) {
            bubble_sort(data, end - start + 1, data_type);
        }},
        {"insertion_sort", [](void** data, int start, int end, string data_type) {
            insertion_sort(data, end - start + 1, data_type);
        }},
        {"heap_sort", heap_sort},
        {"cocktail_sort", cocktail_sort},
        {"intro_sort", intro_sort},
        {"comb_sort", comb_sort},
        {"tournament_sort", tournament_sort},
        {"tim_sort", tim_sort},
        {"library_sort", library_sort}
    };
    
    auto it = sorting_functions.find(sort_func_name);
    if (it != sorting_functions.end()) {
        cout << "== " << sort_func_name << " 평가 시작 ==" << endl;
        if (!specific_file.empty()) {
            cout << "특정 파일: " << specific_file << endl;
        }
        cout << "반복 횟수: " << iter_num << "회" << endl;
        
        run_eval(it->second, sort_func_name, specific_file, iter_num);
        cout << "== " << sort_func_name << " 평가 완료 ==" << endl;
    } else {
        
        return 1;
    }

    return 0;
} 