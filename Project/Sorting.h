#pragma once

#include <vector>
#include <filesystem>
#include "Password.h"

/**
 * @brief Sorts the passwords based on the selected sorting options.
 *
 * This function calls the `sortingOptions()` function to get the selected sorting
 * options from the user. It then sorts a vector of Password objects based on the
 * selected options. The sorting is performed using stable sort.
 *
 * @param allPasswords A vector of Password objects.
 */

auto sortPasswords(std::vector<Password>& allPasswords) -> void;
