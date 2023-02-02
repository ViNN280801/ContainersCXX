cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(QueueCyclicBuffer
        VERSION 1.0
        DESCRIPTION "Implementation of cyclic buffer (ring buffer) using STL std::vector"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra")

add_executable(main main.cpp)