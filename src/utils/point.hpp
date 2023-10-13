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
    using value_type = T;

    value_type x;
    value_type y;

    Point() = default;

    /// @brief Constructor for Point
    /// @param x 
    /// @param y 
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

    // move constructor
    Point(Point &&other) {
        this->x = other.x;
        this->y = other.y;
        other = Point();
    }

    // assignment copy
    Point &operator=(const Point &other) {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }

    // move assignment
    Point &operator=(Point &&other) {
        // returning reference to self when moving
        this->x = other.x;
        this->y = other.y;
        other = Point();
        return *this;
    }

    bool operator==(const Point &other) {
        return (x == other.x) && (y == other.y);
    }

    bool operator!=(const Point &other) { return !(*this == other); }

    friend std::ostream &operator<<(std::ostream &os, Point<T> &p) {
        return os << "( " << p.x << ", " << p.y << " )";
    }
};
