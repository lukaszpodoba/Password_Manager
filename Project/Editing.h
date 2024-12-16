#pragma once

#include "Password.h"

#include <vector>

/**
 * @brief Edits the password.
 *
 * This function allows the user to select a password and edit its attributes
 * such as name, password, category, website, and login. The user can choose which
 * attributes to edit and can go back or exit at any time. This function calls the
 * `editOptions()` function to get the selected edit options from the user.
 *
 * @param allPasswords A vector of all passwords from which passwords will be selected for editing.
 */

auto editPassword(std::vector<Password>& allPasswords) -> void;