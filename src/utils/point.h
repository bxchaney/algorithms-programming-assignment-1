/*
 * Copyright 2023 Brandon Chaney
 */
#pragma once
#include <iostream>

/*
 * This class is used to store 2-dimensional ordered pairs and includes some
 * conveniece methods for string formatting. Later on, we assumes that the
 * parameter type of Point is ordered or partially ordered, this is that the
 * type supports the operators: >, <, <=, >=, ==
 */
template <typename T>
class Point {
 public:
    typedef T value_type;
    typedef T *pointer_type;
    typedef T &reference;
    typedef const T &const_reference;

    value_type x;
    value_type y;

    Point(value_type x, value_type y) {
        this->x = x;
        this->y = y;
    }

    ~Point() = default;

    // copy constructor
    Point(const Point &other) {
        this->x = other.x;
        this->y = other.y;
    }

    Point operator=(const Point &other) {
        this->x = other.x;
        this->y = other.y;
    }

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, Point<U> &p) {
        return os << "( " << p.x << ", " << p.y << " )";
    }
};
