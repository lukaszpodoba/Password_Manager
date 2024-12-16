#include "Password.h"

#include <string>

Password::Password(const std::string &name,
                   const std::string &password,
                   const std::string &category,
                   const std::string &website,
                   const std::string &login) {
    this->name = name;
    this->password = password;
    this->category = category;
    this->website = website;
    this->login = login;
}

std::string Password::getName() const {
    return name;
}
std::string Password::getPassword() const {
    return password;
}
std::string Password::getCategory() const {
    return category;
}
std::string Password::getWebsite() const {
    return website;
}
std::string Password::getLogin() const {
    return login;
}


void Password::setName(const std::string &name) {
    Password::name = name;
}
void Password::setPassword(const std::string &password) {
    Password::password = password;
}
void Password::setCategory(const std::string &category) {
    Password::category = category;
}
void Password::setWebsite(const std::string &website) {
    Password::website = website;
}
void Password::setLogin(const std::string &login) {
    Password::login = login;
}

