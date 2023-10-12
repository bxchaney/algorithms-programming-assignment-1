
/*
 * Copyright 2023, Brandon Chaney
 */

#pragma once
#include <fstream>

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
/// where each value is read in as a double and each value is delimited by a
/// space
void read_points(std::ifstream& is, ArrayQueue<Point<double>>* queue);
