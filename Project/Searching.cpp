#include "Searching.h"
#include "Encryption.h"
#include "Category.h"

#include <fmt/ranges.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <regex>
#include <random>

/**
 * @brief Provides search options for the user to choose from.
 *
 * This function asks the user to select one of two search options: view all passwords or
 * search for a password by specific values, which will be displayed when this option is
 * selected. The function validates the user's input and returns a set of strings representing
 * the selected search options.
 *
 * @return A set of strings representing the selected search options.
 */

auto searchOptions() -> std::set<std::string> {

    fmt::print("\t◉ View all passwords - enter 1 ◉\n");
    fmt::print("\t◉ Search for a password by specific values - enter 2 ◉\n");

    auto decision = std::string();

    getline(std::cin, decision);
    while (decision != "1" && decision != "2") {
        fmt::print("\t◉ Unrecognized value, retype 1 or 2 ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, decision);
        if (decision == "~") {
            fmt::print("\t◉ Returned ◉\n");
            std::set<std::string> back;
            return back;
        }
    }

    if (decision == "1") {
        auto all = std::set<std::string>();
        all.insert("0");
        return all;
    }
    

    fmt::print("\t◉ Avaliable search options ◉\n");
    fmt::print("\t◉ 1 - by Name ◉\n"
               "\t◉ 2 - by Category ◉\n"
               "\t◉ 3 - by Website ◉\n"
               "\t◉ 4 - by Login ◉\n");
    fmt::print("\t◉ Enter options one at a time ◉\n");

    auto option = std::string();
    auto pattern = std::regex("[1-4]");
    auto decisionAnotherBool = true;

    auto pickedOptions = std::set<std::string>();
    do {
        
        fmt::print("\t◉ Select option ◉\n");
        getline(std::cin, option);
        
        if (pickedOptions.contains(option)) {
            fmt::print("\t◉ This option has already been given ◉\n");
        }

        if (regex_match(option, pattern)) {
            pickedOptions.insert(option);
        } else {
            fmt::print("\t◉ Option not found ◉\n");
        }

        fmt::print("\t◉ Want to add another option? (yes/no) ◉\n");

        auto decisionAnother = std::string();
        decisionAnotherBool = true;
            
        getline(std::cin, decisionAnother);
        while (decisionAnother != "yes" && decisionAnother != "no") {
            fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
            fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
            getline(std::cin, decisionAnother);
            if (decisionAnother == "~") {
                fmt::print("\t◉ Returned ◉\n");
                std::set<std::string> back;
                return back;
            }
        }

        if (decisionAnother == "no") {
            decisionAnotherBool = false;
        }

    } while (decisionAnotherBool);
     
    return pickedOptions;
}


auto searchPassword(const std::vector<Password>& allPasswords) -> std::set<int> {
    auto pickedOptions = searchOptions();
    auto indexes = std::set<int>();

    if (pickedOptions.empty()) {
        return indexes;
    }

    for (int i = 0; i < allPasswords.size(); ++i) {
        indexes.insert(i);
    }

    if (pickedOptions.contains("0")) {

        auto counter = 1;
        for (auto i : indexes) {
            fmt::print("\t◉ {} - name: {}, password: {}, category: {}, website: {}, login: {} ◉\n",
                       counter, allPasswords[i].getName(), allPasswords[i].getPassword(), allPasswords[i].getCategory(),
                       allPasswords[i].getWebsite(), allPasswords[i].getLogin());
            counter += 1;
        }
        fmt::print("\n");

        return indexes;
    }

    auto searching = std::string();
    if (pickedOptions.contains("1")) {
        fmt::print("\t◉ Enter the name by which you want to find passwords ◉\n");
        getline(std::cin, searching);
        for (int i = 0; i < allPasswords.size(); ++i) {
            if (allPasswords[i].getName().find(searching) == std::string::npos) {
                indexes.erase(i);
            }
        }
    }

    if (pickedOptions.contains("2")) {
        fmt::print("\t◉ Enter the category by which you want to find passwords ◉\n");
        fmt::print("\t◉ Here are the available categories ◉\n");
        fmt::print("\t◉ {} ◉\n", avaliableCategories(allPasswords));
        getline(std::cin, searching);
        for (int i = 0; i < allPasswords.size(); ++i) {
            if (allPasswords[i].getCategory().find(searching) == std::string::npos) {
                indexes.erase(i);
            }
        }
    }

    if (pickedOptions.contains("3")) {
        fmt::print("\t◉ Enter the website by which you want to find passwords ◉\n");
        getline(std::cin, searching);
        for (int i = 0; i < allPasswords.size(); ++i) {
            if (allPasswords[i].getWebsite().find(searching) == std::string::npos) {
                indexes.erase(i);
            }
        }
    }

    if (pickedOptions.contains("4")) {
        fmt::print("\t◉ Enter the Login by which you want to find passwords ◉\n");
        getline(std::cin, searching);
        for (int i = 0; i < allPasswords.size(); ++i) {
            if (allPasswords[i].getLogin().find(searching) == std::string::npos) {
                indexes.erase(i);
            }
        }
    }

    fmt::print("\t◉ Passwords that meet your criteria ◉\n");
    auto counter = 1;
    for (auto i : indexes) {
        fmt::print("\t◉ {} - name: {}, password: {}, category: {}, website: {}, login: {} ◉\n",
                   counter, allPasswords[i].getName(), allPasswords[i].getPassword(), allPasswords[i].getCategory(),
                   allPasswords[i].getWebsite(), allPasswords[i].getLogin());
        counter += 1;
    }

    return indexes;
}