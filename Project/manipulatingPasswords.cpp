#include "Encryption.h"
#include "manipulatingPasswords.h"

#include <fmt/ranges.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <regex>

#include <cstdlib>
#include <ctime>
#include <random>


auto passwordStrength(const std::string& password) -> void {
    auto strength = 0;
    if (password.size() > 8) {
        strength += 1;
    }
    std::regex upper("[A-Z]");
    std::regex lower("[a-z]");
    if (std::regex_search(password, upper) && std::regex_search(password, lower)) {
        strength += 1;
    }
    std::regex digits("[0-9]");
    if (std::regex_search(password, digits)) {
        strength += 1;
    }
    std::regex specialCharacters("[^a-zA-Z0-9]");
    if (std::regex_search(password, specialCharacters)) {
        strength += 1;
    }

    if (strength == 4) {
        fmt::print("\t◉ The password is very strong ◉\n");
    } else if (strength == 3) {
        fmt::print("\t◉ The password is strong ◉\n");
    } else if (strength == 2) {
        fmt::print("\t◉ The password is medium ◉\n");
    } else if (strength == 1){
        fmt::print("\t◉ The password is weak ◉\n");
    } else {
        fmt::print("\t◉ The password is very weak ◉\n");
    }
}

auto addPassword(std::vector<Password> &allPasswords) -> std::string {

    auto repeatPasswordBool = false;
    auto newPassword = std::string();
    do {
        repeatPasswordBool = false;
        fmt::print("\t◉ Enter the new password you want to add ◉\n");
        fmt::print("\t◉ Password should contain at least three characters and cannot contain the `~` character ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, newPassword);
        if (newPassword == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return "";
        }

        if (newPassword.size() < 3) {
            repeatPasswordBool = true;
        }

        if (newPassword.find('~') != std::string::npos) {
            repeatPasswordBool = true;
        }
    } while(repeatPasswordBool);

    auto passwordExists = false;
    auto decision = std::string();
    for (const auto& password : allPasswords) {
        if (password.getPassword() == newPassword) {
            passwordExists = true;
        }
    }
    if (passwordExists) {
        fmt::print("\t◉ Password is already in use type anything to continue or type `~` to quit ◉\n");
        getline(std::cin, decision);
        if (decision == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return "";
        }
    }

    return newPassword;
}

/**
 * @brief Letter generation.
 *
 * This function generates a random string of letters based on the specified number
 * of characters. It can include uppercase and lowercase letters based on the smallBigBool
 * parameter.
 *
 * @param charactersNumber Number of letters.
 * @param smallBigBool Should it include uppercase and lowercase letters.
 * @return A string representing the letters that will be used in the password generator.
 */

auto generateLetters(int charactersNumber, bool smallBigBool) -> std::string {
    auto result = std::string();
    srand(time(nullptr));

    auto lettersNumber = ((rand() % (charactersNumber - 2)) + 2);

    auto bigLetterNumber = 0;
    if (smallBigBool) {
        bigLetterNumber = ((rand() % (lettersNumber - 1)) + 1);
        for (int i = 0; i < bigLetterNumber; ++i) {
            result += (char)((rand() % 26) + 65);
        }
    }
    auto rest = lettersNumber - bigLetterNumber;
    for (int i = 0; i < rest; ++i) {
        result += (char)((rand() % 26) + 97);
    }

    return result;
}

/**
 * @brief Generation of special characters.
 *
 * This function generates a random string of special characters based on the specified number
 * of characters.
 *
 * @param specialNumber Number of special characters.
 * @return A string representing the special characters that will be used in the password generator.
 */

auto generateSpecials(int specialNumber) -> std::string {
    auto result = std::string();
    srand(time(nullptr));

    auto randomSpecialNumber = (rand() % (specialNumber) + 1);

    for (int i = 0; i < randomSpecialNumber; ++i) {

        auto section = ((rand() % 4) + 1);

        switch (section) {
            case 1:
                result += (char) ((rand() % 15) + 33);
                break;
            case 2:
                result += (char) ((rand() % 7) + 58);
                break;
            case 3:
                result += (char) ((rand() % 6) + 91);
                break;
            case 4:
                result += (char) ((rand() % 3) + 123);
                break;
        }
    }

    return result;
}

/**
 * @brief Digit generator.
 *
 * This function generates a random string of digits based on the number of
 * characters left, so there is a chance that the generated password will not have digits.
 *
 * @param letterNumber Remaining number of characters to be completed in the password.
 * @return A string representing the digits that will be used in the password generator.
 */

auto generateDigits(int letterNumber) -> std::string {
    auto result = std::string();
    srand(time(nullptr));

    for (int i = 0; i < letterNumber; ++i) {
        result += (char) ((rand() % 10) + 48);
    }
    return result;
}

auto generatePassword() -> std::string {

    fmt::print("\t◉ Password generator ◉\n");

    auto charactersNumber = std::string();
    fmt::print("\t◉ Enter the number of characters, at least three ◉\n");
    fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
    getline(std::cin, charactersNumber);
    if (charactersNumber == "~") {
        fmt::print("\t◉ Returned ◉\n");
        return "";
    }

    std::regex numbers("[3-9][0-9]*|[1-9][0-9]+");
    while (! std::regex_match(charactersNumber, numbers)) {
        fmt::print("\t◉ Wrong value, it is not a number, or it is too small ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, charactersNumber);
        if (charactersNumber == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return "";
        }
    }

    auto smallBig = std::string();
    auto smallBigBool = false;
    fmt::print("\t◉ Should the password contain uppercase and lowercase letters? (yes/no) ◉\n");
    fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
    getline(std::cin, smallBig);
    if (smallBig == "~") {
        fmt::print("\t◉ Returned ◉\n");
        return "";
    }

    while (smallBig != "yes" && smallBig != "no") {
        fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, smallBig);
        if (smallBig == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return "";
        }
    }

    if (smallBig == "yes") {
        smallBigBool = true;
    }

    auto specialCharacters = std::string();
    auto specialCharactersBool = false;
    fmt::print("\t◉ Should the password contain special characters(@ # $ etc.)? (yes/no) ◉\n");
    fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
    getline(std::cin, specialCharacters);
    if (specialCharacters == "~") {
        fmt::print("\t◉ Returned ◉\n");
        return "";
    }

    while (specialCharacters != "yes" && specialCharacters != "no") {
        fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, specialCharacters);
        if (specialCharacters == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return "";
        }
    }

    if (specialCharacters == "yes") {
        specialCharactersBool = true;
    }

    auto result = std::string();
    auto intValue = std::stoi(charactersNumber);

    auto specialNumber = 0;

    result = generateLetters(intValue, smallBigBool);
    if (specialCharactersBool) {
        specialNumber = intValue - result.size();
        result += generateSpecials(specialNumber);
    }
    auto digitNumber = intValue - result.size();
    result += generateDigits(digitNumber);


    for (int i = result.size() - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(result[i], result[j]);
    }

    return result;
}

auto newPasswordObject(std::vector<Password>& allPasswords, const std::set<std::string> &uniqueCategories) -> void {

    auto passwordPassword = std::string();
    auto repeatPassword = std::string();
    auto repeatPasswordBool = false;
    do {
        fmt::print("\t◉ Do you want to write the password yourself or should it be generated? (write/generate) ◉\n");
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
            passwordPassword = addPassword(allPasswords);
        } else if (decision == "generate") {
            passwordPassword = generatePassword();
        }
        if (passwordPassword.empty()) {
            return;
        }

        fmt::print("\t◉ Your new password: {} ◉\n", passwordPassword);
        passwordStrength(passwordPassword);
        fmt::print("\t◉ Do you want to repeat the password creation process? (yes/no) ◉\n");

        getline(std::cin, repeatPassword);
        while (repeatPassword != "yes" && repeatPassword != "no") {
            fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
            fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
            getline(std::cin, repeatPassword);
            if (repeatPassword == "~") {
                fmt::print("\t◉ Returned ◉\n");
                return;
            }
        }

        if (repeatPassword == "yes") {
            repeatPasswordBool = true;
        }
        else if (repeatPassword == "no") {
            repeatPasswordBool = false;
        }

    } while (repeatPasswordBool);

    //NAME
    auto passwordName = std::string();
    auto repeatNameBool = false;
    do {
        repeatNameBool = false;
        fmt::print("\t◉ Enter the new Name you want to add ◉\n");
        fmt::print("\t◉ Name should contain at least one characters and cannot contain the `~` character ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");

        getline(std::cin, passwordName);
        if (passwordName == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return;
        }

        if (passwordName.empty()) {
            repeatNameBool = true;
        }
        if (passwordName.find('~') != std::string::npos) {
            repeatNameBool = true;
        }
    } while(repeatNameBool);

    //CATEGORY
    auto passwordCategory = std::string();
    auto repeatCategoryBool = false;
    do {
        repeatCategoryBool = false;
        fmt::print("\t◉ Here are the available categories ◉\n");
        fmt::print("\t◉ {} ◉\n", uniqueCategories);
        fmt::print("\t◉ Enter one of the available categories that you want to use ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");

        getline(std::cin, passwordCategory);
        if (passwordCategory == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return;
        }
        if (passwordCategory.empty()) {
            repeatCategoryBool = true;
        }
        if (!uniqueCategories.contains(passwordCategory)) {
            repeatCategoryBool = true;
        }

        if (passwordCategory.find('~') != std::string::npos) {
            repeatCategoryBool = true;
        }
    } while(repeatCategoryBool);

    Password password(passwordName, passwordPassword, passwordCategory, "", "");

    //WEBSITE
    fmt::print("\t◉ Adding a website is not mandatory, do you want to add it? (yes/no) ◉\n");
    auto decisionWebsite = std::string();
    auto decisionBoolWebsite = true;

    getline(std::cin, decisionWebsite);
    while (decisionWebsite != "yes" && decisionWebsite != "no") {
        fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, decisionWebsite);
        if (decisionWebsite == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return;
        }
    }

    if (decisionWebsite == "no") {
        decisionBoolWebsite = false;
    }

    if (decisionBoolWebsite) {
        auto passwordWebsite = std::string();
        auto repeatWebsiteBool = false;
        do {
            repeatWebsiteBool = false;
            fmt::print("\t◉ Enter the new Website you want to add ◉\n");
            fmt::print("\t◉ Website should contain at least one characters and cannot contain the `~` character ◉\n");
            fmt::print("\t◉ If you want to go back, enter `~` ◉\n");

            getline(std::cin, passwordWebsite);
            if (passwordWebsite == "~") {
                fmt::print("\t◉ Returned ◉\n");
                return;
            }

            if (passwordWebsite.empty()) {
                repeatWebsiteBool = true;
            }
            if (passwordWebsite.find('~') != std::string::npos) {
                repeatWebsiteBool = true;
            }
        } while (repeatWebsiteBool);
        password.setWebsite(passwordWebsite);
    }

    //LOGIN
    fmt::print("\t◉ Adding a Login is not mandatory, do you want to add it? (yes/no) ◉\n");
    auto decisionLogin = std::string();
    auto decisionBoolLogin = true;

    getline(std::cin, decisionLogin);
    while (decisionLogin != "yes" && decisionLogin != "no") {
        fmt::print("\t◉ Unrecognized value, retype yes/no ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, decisionLogin);
        if (decisionLogin == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return;
        }
    }

    if (decisionLogin == "no") {
        decisionBoolLogin = false;
    }

    if (decisionBoolLogin) {
        auto passwordLogin = std::string();
        auto repeatLoginBool = false;
        do {
            repeatLoginBool = false;
            fmt::print("\t◉ Enter the new Login you want to add ◉\n");
            fmt::print("\t◉ Login should contain at least one characters and cannot contain the `~` character ◉\n");
            fmt::print("\t◉ If you want to go back, enter `~` ◉\n");

            getline(std::cin, passwordLogin);
            if (passwordLogin == "~") {
                fmt::print("\t◉ Returned ◉\n");
                return;
            }

            if (passwordLogin.empty()) {
                repeatLoginBool = true;
            }
            if (passwordLogin.find('~') != std::string::npos) {
                repeatLoginBool = true;
            }
        } while (repeatLoginBool);
        password.setLogin(passwordLogin);
    }

    allPasswords.push_back(password);
}