cmake_minimum_required(VERSION 3.12)

project(HW LANGUAGES CXX C)

add_executable(${PROJECT_NAME} main.cpp HW.hpp)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)