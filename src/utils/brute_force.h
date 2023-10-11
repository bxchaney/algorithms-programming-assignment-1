/*
 * Copyright 2023, Brandon Chaney
 */

#pragma once

#include "./close.h"
#include "./container.hpp"
#include "./point.hpp"

class BruteForceClosestPairs : public PointComparer {
 public:
    BruteForceClosestPairs() : PointComparer() {}

    ArrayList<PointPair>* brute_force_closest_pairs(Point<double>* p,
                                                    int arr_size, int m);
};
