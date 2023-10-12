/*
 * Copyright 2023, Brandon Chaney
 */

#include "./brute_force.h"

using PointPair = PointComparer::PointPair;

ArrayList<PointPair>* BruteForceClosestPairs::brute_force_closest_pairs(
    Point<double>* p, int arr_size, int m) {
    return conquer(p, arr_size, m);
}
