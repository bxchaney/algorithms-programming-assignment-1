/*
 * Copyright 2023, Brandon Chaney
 */

#include <time.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "utils/container.hpp"
#include "utils/mergesort.hpp"
#include "utils/point.hpp"
#include "utils/point_reader.h"
#include "utils/tree.hpp"

void test_hash() {
    uint16_t x{65535};
    uint16_t y{65535};
    uint32_t hash{get_hash(x, y)};
    std::cout << hash << std::endl;
}

bool cmp(int* a, int* b) { return *a <= *b; }

bool call_cmp(int a, int b, bool (*cmp)(int*, int*)) { return cmp(&a, &b); }

int read_input(int argc, char** argv) {
    if (argc < 3) {
        return -1;
    }

    // assuming that the filepath to the datafile is the first parameter
    std::ifstream ifs{argv[1]};
    if (!ifs.is_open()) {
        std::cout << "Could not open file."
                  << " Please ensure that the first parameter is a valid "
                  << "relative filepath." << std::endl;
        return -1;
    }

    Queue<Point<uint16_t>> q{};

    read_points(ifs, &q);

    Point<uint16_t>* p{q.to_array()};

    std::cout << "Read input set. There are " << q.size() << " unique points"
              << std::endl;

    delete p;
    return 0;
}

int main(int argc, char** argv) {
    using int_point = Point<int>;

    Stack<int_point> s{};

    for (int i = 0; i < 10; i++) {
        s.push(Point<int>(i, i));
    }
    Queue<int_point> q{};

    std::cout << "Emptying stack" << std::endl;
    while (!s.is_empty()) {
        int_point p{s.pop()};
        q.enqueue(p);
        std::cout << "queued p" << std::endl;
        std::cout << p << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Printing queue" << std::endl;
    std::cout << q << std::endl;

    Point<int>* arr{q.to_array()};
    int q_size = q.size();

    std::cout << "printing arr contents" << std::endl;
    for (int i = 0; i < q_size; i++) {
        std::cout << arr[i] << std::endl;
    }

    Tree<int> t{};

    for (int j = 0; j < 1000; j++) {
        t.insert(j);
    }

    std::cout << t.search(5) << std::endl;
    std::cout << t.search(999) << std::endl;
    std::cout << t.search(1000) << std::endl;
    test_hash();

    srand(time(0));

    int* int_arr{new int[20]};
    for (int i = 0; i < 20; i++) {
        int_arr[i] = (rand() % 50);
    }
    std::cout << "random array: ";
    for (int i = 0; i < 20; i++) {
        std::cout << int_arr[i] << " ";
    }
    std::cout << std::endl;
    merge_sort<int>(int_arr, 0, 19, &cmp);
    std::cout << "sorted array: ";
    for (int i = 0; i < 20; i++) {
        std::cout << int_arr[i] << " ";
    }
    std::cout << std::endl;

    int a{4};
    int b{5};
    std::cout << call_cmp(a, b, &cmp) << std::endl;

    ArrayList<int> arr_list{5};

    arr_list.insert(0, 1);
    arr_list.insert(0, 2);
    arr_list.insert(0, 3);
    arr_list.insert(0, 4);
    arr_list.insert(0, 5);

    std::cout << "Array list contents: " << std::endl;
    for (int i = 0; i < (int)arr_list.size(); i++) {
        std::cout << arr_list[i] << std::endl;
    }

    read_input(argc, argv);
}
