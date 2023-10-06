
/*
 * Copyright 2023, Brandon Chaney
 */

#pragma once
#include <cstdint>
#include <fstream>

#include "./container.hpp"
#include "./point.hpp"
#include "./tree.hpp"

/// @brief because each integer in the input file is assumed to be less than or
/// equal to 65535,
/// this function returns a unique hash for each x, y combination. This ensures
/// that the list of points added to the queue is unique.
uint32_t get_hash(uint16_t x, uint16_t y);

/// @brief This helper function reads from the provided file stream
/// and returns a Queue with the points contained in the file.
///
/// This function assumes that the input filestream has the form:
/// a,b
/// c,d
/// e,f
/// ...
/// y,z
///
/// where each value is between 0 and 65535, and each line contains two integers
/// delimited by a single comma.
void read_points(std::ifstream& is, ArrayQueue<Point<uint16_t>>* queue);
