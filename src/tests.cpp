/*
 * Copyright 2023, Brandon Chaney
 */

#include <time.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "utils/mergesort.hpp"
#include "utils/container.hpp"
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

int main() {
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
}
