#include "Sorting.h"
#include "Category.h"

#include <fmt/ranges.h>
#include <iostream>
#include <vector>
#include <regex>
#include <algorithm>

/**
 * @brief Provides sorting options for the user to choose from.
 *
 * This function prompts the user to select sorting options for the passwords. The user can
 * select multiple options. The function validates the user's input and returns a vector of
 * integers representing the selected sorting options.
 *
 * @return A vector of integers representing the selected sorting options.
 */

auto sortingOptions() -> std::vector<int> {
    auto options = std::vector<int>();
    auto option = std::string();
    auto repeat = std::string();
    auto repeatBool = true;
    
    fmt::print("\t◉ Avaliable sorting options ◉\n");
    fmt::print("\t◉ 1 - by Name ◉\n"
               "\t◉ 2 - by Password ◉\n"
               "\t◉ 3 - by Category ◉\n"
               "\t◉ 4 - by Website ◉\n"
               "\t◉ 5 - by Login ◉\n");
    do {
        fmt::print("\t◉ Enter sorting options one at a time ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, option);
        if (option == "~") {
            fmt::print("\t◉ Returned ◉\n");
            std::vector<int> back;
            return back;
        }

        auto pattern = std::regex("[1-5]");
        if (std::regex_match(option, pattern)) {
            options.push_back(std::stoi(option));
        } else {
            fmt::print("\t◉ Unrecognized value ◉\n");
        }

        fmt::print("\t◉ Want to add another option? (yes/no) ◉\n");
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

    return options;
}

auto sortPasswords(std::vector<Password>& allPasswords) -> void {
    auto options = sortingOptions();

    if (options.empty()) {
        return;
    }

    for (int i = options.size() - 1; i >= 0 ; i--) {
        switch (options[i]) {
            case 1:
                fmt::print("\t◉ Sorted by name.. ◉\n");
                std::ranges::stable_sort(allPasswords, {}, [](const Password& password)  {return password.getName();});
                break;
            case 2:
                fmt::print("\t◉ Sorted by password.. ◉\n");
                std::ranges::stable_sort(allPasswords, {}, [](const Password& password)  {return password.getPassword();});
                break;
            case 3:
                fmt::print("\t◉ Sorted by category.. ◉\n");
                std::ranges::stable_sort(allPasswords, {}, [](const Password& password)  {return password.getCategory();});
                break;
            case 4:
                fmt::print("\t◉ Sorted by website.. ◉\n");
                std::ranges::stable_sort(allPasswords, {}, [](const Password& password)  {return password.getWebsite();});
                break;
            case 5:
                fmt::print("\t◉ Sorted by login.. ◉\n");
                std::ranges::stable_sort(allPasswords, {}, [](const Password& password)  {return password.getLogin();});
                break;
        }
    }
    fmt::print("\t◉ Sorting is complete ◉\n");
}