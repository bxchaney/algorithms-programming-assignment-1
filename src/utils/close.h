/*
 * Copyright 2023, Brandon Chaney
 */
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

bool cmp(PointPair* a, PointPair* b);
bool sort_by_x(Point<uint16_t>* a, Point<uint16_t>* b);
bool sort_by_y(Point<uint16_t>* a, Point<uint16_t>* b);

/*
 * Brute-force implementation
 *
 */
void calc_distances(Queue<PointPair>* queue, Point<uint16_t>* point_arr,
                    int arr_size);

void get_closest_points(Point<uint16_t>* point_arr, int arr_size);

void insert_in_order(ArrayList<PointPair>* arr, PointPair p);
ArrayList<PointPair>* arraylist_merge(ArrayList<PointPair>* list1,
                                      ArrayList<PointPair>* list2, int m);

ArrayList<PointPair>* conquer(Point<uint16_t>* p, int arr_size, int m);
ArrayList<PointPair>* combine(ArrayList<PointPair>* p_l,
                              ArrayList<PointPair>* p_r, Point<uint16_t>* y,
                              int arr_size, uint16_t line, int m);
ArrayList<PointPair>* divide(Point<uint16_t>* x, int x_size, Point<uint16_t>* y,
                             int y_size, int m);

ArrayList<PointPair>* divide_and_conquer_closest_pairs(Point<uint16_t>* p,
                                                       int arr_size, int m);
