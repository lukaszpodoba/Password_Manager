cmake_minimum_required(VERSION 3.25)
project(Project)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         a33701196adfad74917046096bf5a2aa0ab0bb50
)
FetchContent_MakeAvailable(fmt)

add_executable(Project main.cpp Password.cpp Password.h Menu.cpp Menu.h Encryption.cpp Encryption.h Category.cpp Category.h manipulatingPasswords.cpp manipulatingPasswords.h Searching.cpp Searching.h Editing.cpp Editing.h Deleting.cpp Deleting.h Sorting.cpp Sorting.h)
target_link_libraries(Project fmt)
