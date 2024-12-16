#include "Category.h"
#include "Encryption.h"

#include <fmt/ranges.h>

#include <vector>
#include <string>
#include <set>
#include <iostream>

auto avaliableCategories(const std::vector<Password> &allPasswords) -> std::set<std::string> {
    auto uniqueCategories = std::set<std::string>();

    for (const auto & category : allPasswords) {
        uniqueCategories.insert(category.getCategory());
    }
    return uniqueCategories;
}

auto addCategory(std::set<std::string> &uniqueCategories) -> void {
    auto newCategory = std::string();

    fmt::print("\t◉ Enter the name of the category you want to add ◉\n");
    fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
    getline(std::cin, newCategory);
    if (newCategory == "~") {
        fmt::print("\t◉ Returned ◉\n");
        return;
    }

    while (newCategory.empty()) {
        fmt::print("\t◉ Category should contain at least one character, enter the name again ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, newCategory);
        if (newCategory == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return;
        }
    }

    while (newCategory.find('~') != std::string::npos) {
        fmt::print("\t◉ Category should not contain `~` in the name, enter the name again ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, newCategory);
        if (newCategory == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return;
        }
    }

    if (!uniqueCategories.contains(newCategory)) {
        uniqueCategories.insert(newCategory);
    } else {
        fmt::print("\t◉ The specified category already exists ◉\n");
    }
}

auto deleteCategory(std::set<std::string> &uniqueCategories, std::vector<Password> &allPasswords) -> void {
    auto toDelete = std::string();
    fmt::print("\t◉ Enter the name of the category you want to delete ◉\n");
    fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
    getline(std::cin, toDelete);
    if (toDelete == "~") {
        fmt::print("\t◉ Returned ◉\n");
        return;
    }

    while (!uniqueCategories.contains(toDelete)) {
        fmt::print("\t◉ This category cannot be deleted because it does not exist, enter the name again ◉\n");
        fmt::print("\t◉ If you want to go back, enter `~` ◉\n");
        getline(std::cin, toDelete);
        if (toDelete == "~") {
            fmt::print("\t◉ Returned ◉\n");
            return;
        }
    }
    auto item = allPasswords.begin();
    while (item != allPasswords.end()) {
        if (item->getCategory() == toDelete) {
            item = allPasswords.erase(item);
        } else {
            item++;
        }
    }

    uniqueCategories.erase(toDelete);
}