#include "Menu.h"
#include "Encryption.h"
#include "Category.h"
#include "manipulatingPasswords.h"
#include "Searching.h"
#include "Editing.h"
#include "Deleting.h"
#include "Sorting.h"

#include <fmt/ranges.h>
#include <iostream>
#include <vector>
#include <filesystem>

auto main() -> int {
    auto vec = std::vector<Password>();
    auto filePassword = std::string();
    auto timestamp = std::vector<std::string>();

    do {
        auto pickedFile = pickFile();

        if (pickedFile.empty()) {
            return 0;
        }

        if (std::filesystem::file_size(pickedFile) == 0) {
            fmt::print("\t◉ The file is empty, enter the password based on which it will be encrypted ◉\n");
            getline(std::cin, filePassword);
            timestamp = prepareFile(filePassword, pickedFile);
        } else {
            do {
                if (pickedFile.empty()) {
                    return 0;
                }
                fmt::print("\t◉ Enter the correct password for the source file ◉\n");
                fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
                getline(std::cin, filePassword);
                try {
                    deleteTimestamps(pickedFile);
                } catch (std::out_of_range& e) {
                    fmt::print("\t◉ Unsupported file ◉\n");
                    return  0;
                }
                timestamp = addTimestamps(pickedFile);

                if (filePassword == "~") {
                    fmt::print("\t◉ Returned ◉\n");
                    pickedFile = pickFile();
                }
            } while (!goodFilePassword(filePassword, pickedFile));
            fmt::print("\t◉ Correct source file password ◉\n\n");
        }
        deleteTimestamps(pickedFile);
        vec = fileToVec(filePassword, pickedFile);
        addOldTimestamps(pickedFile, timestamp);

        auto command = std::string();
        auto categories = avaliableCategories(vec);

        auto running = true;

        do {
            fmt::print("\t◉ -=-=-=-=-=-=- MENU -=-=-=-=-=-=- ◉\n");
            fmt::print("\t◉ Choose one of the commands below: ◉\n"
                       "\t◉ 1 - Search for passwords ◉\n"
                       "\t◉ 2 - Sort passwords ◉\n"
                       "\t◉ 3 - Add password ◉\n"
                       "\t◉ 4 - Edit password ◉\n"
                       "\t◉ 5 - Delete password ◉\n"
                       "\t◉ 6 - Add Category ◉\n"
                       "\t◉ 7 - Delete Category ◉\n"
                       "\t◉ 8 - Show timestamp ◉\n"
                       "\t◉ 9 - Change source file ◉\n"
                       "\t◉ 10 - Exit ◉\n");
            fmt::print("\t◉ -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- ◉\n");
            getline(std::cin, command);

            if (command == "1") {
                searchPassword(vec);
            } else if (command == "2") {
                sortPasswords(vec);
            } else if (command == "3") {
                if (!categories.empty()) {
                    newPasswordObject(vec, categories);
                } else {
                    fmt::print("\t◉ No categories to create passwords, add categories first ◉\n");
                }
            } else if (command == "4") {
                editPassword(vec);
            } else if (command == "5") {
                deletePassword(vec);
            } else if (command == "6") {
                addCategory(categories);
            } else if (command == "7") {
                deleteCategory(categories, vec);
            } else if (command == "8") {
                showTimestamps(pickedFile);
            } else if (command == "9") {
                fmt::print("\t◉ Saving changes... ◉\n");
                running = false;
            } else if (command == "10") {
                fmt::print("\t◉ Saving changes and exiting... ◉\n");
                vecTofile(filePassword, pickedFile, vec);
                addOldTimestamps(pickedFile, timestamp);
                return 0;
            } else {
                fmt::print("\t◉ There is no such command ◉\n\n");
            }
        } while (running);
        vecTofile(filePassword, pickedFile, vec);
        addOldTimestamps(pickedFile, timestamp);
    } while (true);
}

