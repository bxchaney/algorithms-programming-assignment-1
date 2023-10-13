/*
 * Copyright 2023, Brandon Chaney
 */

#include "./brute_force.h"

using PointPair = PointComparer::PointPair;

/// @brief This method is identical to PointComparer::conquer.
/// @param p 
/// @param arr_size 
/// @param m 
/// @return 
ArrayList<PointPair>* BruteForceClosestPairs::brute_force_closest_pairs(
    Point<double>* p, int arr_size, int m) {
    return conquer(p, arr_size, m);
}
