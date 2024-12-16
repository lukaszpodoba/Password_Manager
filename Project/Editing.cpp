#include "Searching.h"
#include "Encryption.h"
#include "Category.h"
#include "manipulatingPasswords.h"

#include <fmt/ranges.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <regex>
#include <random>

/**
 * @brief Provides a set of available edit options.
 *
 * This function displays a menu of edit options and allows the user to select multiple options.
 * The user can choose to edit the name, password, category, website, and login of a password.
 *
 * @return A set of strings representing the selected edit options.
 */

auto editOptions() -> std::set<std::string> {

    fmt::print("\t◉ Avaliable edit options ◉\n");
    fmt::print("\t◉ 1 - Name ◉\n"
               "\t◉ 2 - Password ◉\n"
               "\t◉ 3 - Category ◉\n"
               "\t◉ 4 - Website ◉\n"
               "\t◉ 5 - Login ◉\n");
    fmt::print("\t◉ Enter options one at a time ◉\n");

    auto option = std::string();
    auto pattern = std::regex("[1-5]");
    auto decisionBool = true;

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

        auto decision = std::string();
        decisionBool = true;

        getline(std::cin, decision);
        while (decision != "yes" && decision != "no") {
            fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
            fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
            getline(std::cin, decision);
            if (decision == "~") {
                fmt::print("\t◉ Returned ◉\n");
                std::set<std::string> back;
                return back;
            }
        }

        if (decision == "no") {
            decisionBool = false;
        }

    } while (decisionBool);

    return pickedOptions;
}

auto editPassword(std::vector<Password>& allPasswords) -> void {

    auto selected = std::string();

    auto indexes = searchPassword(allPasswords);
    if (indexes.empty()) {
        return;
    }

    auto decisionBool = true;
    do {

        fmt::print("\t◉ Select password you want to edit ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, selected);
        if (selected == "~") {
            fmt::print("\t◉ Returned ◉\n");
            std::set<std::string> back;
            return;
        }

        auto intSelected = std::stoi(selected);
        auto pattern = std::regex("[1-9][0-9]*");
        if (std::regex_match(selected, pattern)) {

            intSelected -= 1;
            if (intSelected < indexes.size()) {

                auto options = editOptions();

                //EDITING NAME
                if (options.contains("1")) {
                    auto edit = std::string();
                    auto repeatEdit = false;
                    do {
                        repeatEdit = false;
                        fmt::print("\t◉ Name should contain at least one character and cannot contain the `~` character ◉\n");
                        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
                        getline(std::cin, edit);
                        if (edit == "~") {
                            fmt::print("\t◉ Returned ◉\n");
                            return;
                        }
                        if (edit.empty()) {
                            repeatEdit = true;
                        }
                        if (edit.find('~') != std::string::npos) {
                            repeatEdit = true;
                        }
                    } while(repeatEdit);


                    auto iter = indexes.begin();
                    for (int i = 0; i < intSelected; ++i) {
                        iter = std::next(iter, 1);
                    }

                    allPasswords[*iter].setName(edit);
                }

                //EDITING PASSWORD
                if (options.contains("2")) {
                    auto edit = std::string();
                    auto repeatEdit = std::string();
                    auto repeatEditBool = false;
                    do {
                        fmt::print("\t◉ Do you want to write the  new password yourself or should it be generated? (write/generate) ◉\n");
                        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");

                        auto decision = std::string();
                        getline(std::cin, decision);
                        if (decision == "~") {
                            fmt::print("\t◉ Returned ◉\n");
                            return;
                        }

                        while (decision != "write" && decision != "generate") {
                            fmt::print("\t◉ Unrecognized value, retype write/generate ◉\n");
                            fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
                            getline(std::cin, decision);
                            if (decision == "~") {
                                fmt::print("\t◉ Returned ◉\n");
                                return;
                            }
                        }

                        if (decision == "write") {
                            edit = addPassword(allPasswords);
                        } else if (decision == "generate") {
                            edit = generatePassword();
                        }
                        if (edit.empty()) {
                            return;
                        }

                        fmt::print("\t◉ Your new password: {} ◉\n", edit);
                        passwordStrength(edit);
                        fmt::print("\t◉ Do you want to repeat the password creation process? (yes/no) ◉\n");

                        getline(std::cin, repeatEdit);
                        while (repeatEdit != "yes" && repeatEdit != "no") {
                            fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
                            fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
                            getline(std::cin, repeatEdit);
                            if (repeatEdit == "~") {
                                fmt::print("\t◉ Returned ◉\n");
                                return;
                            }
                        }

                        if (repeatEdit == "yes") {
                            repeatEditBool = true;
                        }
                        else if (repeatEdit == "no") {
                            repeatEditBool = false;
                        }

                    } while (repeatEditBool);

                    auto iter = indexes.begin();
                    for (int i = 0; i < intSelected; ++i) {
                        iter = std::next(iter, 1);
                    }

                    allPasswords[*iter].setPassword(edit);
                }

                //EDITING CATEGORY
                if (options.contains("3")) {
                    auto edit = std::string();
                    auto repeatEdit = false;
                    auto categories = avaliableCategories(allPasswords);
                    do {
                        repeatEdit = false;
                        fmt::print("\t◉ Here are the available categories ◉\n");
                        fmt::print("\t◉ {} ◉\n", categories);
                        fmt::print("\t◉ Enter one of the available categories that you want to use ◉\n");
                        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");

                        getline(std::cin, edit);
                        if (edit == "~") {
                            fmt::print("\t◉ Returned ◉\n");
                            return;
                        }
                        if (edit.empty()) {
                            repeatEdit = true;
                        }
                        if (!categories.contains(edit)) {
                            repeatEdit = true;
                        }

                        if (edit.find('~') != std::string::npos) {
                            repeatEdit = true;
                        }
                    } while(repeatEdit);

                    auto iter = indexes.begin();
                    for (int i = 0; i < intSelected; ++i) {
                        iter = std::next(iter, 1);
                    }

                    allPasswords[*iter].setCategory(edit);
                }

                //EDITING WEBSITE
                if (options.contains("4")) {
                    auto edit= std::string();
                    auto repeatEdit = false;
                    do {
                        repeatEdit = false;
                        fmt::print("\t◉ Enter the new Website you want to add ◉\n");
                        fmt::print("\t◉ Website should contain at least one characters and cannot contain the `~` character ◉\n");
                        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");

                        getline(std::cin, edit);
                        if (edit == "~") {
                            fmt::print("\t◉ Returned ◉\n");
                            return;
                        }

                        if (edit.empty()) {
                            repeatEdit = true;
                        }
                        if (edit.find('~') != std::string::npos) {
                            repeatEdit = true;
                        }
                    } while (repeatEdit);

                    auto iter = indexes.begin();
                    for (int i = 0; i < intSelected; ++i) {
                        iter = std::next(iter, 1);
                    }

                    allPasswords[*iter].setWebsite(edit);
                }

                //EDITING LOGIN
                if (options.contains("5")) {
                    auto edit = std::string();
                    auto repeatEdit = false;
                    do {
                        repeatEdit = false;
                        fmt::print("\t◉ Enter the new Login you want to add ◉\n");
                        fmt::print("\t◉ Login should contain at least one characters and cannot contain the `~` character ◉\n");
                        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");

                        getline(std::cin, edit);
                        if (edit == "~") {
                            fmt::print("\t◉ Returned ◉\n");
                            return;
                        }

                        if (edit.empty()) {
                            repeatEdit = true;
                        }
                        if (edit.find('~') != std::string::npos) {
                            repeatEdit = true;
                        }
                    } while (repeatEdit);

                    auto iter = indexes.begin();
                    for (int i = 0; i < intSelected; ++i) {
                        iter = std::next(iter, 1);
                    }

                    allPasswords[*iter].setLogin(edit);
                }
            }

        } else {
            fmt::print("\t◉ Unrecognized value ◉\n");
        }

        fmt::print("\t◉ Want to edit another password? (yes/no) ◉\n");

        auto decision = std::string();
        decisionBool = true;

        getline(std::cin, decision);
        while (decision != "yes" && decision != "no") {
            fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
            fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
            getline(std::cin, decision);
            if (decision == "~") {
                fmt::print("\t◉ Returned ◉\n");
                return;
            }
        }

        if (decision == "no") {
            decisionBool = false;
        }

    } while (decisionBool);

}