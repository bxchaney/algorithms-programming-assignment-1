/*
 * Copyright 2023, Brandon Chaney
 */
#pragma once

#include <cstdint>

#include "./container.hpp"
#include "./point.hpp"

class PointComparer {
 protected:
    uint32_t _comparisons;

 public:
    struct PointPair {
        Point<double> first;
        Point<double> second;
        double distance;

        PointPair() = default;
        ~PointPair() = default;

        PointPair(Point<double> first, Point<double> second, double dist)
            : first(first), second(second), distance(dist) {}

        bool operator==(const PointPair& other) {
            if (first == other.first) {
                if (second == other.second) {
                    return true;
                }
            } else if (first == other.second) {
                if (second == other.first) {
                    return true;
                }
            }
            return false;
        }

        bool operator!=(const PointPair& other) { return !(*this == other); }
    };

 protected:
    void insert_in_order(ArrayList<PointPair>* arr, PointPair p);
    ///
    /// @brief brute force comparison
    ArrayList<PointPair>* conquer(Point<double>* p, int arr_size, int m);

 public:
    PointComparer() = default;

    uint32_t comparisons() { return _comparisons; }
};
