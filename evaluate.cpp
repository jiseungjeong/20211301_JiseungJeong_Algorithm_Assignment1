#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>
#include <algorithm>
#include <memory>
#include <iomanip>
#include <map>
#include <numeric>
#include <thread>
#include "general.h"

#ifdef __APPLE__
#include <mach/mach.h>
#include <sys/resource.h>
#endif

using namespace std;

// 파일 데이터 파싱
vector<void*> parse_data(const string& file_name, const string& type) {
    vector<void*> data;
    ifstream file(file_name);
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        if (type == "INT") {
            int* value = new int(stoi(line));
            data.push_back(value);
        }
        else if (type == "FLOAT") {
            float* value = new float(stof(line));
            data.push_back(value);
        }
        else if (type == "STRING") {
            string* value = new string(line);
            data.push_back(value);
        }
        else if (type == "TUPLE") {
            size_t comma_pos = line.find(',');
            int num = stoi(line.substr(0, comma_pos));
            string str = line.substr(comma_pos + 1);
            Tuple* value = new Tuple{num, str};
            data.push_back(value);
        }
    }

    file.close();
    return data;
}

// 메모리 사용량 측정 함수 개선
// 참조 링크: https://developer.apple.com/forums/thread/105088
size_t get_current_memory_usage() {
#ifdef __APPLE__
    task_vm_info_data_t vmInfo;
    mach_msg_type_number_t count = TASK_VM_INFO_COUNT;
    kern_return_t kerr = task_info(mach_task_self(), TASK_VM_INFO, (task_info_t)&vmInfo, &count);
    
    if (kerr == KERN_SUCCESS) {
        return vmInfo.phys_footprint;
    }
#endif
    return 0;
}

// 동적으로 메모리 사용량을 추적하는 클래스
class MemoryTracker {
private:
    size_t baseline;
    size_t peak_usage;
    bool tracking;
    
public:
    MemoryTracker() : baseline(0), peak_usage(0), tracking(false) {}
    
    void start() {
        baseline = get_current_memory_usage();
        peak_usage = 0;
        tracking = true;
    }
    
    void update() {
        if (!tracking) return;
        
        size_t current = get_current_memory_usage();
        if (current > baseline) {
            size_t current_usage = current - baseline;
            if (current_usage > peak_usage) {
                peak_usage = current_usage;
            }
        }
    }
    
    void stop() {
        tracking = false;
    }
    
    size_t getPeakUsage() const {
        return peak_usage;
    }
};

void memory_tracking_sort_wrapper(
    void (*sort_func)(void**, int, int, string),
    void** data, 
    int left, 
    int right, 
    string type,
    MemoryTracker& tracker
) {
    tracker.start();
    
    bool should_monitor = true;
    thread monitor_thread([&]() {
        while (should_monitor) {
            tracker.update();
            this_thread::sleep_for(chrono::milliseconds(1)); // 1ms 간격으로 모니터링
        }
    });
    
    sort_func(data, left, right, type);
    
    should_monitor = false;
    if (monitor_thread.joinable()) {
        monitor_thread.join();
    }
    
    tracker.stop();
}

map<string, double> evaluate_sorting_function(
    void (*sort_func)(void**, int, int, string), 
    const vector<void*>& data, 
    const string& data_type,
    int iter_num)
{
    vector<double> execution_times;
    vector<double> memory_usages;
    
    for (int i = 0; i < iter_num; ++i) {
        vector<void*> test_data;
        for (auto ptr : data) {
            if (data_type == "INT") {
                test_data.push_back(new int(*(int*)ptr));
            }
            else if (data_type == "FLOAT") {
                test_data.push_back(new float(*(float*)ptr));
            }
            else if (data_type == "STRING") {
                test_data.push_back(new string(*(string*)ptr));
            }
            else if (data_type == "TUPLE") {
                Tuple* original = (Tuple*)ptr;
                test_data.push_back(new Tuple{original->num, original->str});
            }
        }
        
        MemoryTracker memTracker;
        
        auto start_time = chrono::high_resolution_clock::now();
        
        memory_tracking_sort_wrapper(sort_func, test_data.data(), 0, test_data.size() - 1, data_type, memTracker);
        
        auto end_time = chrono::high_resolution_clock::now();
        
        execution_times.push_back(chrono::duration<double>(end_time - start_time).count());
        memory_usages.push_back(static_cast<double>(memTracker.getPeakUsage()));
        
        for (void* ptr : test_data) {
            if (data_type == "INT") delete static_cast<int*>(ptr);
            else if (data_type == "FLOAT") delete static_cast<float*>(ptr);
            else if (data_type == "STRING") delete static_cast<string*>(ptr);
            else if (data_type == "TUPLE") delete static_cast<Tuple*>(ptr);
        }
    }

    double avg_time = 0.0;
    double avg_memory = 0.0;
    
    if (!execution_times.empty()) {
        avg_time = accumulate(execution_times.begin(), execution_times.end(), 0.0) / execution_times.size();
    }
    
    if (!memory_usages.empty()) {
        avg_memory = accumulate(memory_usages.begin(), memory_usages.end(), 0.0) / memory_usages.size() / 1024.0;
    }

    cout << fixed << setprecision(6);
    cout << " - 평균 실행 시간: " << avg_time << " 초" << endl;
    cout << " - 평균 메모리 사용량: " << avg_memory << " KB" << endl;
    cout << " - 반복 횟수: " << iter_num << "회" << endl;
    
    size_t data_size = data.size();
    cout << " - 데이터 크기: " << data_size << " 항목" << endl;
    
    return {
        {"data_size", static_cast<double>(data_size)},
        {"avg_time", avg_time},
        {"avg_memory", avg_memory}
    };
}

void run_eval(void (*sort_func)(void**, int, int, string), const string& sort_func_name, const string& specific_file, int iter_num) {
    
    vector<tuple<string, string, string>> data_config = {
        {"int_ascending_sorted_", "int", "INT"},
        {"int_descending_sorted_", "int", "INT"},
        {"int_random_", "int", "INT"},
        /*
        {"float_ascending_sorted_", "float", "FLOAT"},
        {"float_descending_sorted_", "float", "FLOAT"},
        {"float_random_", "float", "FLOAT"},
        {"string_random_", "string", "STRING"},
        */
        {"tuple_num_descending_char_ascending_data_", "tuple", "TUPLE"},
        {"10per_", "int", "INT"},
        {"50per_", "int", "INT"},
        {"90per_", "int", "INT"}
    };

    struct ResultStruct {
        string file_name;
        double data_size;
        double avg_time;
        double avg_memory;
    };
    vector<ResultStruct> all_results;
    
    string results_csv_file = sort_func_name + "_evaluation_results.csv";
    

    // 특정 파일명에서 경로 부분 제거 , 경로 파싱
    string specific_filename = specific_file;
    if (!specific_file.empty()) {
        size_t last_slash = specific_file.find_last_of("/\\");
        if (last_slash != string::npos) {
            specific_filename = specific_file.substr(last_slash + 1);
        }
    }
    
    for (const auto& [prefix, data_type, sentinel_type] : data_config) {
        for (const auto& entry : filesystem::directory_iterator("./data")) {
            string file_path = entry.path().string();
            string file_name = entry.path().filename().string();
            
            if (!specific_file.empty() && file_name != specific_filename) {
                continue;
            }
            
            if (file_name.find(prefix) != string::npos || specific_file == file_name) {
                cout << "\n평가 중: " << file_name << endl;
                
                try {
                    vector<void*> data = parse_data(file_path, sentinel_type);
                    if (data.empty()) {
                        cout << "data empty!!" << endl;
                        continue;
                    }
                    
                    map<string, double> result = evaluate_sorting_function(sort_func, data, sentinel_type, iter_num);
                    
                    ResultStruct entry = {
                        file_name,
                        result.at("data_size"),
                        result.at("avg_time"),
                        result.at("avg_memory")
                    };
                    all_results.push_back(entry);
                    
                    // 메모리 해제
                    for (void* ptr : data) {
                        if (sentinel_type == "INT") delete static_cast<int*>(ptr);
                        else if (sentinel_type == "FLOAT") delete static_cast<float*>(ptr);
                        else if (sentinel_type == "STRING") delete static_cast<string*>(ptr);
                        else if (sentinel_type == "TUPLE") delete static_cast<Tuple*>(ptr);
                    }
                    
                    if (!specific_file.empty()) {
                        break;
                    }
                }
                catch (const exception& e) {
                    cerr << "오류: " << e.what() << endl;
                }
            }
        }
        
        if (!specific_file.empty() && !all_results.empty()) {
            break;
        }
    }
    
    // CSV 파일 결과 저장
    ofstream csv_file(results_csv_file);
    if (csv_file.is_open()) {
        csv_file << "file_name,data_size,avg_time,avg_memory\n";
        
        for (const auto& entry : all_results) {
            csv_file << entry.file_name << ","
                        << entry.data_size << ","
                        << entry.avg_time << ","
                        << entry.avg_memory << "\n";
        }
        
        csv_file.close();
        cout << "\n결과 " << results_csv_file << "에 저장" << endl;
    }

} 