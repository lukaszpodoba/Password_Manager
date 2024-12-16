#pragma ocne

#include "Menu.h"
#include "Encryption.h"
#include "Category.h"
#include "manipulatingPasswords.h"
#include "Password.h"

#include <vector>
#include <set>

/**
 * @brief Searches for passwords based on selected search options.
 *
 * This function calls the `searchOptions()` function to get the selected search options
 * from the user. The function searches for passwords in the provided vector of Password
 * objects based on the selected options.
 *
 * @param allPasswords A vector of Password objects.
 * @return A set of indexes representing the positions of the matching passwords in the vector.
 */

auto searchPassword(const std::vector<Password>& allPasswords) -> std::set<int>;