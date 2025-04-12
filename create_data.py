import random
import os
import string

random.seed(1)

SIZES = {
    "1K": 1000,
    "3K": 3000,
    "10K": 10000,
    "30K": 30000,
    "100K": 100000,
    "300K": 300000,
    "1M": 1000000,
}


def check_output_dir(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)


# 실행 시간, 메모리 소비, stability 평가
# 각 테스트는 최소 10번 연산하고 실행 시간 평균을 기록해놓아야 함.


## 정수 오름차순 정렬 데이터 생성 함수 (출력 형태는 목표 디렉토리의 int_ascending_sorted_1K.txt/ 3K/10K/30K/100K/300K/1M)
def create_int_ascending_sorted(output_dir="data"):
    check_output_dir(output_dir)
    for size_name, size in SIZES.items():
        data = list(range(1, size + 1))
        filename = f"{output_dir}/int_ascending_sorted_{size_name}.txt"
        with open(filename, "w") as f:
            for num in data:
                f.write(f"{num}\n")
        print(f"Created: {filename}")


## 정수 내림차순 정렬 데이터 생성 함수 (출력 형태는 목표 디렉토리의 int_descending_sorted_1K.txt/ 3k/10K/30K/100K/300K/1M)
def create_int_descending_sorted(output_dir="data"):
    check_output_dir(output_dir)
    for size_name, size in SIZES.items():
        data = list(range(size, 0, -1))
        filename = f"{output_dir}/int_descending_sorted_{size_name}.txt"
        with open(filename, "w") as f:
            for num in data:
                f.write(f"{num}\n")
        print(f"Created: {filename}")


## 정수 랜덤 데이터 생성 (출력 형태는 목표 디렉토리의 int_random_1K.txt/ 3k/10K/30K/100K/300K/1M) - 랜덤시드 고정
def create_int_random(output_dir="data"):
    check_output_dir(output_dir)
    for size_name, size in SIZES.items():
        data = [
            random.randint(1, size * 10) for _ in range(size)
        ]  # the range is about from 1 to size*10
        filename = f"{output_dir}/int_random_{size_name}.txt"
        with open(filename, "w") as f:
            for num in data:
                f.write(f"{num}\n")
        print(f"Created: {filename}")


## 부분 정렬 데이터 생성 (10per_10K.txt/100K/1M, 50per_10K.txt/100K/1M, 90per_10K.txt/100K/1M)
def create_partially_sorted(percent, output_dir="data"):
    check_output_dir(output_dir)
    target_sizes = ["10K", "100K", "1M"]
    for size_name, size in SIZES.items():
        if size_name not in target_sizes:
            continue

        data = list(range(1, size + 1))
        sorted_cnt = int(size * percent / 100)

        unsorted_part = data[sorted_cnt:]
        random.shuffle(unsorted_part)

        data = data[:sorted_cnt] + unsorted_part

        filename = f"{output_dir}/{percent}per_{size_name}.txt"
        with open(filename, "w") as f:
            for num in data:
                f.write(f"{num}\n")

        print(f"Created: {filename}")


## 실수 데이터 생성 (출력 형태는 목표 디렉토리의 float_ascending_sorted_100K.txt)
def create_float_ascending_data_100K(output_dir="data"):
    check_output_dir(output_dir)
    data = [round(random.uniform(0, 10000), 2) for _ in range(1000000)]
    data.sort()

    filename = f"{output_dir}/float_ascending_sorted_100K.txt"
    with open(filename, "w") as f:
        for num in data:
            f.write(f"{num}\n")

    print(f"Created: {filename}")


def create_float_descending_data_100K(output_dir="data"):
    check_output_dir(output_dir)
    data = [round(random.uniform(0, 10000), 2) for _ in range(1000000)]
    data.sort(reverse=True)

    filename = f"{output_dir}/float_descending_sorted_100K.txt"
    with open(filename, "w") as f:
        for num in data:
            f.write(f"{num}\n")

    print(f"Created: {filename}")


def create_float_random_data_100K(output_dir="data"):
    check_output_dir(output_dir)
    data = [round(random.uniform(0, 10000), 2) for _ in range(1000000)]

    filename = f"{output_dir}/float_random_100K.txt"
    with open(filename, "w") as f:
        for num in data:
            f.write(f"{num}\n")

    print(f"Created: {filename}")


## 문자열 데이터 생성 (출력 형태는 목표 디렉토리의 string_ascending_sorted_100K.txt)
def create_string_random_data_100K(output_dir="data"):
    check_output_dir(output_dir)
    data = [
        "".join(random.choices(string.ascii_letters, k=random.randint(5, 10)))
        for _ in range(1000000)
    ]

    filename = f"{output_dir}/string_random_100K.txt"
    with open(filename, "w") as f:
        for num in data:
            f.write(f"{num}\n")

    print(f"Created: {filename}")


## 2-size tuple 데이터 생성 (출력 형태는 목표 디렉토리의 tuple_descending_sorted_1K.txt) (4,A), (4,B)와 같은 데이터 넣고 stability 분석
# 숫자에 대해 내림차순, 문자에 대해 오름차순
def create_tuple_num_descending_char_ascending_data_1K(output_dir="data"):
    check_output_dir(output_dir)
    data = []
    for i in range(1, 1000 // 5, 1):
        for char in string.ascii_uppercase[:5]:
            data.append((i, char))

    while len(data) < 1000:
        num = random.randint(1, 1000 // 5)
        char = random.choice(string.ascii_uppercase[:5])
        data.append((num, char))

    data.sort(key=lambda item: (-item[0], item[1]))

    filename = f"{output_dir}/tuple_num_descending_char_ascending_data_1K.txt"
    with open(filename, "w") as f:
        for i in data:
            f.write(f"{i[0]}, {i[1]}\n")

    print(f"Created: {filename}")


## reverse로 기존 데이터 뒤에서 부터 입력받는 파서 만들기


def main():
    create_int_ascending_sorted()
    create_int_descending_sorted()
    create_int_random()
    create_partially_sorted(10)
    create_partially_sorted(50)
    create_partially_sorted(90)
    create_float_ascending_data_100K()
    create_float_descending_data_100K()
    create_float_random_data_100K()
    create_string_random_data_100K()
    create_tuple_num_descending_char_ascending_data_1K()
    print("Every data creation is completed.")


main()
