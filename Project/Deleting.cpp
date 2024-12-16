#include "Deleting.h"
#include "Searching.h"

#include <fmt/ranges.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <regex>

/**
 * @brief Selects passwords to delete based on user input.
 *
 * This function prompts the user to select passwords to remove from the password
 * vector. First the passwords are searched based on the specified values, then the
 * user chooses whether to delete all the searched passwords or select specific passwords
 * from among the searched ones. Each password deletion, will need to be confirmed.
 *
 * @param allPasswords A vector containing all the passwords.
 * @return A vector of integers representing the indexes of the selected passwords to delete.
 *         An empty vector is returned if the user cancels or provides invalid input.
 */

auto selectedToDelete(const std::vector<Password>& allPasswords) -> std::vector<int> {

    auto indexes = searchPassword(allPasswords);
    auto indexesVec = std::vector<int>();

    fmt::print("\n");
    fmt::print("\t◉ Please select an option: ◉\n"
                   "\t◉ 1 - Delete all search terms ◉\n"
                   "\t◉ 2 - Select passwords to delete  ◉\n");

    auto decision = std::string();
    getline(std::cin, decision);

    while (decision != "1" && decision != "2") {
        fmt::print("\t◉ Unrecognized value, retype 1 or 2 ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, decision);
        if (decision == "~") {
            fmt::print("\t◉ Returned ◉\n");
            std::vector<int> back;
            return back;
        }
    }

    if (decision == "1") {
        for (auto i: indexes) {
            indexesVec.push_back(i);
        }

        auto remove = std::string();
        fmt::print("\t◉ Are you sure you want to delete them? (yes/no) ◉\n");
        getline(std::cin, remove);
        while (remove != "yes" && remove != "no") {
            fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
            fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
            getline(std::cin, remove);
            if (remove == "~") {
                fmt::print("\t◉ Returned ◉\n");
                std::vector<int> back;
                return back;
            }
        }
        if (remove == "no") {
            fmt::print("\t◉ Cancelled ◉\n");
            std::vector<int> back;
            return back;
        }
        return indexesVec;
    }

    auto selected = std::string();
    auto repeat = std::string();
    auto repeatBool = true;
    do {
        fmt::print("\t◉ Which password do you want to remove? ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, selected);
        if (decision == "~") {
            fmt::print("\t◉ Returned ◉\n");
            std::vector<int> back;
            return back;
        }

        auto pattern = std::regex("[1-9][0-9]*");

        if (std::regex_match(selected, pattern)) {
            auto intSelected = std::stoi(selected);
            intSelected -= 1;

            if (intSelected < indexes.size()) {

                auto iter = indexes.begin();
                for (int i = 0; i < intSelected; ++i) {
                    iter = std::next(iter, 1);
                }

                if (indexes.contains(*iter)) {

                    auto iterator = std::find(indexesVec.begin(), indexesVec.end(), *iter);

                    if (iterator == indexesVec.end()) {
                        indexesVec.push_back(*iter);
                    } else {
                        fmt::print("\t◉ You have already entered this password ◉\n");
                    }
                }
            } else {
                fmt::print("\t◉ Unrecognized value ◉\n");
            }
        } else {
            fmt::print("\t◉ Unrecognized value ◉\n");
        }

        fmt::print("\t◉ Want to choose another password? (yes/no) ◉\n");
        getline(std::cin, repeat);
        while (repeat != "yes" && repeat != "no") {
            fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
            fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
            getline(std::cin, repeat);
            if (repeat == "~") {
                fmt::print("\t◉ Returned ◉\n");
                std::vector<int> back;
                return back;
            }
        }

        if (repeat == "no") {
            repeatBool = false;
        }

    } while (repeatBool);

    auto remove = std::string();
    fmt::print("\t◉ Are you sure you want to delete them? (yes/no) ◉\n");
    getline(std::cin, repeat);
    while (repeat != "yes" && repeat != "no") {
        fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, repeat);
        if (repeat == "~") {
            fmt::print("\t◉ Returned ◉\n");
            std::vector<int> back;
            return back;
        }
    }
    if (repeat == "no") {
        fmt::print("\t◉ Cancelled ◉\n");
        std::vector<int> back;
        return back;
    }

    return indexesVec;
}


auto deletePassword(std::vector<Password>& allPasswords) -> void {

    auto toDelete = selectedToDelete(allPasswords);

    std::sort(toDelete.rbegin(), toDelete.rend()); //Highest to Lowest

    for (auto index : toDelete) {
        allPasswords.erase(allPasswords.begin() + index);
    }

    fmt::print("\t◉ Passwords have been removed ◉\n");
}