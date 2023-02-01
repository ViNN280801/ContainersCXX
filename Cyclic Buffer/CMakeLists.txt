cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(CyclicBuffer
        VERSION 1.0
        DESCRIPTION "Implementation of cyclic buffer (ring buffer)"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra")

add_executable(main main.cpp)
