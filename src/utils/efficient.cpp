/*
 * Copyright 2023, Brandon Chaney
 */

#include "./efficient.h"

#include <math.h>

using PointPair = PointComparer::PointPair;

ArrayList<PointPair>* EfficientClosestPairs::arraylist_merge(
    ArrayList<PointPair>* list1, ArrayList<PointPair>* list2, int m) {
    ArrayList<PointPair>* new_list{new ArrayList<PointPair>(m)};
    int i{0};
    int j{0};

    // put elements in to new list until new list is full or one of the source
    // lists is empty
    while (i < static_cast<int>(list1->size()) &&
           j < static_cast<int>(list2->size()) &&
           static_cast<int>(new_list->size()) < m) {
        _comparisons++;
        if ((*list1)[i].distance <= (*list2)[j].distance) {
            insert_in_order(new_list, (*list1)[i]);
            i++;
        } else {
            insert_in_order(new_list, (*list2)[j]);
            j++;
        }
    }

    // continue filling list until full or list1 is empty
    while (i < static_cast<int>(list1->size()) &&
           static_cast<int>(new_list->size()) < m) {
        _comparisons++;
        new_list->insert(new_list->size(), (*list1)[i]);
        i++;
    }

    // continue fill list until fill or list2 is empty
    while (j < static_cast<int>(list2->size()) &&
           static_cast<int>(new_list->size()) < m) {
        _comparisons++;
        new_list->insert(new_list->size(), (*list2)[j]);
        j++;
    }
    return new_list;
}

ArrayList<PointPair>* EfficientClosestPairs::combine(ArrayList<PointPair>* p_l,
                                                     ArrayList<PointPair>* p_r,
                                                     Point<double>* y,
                                                     int arr_size, double line,
                                                     int m) {
    ArrayList<PointPair>* p{arraylist_merge(p_l, p_r, m)};
    ArrayQueue<Point<double>> q{};

    double delta{(*p)[p->size()-1].distance};

    double u_bound{static_cast<int>(line) + delta};
    double l_bound{static_cast<int>(line) - delta};
    for (int i = 0; i < arr_size; i++) {
        _comparisons++;
        if (y[i].x >= l_bound && y[i].x <= u_bound) {
            q.enqueue(y[i]);
        }
    }
    Point<double>* y_prime{q.to_array()};
    for (int i = 0; i < static_cast<int>(q.size()) - 1; i++) {
        Point<double> p1{y_prime[i]};
        for (int j = i + 1; (j < static_cast<int>(q.size()) && j <= i + 7);
             j++) {
            Point<double> p2{y_prime[j]};
            double dist_squared{std::pow(p1.x - p2.x, 2) +
                                std::pow(p1.y - p2.y, 2)};
            double dist{sqrt(dist_squared)};
            insert_in_order(p, {p1, p2, dist});
        }
    }

    delete[] y_prime;

    return p;
}

ArrayList<PointPair>* EfficientClosestPairs::divide(Point<double>* x,
                                                    int x_size,
                                                    Point<double>* y,
                                                    int y_size, int m) {
    // base case is when we have a small enough subset that the total number
    // of possible point pairs is less than m or less than 3

    uint64_t x_size_big{static_cast<uint64_t>(x_size)};

    _comparisons += 3;
    if (x_size <= 3 || (x_size <= m) ||
        (((x_size_big * (x_size_big - 1)) / 2) <= static_cast<u_int64_t>(m))) {
        return conquer(x, x_size, m);
    }

    // divide problem space
    int k{(x_size - 1) / 2};

    ArrayQueue<Point<double>> l{};
    ArrayQueue<Point<double>> r{};
    ArrayQueue<Point<double>> l_y{};
    ArrayQueue<Point<double>> r_y{};

    double line{x[k].x};

    for (int i = 0; i < x_size; i++) {
        _comparisons++;
        if (x[i].x == line) {
            l.enqueue(x[i]);
            r.enqueue(x[i]);
        } else if (x[i].x < line) {
            _comparisons++;
            l.enqueue(x[i]);
        } else {
            _comparisons++;
            r.enqueue(x[i]);
        }
    }

    for (int i = 0; i < y_size; i++) {
        _comparisons++;
        if (y[i].x == line) {
            l_y.enqueue(y[i]);
            r_y.enqueue(y[i]);
        } else if (y[i].x < line) {
            _comparisons++;
            l_y.enqueue(y[i]);
        } else {
            _comparisons++;
            r_y.enqueue(y[i]);
        }
    }

    // not actually dividing in to smaller sub-problems because of the line
    // choice
    _comparisons++;
    if (static_cast<int>(l.size()) == x_size ||
        static_cast<int>(r.size()) == x_size) {
        return conquer(x, x_size, m);
    }

    Point<double>* x_l{l.to_array()};
    Point<double>* x_r{r.to_array()};
    Point<double>* y_l{l_y.to_array()};
    Point<double>* y_r{r_y.to_array()};

    ArrayList<PointPair>* p_l{divide(x_l, static_cast<int>(l.size()), y_l,
                                     static_cast<int>(l_y.size()), m)};
    ArrayList<PointPair>* p_r{divide(x_r, static_cast<int>(r.size()), y_r,
                                     static_cast<int>(r_y.size()), m)};

    ArrayList<PointPair>* p{combine(p_l, p_r, y, y_size, line, m)};

    delete[] x_l;
    delete[] x_r;
    delete[] y_l;
    delete[] y_r;
    delete p_l;
    delete p_r;

    return p;
}

void EfficientClosestPairs::merge(Point<double>* arr, int l, int m, int r,
                                  int x_or_y) {
    bool (EfficientClosestPairs::*leq)(Point<double>*, Point<double>*);
    // sorting by x
    if (x_or_y == 0) {
        leq = &EfficientClosestPairs::sort_by_x;
    } else {
        leq = &EfficientClosestPairs::sort_by_y;
    }

    int i, j, k, nl, nr;
    nl = m - l + 1;
    nr = r - m;

    // make temp arrays and copy array contents into them
    Point<double>* larr{new Point<double>[nl]};
    Point<double>* rarr{new Point<double>[nr]};

    for (i = 0; i < nl; i++) larr[i] = arr[l + i];
    for (j = 0; j < nr; j++) rarr[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    // merge arrays
    while (i < nl && j < nr) {
        _comparisons++;
        if ((this->*leq)(&(larr[i]), &(rarr[j]))) {
            arr[k] = larr[i];
            i++;
        } else {
            arr[k] = rarr[j];
            j++;
        }
        k++;
    }
    while (i < nl) {
        _comparisons++;
        arr[k] = larr[i];
        i++;
        k++;
    }
    while (j < nr) {
        _comparisons++;
        arr[k] = rarr[j];
        j++;
        k++;
    }

    delete[] larr;
    delete[] rarr;
}

void EfficientClosestPairs::merge_sort(Point<double>* arr, int l, int r,
                                       int x_or_y) {
    _comparisons++;
    if (l < r) {
        int m{l + (r - l) / 2};
        merge_sort(arr, l, m, x_or_y);
        merge_sort(arr, m + 1, r, x_or_y);
        merge(arr, l, m, r, x_or_y);
    }
}

bool EfficientClosestPairs::sort_by_x(Point<double>* a, Point<double>* b) {
    _comparisons += 2;
    if (a->x == b->x) {
        return a->y <= b->y;
    }
    return a->x < b->x;
}

bool EfficientClosestPairs::sort_by_y(Point<double>* a, Point<double>* b) {
    _comparisons += 2;
    if (a->y == b->y) {
        return a->x <= b->x;
    }
    return a->y < b->y;
}

ArrayList<PointPair>* EfficientClosestPairs::divide_and_conquer_closest_pairs(
    Point<double>* p, int arr_size, int m) {
    // copy p into x and y
    Point<double>* x{new Point<double>[arr_size]};
    Point<double>* y{new Point<double>[arr_size]};
    for (int i = 0; i < arr_size; i++) {
        x[i] = p[i];
        y[i] = p[i];
    }

    // sort x and y
    merge_sort(x, 0, arr_size - 1, 0);
    merge_sort(y, 0, arr_size - 1, 1);

    ArrayList<PointPair>* pp{divide(x, arr_size, y, arr_size, m)};
    return pp;
}
