CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# 디렉토리 설정
CONV_DIR = convention_sort
CONT_DIR = contemporary-sort

MAIN_SRCS = main.cpp evaluate.cpp general.cpp
CONV_SRCS = $(wildcard $(CONV_DIR)/*.cpp)
CONT_SRCS = $(wildcard $(CONT_DIR)/*.cpp)

ALL_SRCS = $(MAIN_SRCS) $(CONV_SRCS) $(CONT_SRCS)

OBJS = $(ALL_SRCS:.cpp=.o)

all: sort_evaluate

sort_evaluate: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

compile: 
	$(CXX) $(CXXFLAGS) $(MAIN_SRCS) $(CONV_SRCS) $(CONT_SRCS) -o sort_evaluate
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

SORT ?= merge_sort
eval: compile
	./sort_evaluate $(SORT)

clean:
	rm -f $(OBJS) sort_evaluate $(SORT)_evaluation_results.csv

clean_csv:
	rm -f *_evaluation_results.csv

.PHONY: all clean eval compile clean_csv 