/*
 * Copyright 2023, Brandon Chaney
 */

#include <iostream>

#include "utils/container.h"
#include "utils/point.h"
#include "utils/tree.h"

int main() {
    using int_point = Point<int>;

    Stack<int_point> s{};

    for (int i = 0; i < 10; i++) {
        s.push(Point<int>(i, i));
    }
    Queue<int_point> q{};

    std::cout << "Emptying stack" << std::endl;
    while (!s.is_empty()) {
        int_point p = s.pop();
        q.enqueue(p);
        std::cout << p << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Printing queue" << std::endl;
    std::cout << q << std::endl;

    Tree<int> t{};

    for (int j = 0; j < 1000; j++) {
        t.insert(j);
    }

    std::cout << t.search(5) << std::endl;
    std::cout << t.search(999) << std::endl;
    std::cout << t.search(1000) << std::endl;
}
