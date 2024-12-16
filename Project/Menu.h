#pragma once

#include <string>
#include <filesystem>
#include <vector>

/**
 * @brief Allows the user to select a text file or provide a direct path.
 *
 * This function asks the user to select a text file from the list of
 * available options or to enter a direct absolute path to a file.
 * The function also checks if the selected file exists and is a text file.
 *
 * @return The path to the selected text file
 */

auto pickFile() -> std::filesystem::path;

/**
 * @brief Prepares the new file.
 *
 * This function opens the specified file and writes the word "verification" to it in the
 * first line, which is responsible for checking the correctness of the file's password.
 * Encrypts the file using the provided password, and adds timestamps to the encrypted file.
 *
 * @param password The password used for file encryption.
 * @param file The path to the file to be prepared
 * @return A vector of strings containing the added timestamps.
 */

auto prepareFile(const std::string& password, const std::filesystem::path& file) -> std::vector<std::string>;

/**
 * @brief Adds missing lines to the specified file so that it has at least 5 lines in total.
 *
 * This function reads the contents of the specified file, counts the number of lines, and adds
 * if missing blank lines to the file until it has at least 5 lines. The function is needed to
 * provide at least 5 lines to add a timestamp.
 *
 * @param file The path to the file to which missing lines should be added.
 */
auto addMissingLines(const std::filesystem::path& file) -> void;