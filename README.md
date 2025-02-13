# C++ Password Manager

## Overview
**Password Manager** is a console-based application developed in C++ that provides secure management and storage of passwords. The application enables users to create, edit, search, sort, and delete saved passwords while ensuring that all sensitive data is encrypted before being stored in a text file.

## Technologies & Tools
- **C++20 & CMake**:  
  - The project is built using C++20, with CMake handling the build configuration.
  - The CMakeLists.txt file fetches the **fmt** library to simplify text formatting and enhance console output readability.  
- **fmt Library**:  
  - Used to format console messages elegantly, improving the overall user interaction experience.

## Project Structure
### Password & Data Management
- **Files**: `Password.h` / `Password.cpp`
- **Description**:  
  - Defines the `Password` class that stores key information such as the name, password, category, website, and login.
  - Provides getter and setter methods to manage these attributes effectively.

### Encryption & Decryption
- **Files**: `Encryption.h` / `Encryption.cpp`
- **Description**:  
  - Implements an XOR-based encryption algorithm with additional modifications (such as adding the password length and a constant value) to secure the data.
  - Includes functions `encrypt` and `decrypt` for securing the passwords.
  - Provides utilities to convert between text lines and `Password` objects.

![XOR Gate](https://www.google.com/imgres?q=xor%20gate&imgurl=https%3A%2F%2Fwww.analog.com%2Fen%2F_%2Fmedia%2Fanalog%2Fen%2Fdesign-center%2Fglossary%2Fxor-gate-symbol.jpg%3Frev%3Db3d6c2e239cd4f6eba77eacf0b65be9c&imgrefurl=https%3A%2F%2Fwww.analog.com%2Fen%2Fresources%2Fglossary%2Fxor-gate.html&docid=eXEGOswbb7Td5M&tbnid=QuUwKrjdh7ZMpM&vet=12ahUKEwiS6bXxzsCLAxV1FhAIHS9NB8QQM3oECBsQAA..i&w=326&h=206&hcb=2&ved=2ahUKEwiS6bXxzsCLAxV1FhAIHS9NB8QQM3oECBsQAA)

### User Interaction
- **Files**: `Menu.h` / `Menu.cpp`
- **Description**:  
  - Handles the selection of the source file (the text file containing passwords) and its preparation (including writing a verification line and adding timestamps).
  - Presents the main interactive menu where users can choose various operations.

### Searching, Sorting, Editing, & Deleting
- **Description**:  
  - Implements modules for searching passwords based on different criteria, sorting the list, and editing or deleting records.
  - Enables interactive management of the password list.

### Password Manipulation & Generator
- **Files**: `manipulatingPasswords.h` / `manipulatingPasswords.cpp`
- **Description**:  
  - Contains functions to assess password strength based on length, and the presence of letters, digits, and special characters.
  - Includes a random password generator that creates passwords according to user-defined parameters.

## Key Functionalities
- **File Encryption/Decryption**:  
  - The application encrypts the file containing saved passwords using a user-provided key.
  - The first line of the file holds an encrypted "verification" value, ensuring that the correct password is used to access the file.
- **Interactive Menu**:  
  - Offers options for searching, sorting, adding, editing, and deleting passwords.
  - Supports category management to group passwords effectively.
- **Password Generator**:  
  - Generates random passwords with options to include uppercase and lowercase letters, digits, and special characters.
- **Timestamps**:  
  - Adds timestamps to the file, which can be useful for monitoring changes and providing an extra layer of security.
