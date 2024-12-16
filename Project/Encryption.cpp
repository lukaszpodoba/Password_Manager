#include "Encryption.h"
#include "Password.h"
#include "Menu.h"

#include <fmt/ranges.h>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <ctime>

/**
 * @brief Encrypts a line of text using the provided password.
 *
 * This function  encrypts every character of the input line with XOR operation with
 * the corresponding character from the password, then adds the length of the password
 * to avoid passing the option where the given password was entered 2 times in a row and
 * the number 32 to skip the first 32 ASCII characters.
 *
 * @param password The password used for encryption.
 * @param line The line of text to be encrypted.
 * @return The encrypted line.
 */

auto encrypt(const std::string& password, const std::string &line) -> std::string {
    auto result = std::string();
    for (int i = 0; i < line.size(); ++i) {
        auto encryptedChar = char(((line[i] ^ password[i % password.size()]) + password.size() + 31));
        result += encryptedChar;
    }
    return result;
}

/**
 * @brief Decrypts a line of text using the provided password.
 *
 * This function decrypts each character of the input line using an XOR
 * operation with the corresponding character from the password, but before
 * it does so it subtracts the length of the password that was added during
 * encryption to prevent a situation where typing the password twice in a
 * row correctly decrypts the file and the number 32, which omitted the first
 * 32 ASCII characters.
 *
 * @param password The password used for decryption.
 * @param line The encrypted line of text to be decrypted.
 * @return The decrypted line.
 */

auto decrypt(const std::string& password, const std::string &line) -> std::string {
    auto result = std::string();
    for (int i = 0; i < line.size(); ++i) {
        auto decryptedChar = char(((line[i]  - password.size() - 31) ^ password[i % password.size()]));
        result += decryptedChar;
    }
    return result;
}

/**
 * @brief Converts a line of text into a `Password` object.
 *
 * This function takes a line of text containing fields separated by "~" and converts
 * it to a `Password` object. The line is split into separate words and used to
 * construct a `Password` object with the appropriate number of fields.
 *
 * @param line The line of text to be converted into a `Password` object.
 * @return The `Password` object created from the input line.
 */

auto lineIntoObject(const std::string& line) -> Password {
    char separator = '~';
    std::stringstream ss(line);
    auto separateWords = std::vector<std::string>();

    auto word = std::string();
    while (getline(ss, word, separator)) {
        separateWords.push_back(word);
    }

    if (separateWords.size() == 3) {
        Password password(separateWords[0], separateWords[1], separateWords[2]);
        return password;
    } else if (separateWords.size() == 4) {
        Password password(separateWords[0], separateWords[1], separateWords[2], separateWords[3]);
        return password;
    } else if (separateWords.size() == 5) {
        Password password(separateWords[0], separateWords[1], separateWords[2], separateWords[3], separateWords[4]);
        return password;
    } else {
        fmt::print("\t◉ Error while creating file ◉\n");
        Password password("~error~", "", "");
        return password;
    }
}

/**
 * @brief Converts a `Password` object into a line of text.
 *
 * This function takes a `Password` object and converts its fields to a line of text, with
 * each field added to the line a '~' character is added to separate them from each other.
 *
 * @param object The `Password` object to be converted into a line of text.
 * @return The line of text representing the `Password` object.
 */

auto objectIntoLine(const Password& object) -> std::string {
    char separator = '~';
    auto line = std::string();
    auto objectFields = std::vector<std::string>();
    objectFields.push_back(object.getName());
    objectFields.push_back(object.getPassword());
    objectFields.push_back(object.getCategory());
    objectFields.push_back(object.getWebsite());
    objectFields.push_back(object.getLogin());

    for (const auto & objectField : objectFields) {
        line += objectField + separator;
    }

    return line;
}

auto goodFilePassword(const std::string& password, const std::filesystem::path& file) -> bool {
    auto inputFile = std::fstream();
    inputFile.open(file, std::ios::in);

    if (!inputFile.is_open()) {
        return false;
    }

    auto checkingLine = std::string();
    getline(inputFile, checkingLine);
    inputFile.close();

    auto decrypted = decrypt(password, checkingLine);

    if (decrypted == "verification") {
        return true;
    } else {
        return false;
    }
}

auto fileToVec(const std::string& password, const std::filesystem::path& file) -> std::vector<Password> {
    auto allPasswords = std::vector<Password>();
    auto inputFile = std::fstream();
    inputFile.open(file, std::ios::in);

    auto takingOutFirstLine = std::string();
    getline(inputFile, takingOutFirstLine);

    if (goodFilePassword(password, file)) {
        auto line = std::string();
        while (getline(inputFile, line)) {

            auto decrypted = decrypt(password, line);

            if (!decrypted.empty()) {
                auto object = lineIntoObject(decrypted);
                allPasswords.push_back(object);
            }

        }
    }

    inputFile.close();
    return allPasswords;
}

auto vecTofile(const std::string& password, const std::filesystem::path& file, const std::vector<Password>& allPasswords) -> void {
    auto outputFile = std::fstream();
    outputFile.open(file, std::ios::out);

    outputFile << encrypt(password, "verification") + '\n';


    for (const auto &object: allPasswords) {

        auto encrypted = encrypt(password, objectIntoLine(object));
        outputFile << encrypted + '\n';
    }

    outputFile.close();

    addMissingLines(file);
}

auto firstTimeEncrypt(const std::string& password, const std::filesystem::path& file) -> void {
    auto encryptedLines = std::vector<std::string>();

    auto inputFile = std::fstream();
    inputFile.open(file, std::ios::in);

    auto line = std::string();
    while (getline(inputFile, line)) {
        encryptedLines.push_back(encrypt(password, line));
    }
    inputFile.close();

    auto outputFile = std::fstream();
    outputFile.open(file, std::ios::out);

    for (const auto & encryptedLine : encryptedLines) {
        outputFile << encryptedLine + '\n';
    }
    outputFile.close();
}

auto addTimestamps(const std::filesystem::path& file) -> std::vector<std::string> {

    time_t currentTime = time(nullptr);
    tm *localTime = std::localtime(&currentTime);
    auto hour = std::to_string(localTime->tm_hour);
    auto minute = std::to_string(localTime->tm_min);
    auto second = std::to_string(localTime->tm_sec);

    if (hour.length() == 1) {
        hour = "0" + hour;
    }
    if (minute.length() == 1) {
        minute = "0" + minute;
    }
    if (second.length() == 1) {
        second = "0" + second;
    }

    auto timestamp = std::vector<std::string>{hour, minute, second};

    auto inputFile = std::fstream();
    inputFile.open(file, std::ios::in);

    auto allLines = std::vector<std::string>();
    auto line = std::string();

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            allLines.push_back(line);
        }
    } else {
        fmt::print("\t◉ Error ◉\n");
    }
    inputFile.close();

    allLines[1] = hour + allLines[1];

    if (allLines.size() % 2 == 1) {
        allLines[(allLines.size() - 1) / 2] = minute + allLines[(allLines.size() - 1) / 2];
    } else {
        allLines[allLines.size() / 2 - 1] = minute + allLines[allLines.size() / 2 - 1];
    }

    allLines[allLines.size() - 1] = second + allLines[allLines.size() - 1];

    auto outputFile = std::fstream();
    outputFile.open(file, std::ios::out);

    if (outputFile.is_open()) {
        for (const auto &l: allLines) {
            outputFile << l + '\n';
        }
    } else {
        fmt::print("\t◉ Error ◉\n");
    }
    outputFile.close();

    return timestamp;
}

auto addOldTimestamps(const std::filesystem::path& file, const std::vector<std::string>& timestamp) -> void {

    auto inputFile = std::fstream();
    inputFile.open(file, std::ios::in);

    auto allLines = std::vector<std::string>();
    auto line = std::string();

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            allLines.push_back(line);
        }
    } else {
        fmt::print("\t◉ Error ◉\n");
    }
    inputFile.close();

    allLines[1] = timestamp[0] + allLines[1];

    if (allLines.size() % 2 == 1) {
        allLines[(allLines.size() - 1) / 2] = timestamp[1] + allLines[(allLines.size() - 1) / 2];
    } else {
        allLines[allLines.size() / 2 - 1] = timestamp[1] + allLines[allLines.size() / 2 - 1];
    }

    allLines[allLines.size() - 1] = timestamp[2] + allLines[allLines.size() - 1];

    auto outputFile = std::fstream();
    outputFile.open(file, std::ios::out);

    if (outputFile.is_open()) {
        for (const auto &l: allLines) {
            outputFile << l + '\n';
        }
    } else {
        fmt::print("\t◉ Error ◉\n");
    }
    outputFile.close();

}

auto deleteTimestamps(const std::filesystem::path& file) -> void {

    auto inputFile = std::fstream();
    inputFile.open(file, std::ios::in);

    auto allLines = std::vector<std::string>();
    auto line = std::string();

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            allLines.push_back(line);
        }
    } else {
        fmt::print("\t◉ Error ◉\n");
    }
    inputFile.close();

    allLines[1] = allLines[1].substr(2);

    if (allLines.size() % 2 == 1) {
        allLines[(allLines.size() - 1) / 2] = allLines[(allLines.size() - 1) / 2].substr(2);
    } else {
        allLines[allLines.size() / 2 - 1] = allLines[allLines.size() / 2 - 1].substr(2);
    }

    allLines[allLines.size() - 1] = allLines[allLines.size() - 1].substr(2);

    auto outputFile = std::fstream();
    outputFile.open(file, std::ios::out);

    if (outputFile.is_open()) {
        for (const auto &l: allLines) {
            outputFile << l + '\n';
        }
    } else {
        fmt::print("\t◉ Error ◉\n");
    }
    outputFile.close();
}

auto showTimestamps(const std::filesystem::path& file) -> void {

    auto inputFile = std::fstream();
    inputFile.open(file, std::ios::in);

    auto allLines = std::vector<std::string>();
    auto line = std::string();

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            allLines.push_back(line);
        }
    } else {
        fmt::print("\t◉ Error ◉\n");
    }
    inputFile.close();

    auto hour = allLines[1].substr(0,2);

    auto minute = std::string();
    if (allLines.size() % 2 == 1) {
        minute = allLines[(allLines.size() - 1) / 2].substr(0, 2);
    } else {
        minute  = allLines[allLines.size() / 2 - 1].substr(0, 2);
    }

    auto second = allLines[allLines.size() - 1].substr(0, 2);

    fmt::print("\t◉ Current timestamp: {}:{}:{} ◉\n\n", hour, minute, second);

}
