#include "Menu.h"
#include "Encryption.h"

#include <fmt/ranges.h>

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <fstream>

/**
 * @brief The available text files
 *
 * This function searches the given directory path and returns
 * a vector containing the names of all the text files found, excluding the
 * "CMakeLists.txt" file.
 *
 * @return A vector of strings containing the names of the available text files.
 */

auto avaliableTxtFiles() -> std::vector<std::string> {
    auto txtFiles = std::vector<std::string>();
    auto directoryPath = std::filesystem::current_path().parent_path();
    auto directoryIterator = std::filesystem::directory_iterator(directoryPath);
    // Iterate through each file in the directory
    for (auto const &entry : directoryIterator) {
        if (entry.path().extension() == ".txt" &&
            entry.path().filename() != "CMakeLists.txt") {
            txtFiles.push_back(entry.path().filename().string());
        }
    }
    return txtFiles;
}

auto pickFile() -> std::filesystem::path {
    auto directoryPath = std::filesystem::current_path().parent_path();
    auto txtFiles = avaliableTxtFiles();
    auto pickedFilePath = std::filesystem::path();
    auto validFile = true;

    do {
        fmt::print("\t◉ Please select one of the following files by entering its name ◉\n");
        for (auto txtFile : txtFiles) {
            fmt::print("{}\n", txtFile);
        }
        fmt::print("\t◉ Or enter a direct absolute path to the file ◉\n");
        fmt::print("\t◉ If you want to exit, enter `~` ◉\n");
        auto pickedFile = std::string();
        std::getline(std::cin, pickedFile);
        pickedFilePath = pickedFile;

        if (pickedFile == "~") {
            return "";
        }

        if (pickedFilePath.extension() == ".txt" && std::filesystem::exists(pickedFilePath)) {
            validFile = false;
        } else if (std::find(txtFiles.begin(), txtFiles.end(), pickedFile) != txtFiles.end()) {
            pickedFilePath = directoryPath / pickedFile;
            validFile = false;
        }
    } while (validFile);

    fmt::print("\t◉ Succes! The file has been found ◉\n");

    return pickedFilePath;
}

auto prepareFile(const std::string& password, const std::filesystem::path& file) -> std::vector<std::string> {

    auto outputFile = std::fstream();
    outputFile.open(file, std::ios::out);

    if (outputFile.is_open()) {
        outputFile << "verification" << '\n';
        outputFile << '\n';
        outputFile << '\n';
        outputFile << '\n';
        outputFile << '\n';
    } else {
        fmt::print("\t◉ Error, when opening the file ◉\n");
    }
    outputFile.close();

    firstTimeEncrypt(password, file);

    auto timestamp = addTimestamps(file);
    return timestamp;
}

auto addMissingLines(const std::filesystem::path& file) -> void {
    auto inFile = std::vector<std::string>();

    auto inputFile = std::fstream();
    inputFile.open(file, std::ios::in);
    int lineCount = 0;

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            inFile.push_back(line);
            lineCount++;
        }
    }
    inputFile.close();

    auto outputFile = std::fstream();
    outputFile.open(file, std::ios::out);
    if (outputFile.is_open()) {

        for (const auto & i : inFile) {
            outputFile << i + '\n';
        }

        int linesToAdd = 5 - lineCount;
        for (int i = 0; i < linesToAdd; i++) {
            outputFile << '\n';
        }
    }
    outputFile.close();
}

