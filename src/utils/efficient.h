/*
 * Copyright 2023, Brandon Chaney
 * This module contains the implementation of the divide and conquer algorithm
 * for finding the closest pairs of points in a set of points.
 */

#pragma once

#include "./close.h"
#include "./container.hpp"
#include "./point.hpp"

class EfficientClosestPairs : public PointComparer {
 private:
    ArrayList<PointPair>* arraylist_merge(ArrayList<PointPair>* list1,
                                          ArrayList<PointPair>* list2, int m);

    ArrayList<PointPair>* combine(ArrayList<PointPair>* p_l,
                                  ArrayList<PointPair>* p_r, Point<double>* y,
                                  int arr_size, double line, int m);
    ArrayList<PointPair>* divide(Point<double>* x, int x_size, Point<double>* y,
                                 int y_size, int m);

    void merge(Point<double>* arr, int l, int m, int r, int x_or_y);
    void merge_sort(Point<double>* arr, int l, int r, int x_or_y);

    bool sort_by_x(Point<double>* a, Point<double>* b);
    bool sort_by_y(Point<double>* a, Point<double>* b);

 public:
    EfficientClosestPairs() : PointComparer() {}

    ArrayList<PointPair>* divide_and_conquer_closest_pairs(Point<double>* p,
                                                           int arr_size, int m);
};
