/*
 * Copyright 2023, Brandon Chaney
 */

#include "./point_reader.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "./container.hpp"
#include "./point.hpp"
#include "./tree.hpp"

/// @brief because each integer in the input file is assumed to be less than or
/// equal to 65535, this function returns a unique hash for each x, y
/// combination. This ensures that the list of points added to the queue is
/// unique.
uint32_t get_hash(uint16_t x, uint16_t y) {
    uint32_t hash{x};
    hash <<= 16;
    hash += y;
    return hash;
}

/// @brief This helper function reads from the provided file stream
/// and returns a Queue with the points contained in the file.
///
/// This function assumes that the input filestream has the form:
/// a b
/// c d
/// e f
/// ...
/// y z
///
/// where each value is between 0 and 65535, and each line contains two integers
/// delimited by a single comma.
void read_points(std::ifstream& is, Queue<Point<uint16_t>>* queue) {
    int x, y;
    uint32_t hash;
    std::string line;
    Tree<uint32_t> t{};
    while (std::getline(is, line)) {
        std::istringstream iss(line);
        if (!(iss >> x >> y)) {
            break;
        }
        hash = get_hash(x, y);
        // if t already contains that hash, then that point has already been
        // added to our queue.
        if (!t.search(hash)) {
            queue->enqueue(Point((uint16_t)x, (uint16_t)y));
            t.insert(hash);
        }
    }
}
