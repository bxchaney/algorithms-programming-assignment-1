/*
 * Copyright 2023 bxchaney
 */
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

#include "utils/close.h"
#include "utils/container.hpp"
#include "utils/point.hpp"
#include "utils/point_reader.h"

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

    Queue<Point<uint16_t>> q{};

    read_points(ifs, &q);

    Point<uint16_t>* p{q.to_array()};

    //    get_closest_points(p, (int)q.size());

    ArrayList<PointPair>* pp{
        divide_and_conquer_closest_pairs(p, static_cast<int>(q.size()), 10)};

    std::cout << pp->size() << std::endl;
    for (int i = 0; i < static_cast<int>(pp->size()); i++) {
        Point<uint16_t> p1{pp->_arr[i].first};
        Point<uint16_t> p2{pp->_arr[i].second};
        double dist{pp->_arr[i].distance};
        std::cout << p1 << " " << p2 << " " << dist << std::endl;
    }

    delete[] p;
    delete pp;
}
