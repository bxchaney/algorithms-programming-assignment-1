#pragma once

#include <cstdint>

#include "./container.hpp"
#include "./point.hpp"

struct PointPair {
    Point<uint16_t> first;
    Point<uint16_t> second;
    double distance;

    PointPair() = default;

    PointPair(Point<uint16_t> first, Point<uint16_t> second, double dist)
        : first(first), second(second), distance(dist) {}
};

bool cmp(PointPair* a, PointPair* b);

void calc_distances(Queue<PointPair>* queue, Point<uint16_t>* point_arr,
                    int arr_size);

void get_closest_points(Point<uint16_t>* point_arr, int arr_size);
