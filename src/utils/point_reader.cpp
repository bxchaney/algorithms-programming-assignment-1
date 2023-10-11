/*
 * Copyright 2023, Brandon Chaney
 */

#include "./point_reader.h"

#include <fstream>
#include <sstream>
#include <string>

#include "./container.hpp"
#include "./point.hpp"

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
void read_points(std::ifstream& is, ArrayQueue<Point<double>>* queue) {
    double x;
    double y;
    std::string line;
    while (std::getline(is, line)) {
        std::istringstream iss(line);
        if (!(iss >> x >> y)) {
            break;
        }
        queue->enqueue(Point(x, y));
    }
}
