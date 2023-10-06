/*
 * Copyright 2023, Brandon Chaney
 */

#include "./close.h"

#include <math.h>

#include <algorithm>
#include <cstdint>
#include <iostream>

#include "./container.hpp"
#include "./mergesort.hpp"
#include "./point.hpp"

bool cmp(PointPair* a, PointPair* b) { return a->distance <= b->distance; }

bool sort_by_x(Point<uint16_t>* a, Point<uint16_t>* b) {
    if (a->x == b->x) {
        return a->y <= b->y;
    }
    return a->x < b->x;
}

bool sort_by_y(Point<uint16_t>* a, Point<uint16_t>* b) {
    if (a->y == b->y) {
        return a->x <= b->x;
    }
    return a->y < b->y;
}

void calc_distances(Queue<PointPair>* queue, Point<uint16_t>* point_arr,
                    int arr_size) {
    for (int i = 0; i < (arr_size - 1); i++) {
        Point<uint16_t> p1{point_arr[i]};
        for (int j = i + 1; j < arr_size; j++) {
            Point<uint16_t> p2{point_arr[j]};
            double dist_squared{std::pow(p1.x - p2.x, 2) +
                                std::pow(p1.y - p2.y, 2)};
            double dist{sqrt(dist_squared)};
            queue->enqueue({p1, p2, dist});
        }
    }
}

void get_closest_points(Point<uint16_t>* point_arr,
                        int arr_size) {  // , int m) {
    Queue<PointPair> q{};
    calc_distances(&q, point_arr, arr_size);
    PointPair* pp{q.to_array()};
    merge_sort(pp, 0, q.size() - 1, &cmp);
    for (int i = 0; i < (int)q.size(); i++) {
        std::cout << pp[i].first << " " << pp[i].second << pp[i].distance
                  << std::endl;
    }

    delete[] pp;
}

void insert_in_order(ArrayList<PointPair>* arr, PointPair p) {
    // if the array list is empty, inster to the beginning
    if (arr->size() == 0) {
        arr->insert(0, p);
        return;
    }

    // if this point pair's distance is greater than the greatest pair's
    // distance so far and it is a new point pair
    if ((p.distance >= (*arr)[arr->size() - 1].distance) &&
        p != (*arr)[arr->size() - 1]) {
        // and the list is not full, insert to end
        // otherwise, exit
        if (arr->size() != arr->max_size()) {
            arr->insert(arr->size(), p);
        }
        return;
    }

    // the point should be inserted in front of at least one point in the list
    int i{0};
    while (i < static_cast<int>(arr->size())) {
        if (p == (*arr)[i]) return;  // if we have this point already, ignore
        if (p.distance < (*arr)[i].distance) {
            arr->insert(i, p);
            return;
        }
        i++;
    }
}

ArrayList<PointPair>* arraylist_merge(ArrayList<PointPair>* list1,
                                      ArrayList<PointPair>* list2, int m) {
    ArrayList<PointPair>* new_list{new ArrayList<PointPair>(m)};
    int i{0};
    int j{0};
    while (i < static_cast<int>(list1->size()) &&
           j < static_cast<int>(list2->size()) &&
           static_cast<int>(new_list->size()) <= m) {
        if ((*list1)[i].distance <= (*list2)[j].distance) {
            insert_in_order(new_list, (*list1)[i]);
            i++;
        } else {
            insert_in_order(new_list, (*list2)[j]);
            j++;
        }
    }

    while (i < static_cast<int>(list1->size()) &&
           static_cast<int>(new_list->size()) <= m) {
        new_list->insert(new_list->size(), (*list1)[i]);
        i++;
    }

    while (j < static_cast<int>(list2->size()) &&
           static_cast<int>(new_list->size()) <= m) {
        new_list->insert(new_list->size(), (*list2)[j]);
        j++;
    }
    return new_list;
}

ArrayList<PointPair>* conquer(Point<uint16_t>* p, int arr_size, int m) {
    ArrayList<PointPair>* arr{new ArrayList<PointPair>(m)};
    for (int i = 0; i < arr_size - 1; i++) {
        Point<uint16_t> p1{p[i]};
        for (int j = i + 1; j < arr_size; j++) {
            Point<uint16_t> p2{p[j]};
            double dist_squared{std::pow(p1.x - p2.x, 2) +
                                std::pow(p1.y - p2.y, 2)};
            double dist{sqrt(dist_squared)};
            insert_in_order(arr, {p1, p2, dist});
        }
    }
    return arr;
}

ArrayList<PointPair>* combine(ArrayList<PointPair>* p_l,
                              ArrayList<PointPair>* p_r, Point<uint16_t>* y,
                              int arr_size, uint16_t line, int m) {
    ArrayList<PointPair>* p{arraylist_merge(p_l, p_r, m)};
    ArrayQueue<Point<uint16_t>> q{};

    double delta{std::min((*p_l)[p_l->size() - 1].distance,
                          (*p_r)[p_r->size() - 1].distance)};
    double u_bound{static_cast<int>(line) + delta};
    double l_bound{static_cast<int>(line) - delta};
    for (int i = 0; i < arr_size; i++) {
        if (y[i].x >= l_bound && y[i].x <= u_bound) {
            q.enqueue(y[i]);
        }
    }
    Point<uint16_t>* y_prime{q.to_array()};
    for (int i = 0; i < static_cast<int>(q.size()) - 1; i++) {
        Point<uint16_t> p1{y_prime[i]};
        for (int j = i + 1; (j < static_cast<int>(q.size()) && j <= i + 7);
             j++) {
            Point<uint16_t> p2{y_prime[j]};
            double dist_squared{std::pow(p1.x - p2.x, 2) +
                                std::pow(p1.y - p2.y, 2)};
            double dist{sqrt(dist_squared)};
            insert_in_order(p, {p1, p2, dist});
        }
    }

    delete[] y_prime;

    return p;
}

ArrayList<PointPair>* divide(Point<uint16_t>* x, int x_size, Point<uint16_t>* y,
                             int y_size, int m) {
    // base case is when we have a small enough subset that the total number
    // of possible point pairs is less than m or less than 3
    
    unsigned long long x_size_big{static_cast<unsigned long long>(x_size)};

    if (x_size <= 3 
        || (x_size <= m) 
        || ( ((x_size_big * (x_size_big - 1)) / 2) <= static_cast<u_int64_t>(m)))
         {
        return conquer(x, x_size, m);
    }

    // divide problem space
    int k{(x_size - 1) / 2};

    ArrayQueue<Point<uint16_t>> l{};
    ArrayQueue<Point<uint16_t>> r{};
    ArrayQueue<Point<uint16_t>> l_y{};
    ArrayQueue<Point<uint16_t>> r_y{};

    uint16_t line{x[k].x};

    for (int i = 0; i < x_size; i++) {
        if (x[i].x == line) {
            l.enqueue(x[i]);
            r.enqueue(x[i]);
        } else if (x[i].x < line) {
            l.enqueue(x[i]);
        } else {
            r.enqueue(x[i]);
        }
    }

    for (int i = 0; i < y_size; i++) {
        if (y[i].x == line) {
            l_y.enqueue(y[i]);
            r_y.enqueue(y[i]);
        } else if (y[i].x < line) {
            l_y.enqueue(y[i]);
        } else {
            r_y.enqueue(y[i]);
        }
    }

    // not actually dividing in to smaller sub-problems because of the line choice
    if (static_cast<int>(l.size()) == x_size || static_cast<int>(r.size()) == x_size) {
        return conquer(x, x_size, m);
    }

    Point<uint16_t>* x_l{l.to_array()};
    Point<uint16_t>* x_r{r.to_array()};
    Point<uint16_t>* y_l{l_y.to_array()};
    Point<uint16_t>* y_r{r_y.to_array()};

    ArrayList<PointPair>* p_l{
        divide(x_l, (int)l.size(), y_l, (int)l_y.size(), m)};
    ArrayList<PointPair>* p_r{
        divide(x_r, (int)r.size(), y_r, (int)r_y.size(), m)};

    ArrayList<PointPair>* p{combine(p_l, p_r, y, y_size, line, m)};

    delete[] x_l;
    delete[] x_r;
    delete[] y_l;
    delete[] y_r;
    delete p_l;
    delete p_r;

    return p;
}

ArrayList<PointPair>* divide_and_conquer_closest_pairs(Point<uint16_t>* p,
                                                       int arr_size, int m) {
    // copy p into x and y
    Point<uint16_t>* x{new Point<uint16_t>[arr_size]};
    Point<uint16_t>* y{new Point<uint16_t>[arr_size]};
    for (int i = 0; i < arr_size; i++) {
        x[i] = p[i];
        y[i] = p[i];
    }

    // sort x and y
    merge_sort<Point<uint16_t>>(x, 0, arr_size - 1, &sort_by_x);
    merge_sort<Point<uint16_t>>(y, 0, arr_size - 1, &sort_by_y);

    ArrayList<PointPair>* pp{divide(x, arr_size, y, arr_size, m)};
    return pp;
}
