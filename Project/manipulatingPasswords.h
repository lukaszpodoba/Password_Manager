#pragma once

#include <set>

/**
 * @brief Checks the strength of the password.
 *
 * This function calculates the strength of a password based on various criteria, such
 * as length, presence of uppercase and lowercase letters, digits, and special
 * characters. It uses regular expressions to perform pattern matching and increments a strength
 * variable based on the presence of these criteria. Finally, it prints a message indicating
 * the strength of the password
 *
 * @param password String representing the password.
 */

auto passwordStrength(const std::string& password) -> void;

/**
 * @brief Creating a new password that the user wrote.
 *
 * This function allows the user to add a new password. It prompts the user to
 * enter a password, checks its validity (length and absence of the '~' character), and
 * ensures it's not already used. If the password already exists, it prompts
 * the user for a decision to continue or quit.
 *
 * @param allPasswords Object vector `Password`, in which it checks the occurrence of a new password.
 * @return New password entered by user.
 */

auto addPassword(std::vector<Password> &allPasswords) -> std::string;

/**
 * @brief Generate a new password based on the parameters entered by the user.
 *
 * This function serves as a password generator. It prompts the user to enter the number
 * of characters for the password, whether it should contain uppercase and lowercase
 * letters, and whether it should include special characters. It uses: `generateLetters`,
 * `generateSpecials`, `generateDigits` helper functions to generate the password, by
 * combining the resulting strings into one and then shuffling the chars in it.
 *
 * @return New password generated based on the given parameters.
 */

auto generatePassword() -> std::string;

/**
 * @brief Creating new Password object.
 *
 * This function allows the user to create a new password object. It calls the
 * addPassword or generatePassword function depending on the user's choice. It then
 * asks the user to enter the name and available category of the password object.
 * If no category exists, the user will not be able to create a new object, the user
 * will have to add a category first Optionally, it asks for the website or login
 * associated with the password. Finally, it creates a new Password object with the
 * provided information and adds it to a vector storing all Password objects.
 *
 * @param allPasswords Vector of `Password` objects, where the new object will be added.
 * @param uniqueCategories Set of available categories that can be used when creating an object.
 */

auto newPasswordObject(std::vector<Password>& allPasswords, const std::set<std::string> &uniqueCategories) -> void;
