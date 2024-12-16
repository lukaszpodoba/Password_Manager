#pragma once

#include "Menu.h"
#include "Encryption.h"

#include <vector>
#include <string>
#include <set>

/**
 * @brief Retrieves available categories from a vector of Password objects.
 *
 * This function takes a vector of Password objects and extracts the unique categories from them.
 *
 * @param allPasswords A vector of Password objects.
 * @return A set of strings representing the unique categories.
 */

auto avaliableCategories(const std::vector<Password> &allPasswords) -> std::set<std::string>;

/**
 * @brief Adds a new category to the set of unique categories.
 *
 * This function prompts the user to enter the name of a new category. It checks whether
 * the entered category already exists in the set of unique categories. If not, it adds the
 * new category to the set. The function supports entering an invalid name.
 *
 * @param uniqueCategories A set of strings representing the unique categories.
 */

auto addCategory(std::set<std::string> &uniqueCategories) -> void;

/**
 * @brief Deletes a category from the set of unique categories and removes passwords associated with that category.
 *
 * This function prompts the user to enter the name of a category to delete. It checks if the
 * entered category exists in the set of unique categories. If found, it removes the category from
 * the set and also removes any passwords associated with that category from the vector of Password
 * objects. The function handles special cases such as an invalid category name or the user canceling
 * the deletion operation.
 *
 * @param uniqueCategories A set of strings representing the unique categories.
 * @param allPasswords A vector of Password objects.
 */

auto deleteCategory(std::set<std::string> &uniqueCategories, std::vector<Password> &allPasswords) -> void;