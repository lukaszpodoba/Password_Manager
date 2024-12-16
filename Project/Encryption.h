#pragma once

#include "Password.h"

#include <string>
#include <vector>
#include <filesystem>

/**
 * @brief Checks if the provided password is correct for the specified file.
 *
 * This function opens the specified file, reads the first line of the file,
 * decrypts it using the provided password, and checks if the decrypted line
 * matches the expected value "verification". If the decrypted line matches,
 * it indicates that the provided password is correct for the file.
 *
 * @param password The password to be checked.
 * @param file The path to the file for which the password is being checked.
 * @return Bool `true` if the password is correct, `false` otherwise.
 */

auto goodFilePassword(const std::string& password, const std::filesystem::path& file) -> bool;

/**
 * @brief Reads lines from a file and returns them as a vector of `Password` objects.
 *
 * This function reads passwords from the specified file, skipping the first line, which is
 * responsible for validating the file password, then decrypts the rest of the lines using the
 * the given password and converts the decrypted lines into `Password` objects. The `Password`
 * objects are stored in a vector.
 *
 * @param password The password used for decryption.
 * @param file The path to the file containing the passwords.
 * @return A vector containing the `Password` objects.
 */

auto fileToVec(const std::string& password, const std::filesystem::path& file) -> std::vector<Password>;

/**
 * @brief Writes a vector of `Password` objects to a file.
 *
 * This function takes a vector of `Password` objects, encrypts each `Password` object, after
 * converting it to a line, using the specified password, and writes the encrypted
 * lines to the specified file. The function also adds a verification line at the beginning
 * of the file, which is responsible for validating the password to the file.
 *
 * @param password The password used for encryption.
 * @param file The path to the output file.
 * @param allPasswords The vector of `Password` objects to be written to the file.
 */

auto vecTofile(const std::string& password, const std::filesystem::path& file, const std::vector<Password>& allPasswords) -> void;

/**
 * @brief Encrypts the contents of a file using the specified password for the first time.
 *
 * This function reads the contents of the specified file, encrypts each line using the specified
 * password and overwrites the file with the encrypted lines. The function ensures that the
 * contents of the file are overwritten with its encrypted version. The function is used in preparing
 * the new file is action.
 *
 * @param password The password used for encryption.
 * @param file The path to the file to be encrypted.
 */

auto firstTimeEncrypt(const std::string& password, const std::filesystem::path& file) -> void;

/**
 * @brief Adds timestamps to a file.
 *
 * This function reads the contents of the specified file and adds timestamps to the specified
 * lines, depending on the number of lines in file. The hour, minute and second values of the current
 * local time are used as timestamps.
 *
 * @param file path to the file.
 * @return A vector of strings representing the current timestamp.
 */

auto addTimestamps(const std::filesystem::path& file) -> std::vector<std::string>;

/**
 * @brief Adds old timestamps to a file.
 *
 * This function reads the contents of the specified file and adds old timestamps to the specified
 * lines, depending on the number of lines in file. The hour, minute and second values of the current
 * local time are used as timestamps.
 *
 * @param file The path to the file.
 * @param timestamp A vector of strings representing the timestamp to be added.
 */

auto addOldTimestamps(const std::filesystem::path& file, const std::vector<std::string>& timestamp) -> void;

/**
 * @brief Deletes timestamps in a file.
 *
 * This function reads the contents of the specified file and removes timestamps from the lines
 * where they are located.
 *
 * @param file The path to the file.
 */

auto deleteTimestamps(const std::filesystem::path& file) -> void;

/**
 * @brief Displays the current timestamp from a file.
 *
 * This function reads the contents of the specified file and retrieves the current
 * timestamp, which it then displays.
 *
 * @param file The path to the file.
 */

auto showTimestamps(const std::filesystem::path& file) -> void;