#pragma once

#include <string>

/**
 * @class Password
 *
 * @brief Class representing a password.
 *
 * The Password class represents the password object, which contain variables
 * such as name, password, category, website, login. It provides methods to access
 * and modify these variables. The objects of the class are the lines of the .txt file
 * that represent the password.
 */

class Password {
private:
    std::string name;
    std::string password;
    std::string category;
    std::string website;
    std::string login;

public:
    Password(const std::string& name, const std::string& password, const std::string& category,
             const std::string& website = "", const std::string& login = "");

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getPassword() const;
    [[nodiscard]] std::string getCategory() const;
    [[nodiscard]] std::string getWebsite() const;
    [[nodiscard]] std::string getLogin() const;

    void setName(const std::string &name);

    void setPassword(const std::string &password);

    void setCategory(const std::string &category);

    void setWebsite(const std::string &website);

    void setLogin(const std::string &login);

};
