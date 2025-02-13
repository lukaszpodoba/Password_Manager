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

![XOR Gate](https://www.google.com/search?sca_esv=abfc99f64281ab7f&rlz=1C5CHFA_enPL1025PL1025&sxsrf=AHTn8zqHzDiG2nUDcCPionEWy-L1bYLrVw:1739448569094&q=xor+gate&udm=2&fbs=ABzOT_C6HZESFBpD-a6wBwrIm2041RevU0T3J6J8ChyWSMUzXpQcs9IBg_JPcxguI_6368qJoebdPzCfPr234SkajgK_K3Vfx92eqV5d3fcoF1LFckIAwyk_zdrk9lrEvf_5BHHb_tuBGmg6TIaP3IQBZXckf2ZNhjMSuZt9LwIrJxnEqeXUv2l4AF8cF8IZDWfJ94Z48ZCW&sa=X&sqi=2&ved=2ahUKEwjomMPwzsCLAxU1R_EDHSPBAzUQtKgLegQIFxAB&biw=1837&bih=846&dpr=1#vhid=LgYC0AU9iC-gxM&vssid=mosaic)

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
