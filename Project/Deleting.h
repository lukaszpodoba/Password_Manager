#pragma once

#include "Password.h"

#include <vector>

/**
 * @brief Deletes selected passwords from a vector of passwords.
 *
 * This function removes the passwords at the specified indexes from the vector
 * of passwords. The indexes to be deleted are obtained by calling the `selectedToDelete`
 * function inside. The vector is modified by removing the selected passwords.
 *
 * @param allPasswords A vector containing all the passwords.
 */

auto deletePassword(std::vector<Password>& allPasswords) -> void;

