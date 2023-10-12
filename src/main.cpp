/*
 * Copyright 2023 bxchaney
 */

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>

#include "utils/brute_force.h"
#include "utils/close.h"
#include "utils/container.hpp"
#include "utils/efficient.h"
#include "utils/point.hpp"
#include "utils/point_reader.h"

using PointPair = PointComparer::PointPair;

/// @brief this function casts a null terminated char array to its integer
/// value. It assumes that the array is only integer numerals.
int cast_char_arr_to_int(char* str) {
    int n{0};
    int i{0};
    while (str[i]) {
        n *= 10;
        n += (str[i] - '0');
        i++;
    }
    return n;
}

void trace_run(Point<double>* p, int arr_size, int m) {
    BruteForceClosestPairs brute_force{};
    EfficientClosestPairs efficient{};

    std::cout << "Finding the " << m
              << " closest pairs amongst the following points:" << std::endl;
    std::cout << "[ ";
    for (int i = 0; i < arr_size; i++) {
        std::cout << p[i] << " ";
    }
    std::cout << "]" << std::endl << std::endl;

    std::unique_ptr<ArrayList<PointPair>> brute_force_pp{
        brute_force.brute_force_closest_pairs(p, arr_size, m)};
    std::unique_ptr<ArrayList<PointPair>> efficient_pp{
        efficient.divide_and_conquer_closest_pairs(p, arr_size, m)};

    bool results_match = true;
    if (brute_force_pp->size() != efficient_pp->size()) {
        results_match = false;
    }

    std::cout << "Brute force closest pairs: " << std::endl;
    std::unique_ptr<PointPair[]> bf_arr{brute_force_pp->to_array()};
    int brute_force_size{static_cast<int>(brute_force_pp->size())};
    for (int i = 0; i < brute_force_size; i++) {
        std::cout << std::setw(3) << (i + 1) << ". "
                  << "Pair( distance: " << std::setw(8) << bf_arr[i].distance
                  << ", p1: " << bf_arr[i].first << ", p2: " << bf_arr[i].second
                  << " )" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Efficient method closest pairs: " << std::endl;
    std::unique_ptr<PointPair[]> eff_arr{efficient_pp->to_array()};
    int eff_size{static_cast<int>(efficient_pp->size())};
    for (int i = 0; i < eff_size; i++) {
        if (eff_arr[i] != bf_arr[i]) results_match = false;
        std::cout << std::setw(3) << (i + 1) << ". "
                  << "Pair( distance: " << std::setw(8) << eff_arr[i].distance
                  << ", p1: " << eff_arr[i].first
                  << ", p2: " << eff_arr[i].second << " )" << std::endl;
    }
    std::cout << std::endl;

    std::cout << std::endl
              << "Results match: " << (results_match ? "True" : "False")
              << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        return -1;
    }

    // assuming that the filepath to the datafile is the first parameter
    std::ifstream ifs{argv[1]};
    if (!ifs.is_open()) {
        std::cout << "Could not open file."
                  << " Please ensure that the first parameter is a valid "
                  << "relative filepath." << std::endl;
        return -1;
    }

    int n{cast_char_arr_to_int(argv[2])};

    ArrayQueue<Point<double>> q{};

    read_points(ifs, &q);

    Point<double>* p{q.to_array()};
    uint64_t dataset_size{q.size()};
    uint64_t max_m{((dataset_size - 1) * dataset_size) / 2};

    if (static_cast<uint64_t>(n) > max_m) {
        std::cout << "The provided m value was too large for this dataset."
                  << std::endl;
        std::cout << "This dataset has " << dataset_size
                  << " points. The max allowed m value is: " << max_m
                  << std::endl;
        std::cout << "You entered: " << n << std::endl;
        delete[] p;
        return -1;
    }

    // trace run to compare brute force and efficient
    if (argc == 3) {
        trace_run(p, static_cast<int>(q.size()), n);
    } else {
        int run_type{cast_char_arr_to_int(argv[3])};

        if (run_type == 0) {
            BruteForceClosestPairs comp{};
            std::unique_ptr<ArrayList<PointPair>> pairs{
                comp.brute_force_closest_pairs(p, dataset_size, n)};
            std::cout << argv[1] << ",brute-force," << dataset_size << "," << n
                      << "," << comp.comparisons() << std::endl;
        } else {
            EfficientClosestPairs comp{};
            std::unique_ptr<ArrayList<PointPair>> pairs{
                comp.divide_and_conquer_closest_pairs(p, dataset_size, n)};
            std::cout << argv[1] << ",efficient," << dataset_size << "," << n
                      << "," << comp.comparisons() << std::endl;
        }
    }

    delete[] p;
}
