#!/bin/bash

echo "Do you want to use GNU GCC (1) or CMake (2). Exit (#): "
while read choice; do
    if [[ "$choice" == "1" ]]; then
        gcc -g -c bintree.cpp -lstdc++ -std=c++17 -Wall -Wpedantic -Wextra -o bintree.o
        gcc -g -c main.cpp -lstdc++ -std=c++17 -Wall -Wpedantic -Wextra -o main.o
        gcc main.o bintree.o -lstdc++ -std=c++17 -o main
        rm bintree.o main.o
        ./main
        break
    elif [[ "$choice" == "2" ]]; then
        cmake .
        cmake --build .
        ./main
        break
    elif [[ "$choice" == "#" ]]; then
        echo "Exiting..."
        break
    fi
done
