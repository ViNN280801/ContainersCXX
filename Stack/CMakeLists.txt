cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(bintree
        VERSION 1.0
        DESCRIPTION "This is an implementation of the binary tree"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra")

add_executable(main main.cpp)
