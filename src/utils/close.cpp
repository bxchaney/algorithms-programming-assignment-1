/*
 * Copyright 2023, Brandon Chaney
 */

#include "./close.h"

#include <math.h>

#include <algorithm>
#include <iostream>

#include "./container.hpp"
#include "./point.hpp"

using PointPair = PointComparer::PointPair;

/// @brief This method inserts the PointPair p to its in-order place in arr,
/// if it should be there.
/// @param arr 
/// @param p 
void PointComparer::insert_in_order(ArrayList<PointPair>* arr, PointPair p) {
    // if the array list is empty, inster to the beginning
    _comparisons++;
    if (arr->size() == 0) {
        arr->insert(0, p);
        return;
    }

    // if this point pair's distance is greater than the greatest pair's
    // distance so far and it is a new point pair
    _comparisons++;
    if ((p.distance >= (*arr)[arr->size() - 1].distance) &&
        p != (*arr)[arr->size() - 1]) {
        // and the list is not full, insert to end
        // otherwise, exit
        _comparisons++;
        if (arr->size() != arr->max_size()) {
            arr->insert(arr->size(), p);
        }
        return;
    }

    // the point should be inserted in front of at least one point in the list
    int i{0};
    while (i < static_cast<int>(arr->size())) {
        _comparisons++;
        if (p == (*arr)[i])
            return;  // if we have this point already, ignore
                     // iterate until we find a point to insert this point after
        _comparisons++;
        if (p.distance < (*arr)[i].distance) {
            // p is inserted to position i in the array, causing size - i
            // elements to be shifted back
            _comparisons += arr->size() - i;
            arr->insert(i, p);
            return;
        }
        i++;
    }
}

/// @brief This is the brute-force comparisons of all points in p to all other
/// points. This method gives the caller ownership of the returned ArrayList 
/// containing the m closest pairs of points.
/// @param p 
/// @param arr_size 
/// @param m 
/// @return 
ArrayList<PointPair>* PointComparer::conquer(Point<double>* p, int arr_size,
                                             int m) {
    ArrayList<PointPair>* arr{new ArrayList<PointPair>(m)};
    for (int i = 0; i < arr_size - 1; i++) {
        Point<double> p1{p[i]};
        for (int j = i + 1; j < arr_size; j++) {
            Point<double> p2{p[j]};
            double dist_squared{std::pow(p1.x - p2.x, 2) +
                                std::pow(p1.y - p2.y, 2)};
            double dist{sqrt(dist_squared)};
            insert_in_order(arr, {p1, p2, dist});
        }
    }
    return arr;
}
