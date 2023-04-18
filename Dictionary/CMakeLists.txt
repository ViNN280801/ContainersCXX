cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(dict
        VERSION 1.0
        DESCRIPTION "This is an implementation of the dictionary (std::map)"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra")

add_executable(main main.cpp)
