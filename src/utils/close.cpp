/*
 * Copyright 2023, Brandon Chaney
 */

#include "./close.h"

#include <math.h>

#include <cstdint>

#include "./container.hpp"
#include "./mergesort.hpp"
#include "./point.hpp"

bool cmp(PointPair* a, PointPair* b) { return a->distance <= b->distance; }

void calc_distances(Queue<PointPair>* queue, Point<uint16_t>* point_arr,
                    int arr_size) {
    for (int i = 0; i < (arr_size - 1); i++) {
        Point<uint16_t> p1{point_arr[i]};
        for (int j = i + 1; j < arr_size; j++) {
            Point<uint16_t> p2{point_arr[j]};
            double dist_squared{std::pow(p1.x - p2.x, 2) +
                                std::pow(p1.y - p2.y, 2)};
            double dist{sqrt(dist_squared)};
            queue->enqueue(PointPair(p1, p2, dist));
        }
    }
}

void get_closest_points(Point<uint16_t>* point_arr,
                        int arr_size) {  // , int m) {
    Queue<PointPair> q{};
    calc_distances(&q, point_arr, arr_size);
    PointPair* pp{q.to_array()};
    merge_sort(pp, 0, q.size() - 1, &cmp);
    std::cout << "pairs by distance:" << std::endl;
    for (int i = 0; i < (int)q.size(); i++) {
        std::cout << pp[i].first << " " << pp[i].second << pp[i].distance
                  << std::endl;
    }

    delete[] pp;
}
