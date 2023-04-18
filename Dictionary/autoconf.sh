#!/bin/bash

echo "Do you want to use GNU GCC (1) or CMake (2). Exit (#): "
while read choice; do
    if [[ "$choice" == "1" ]]; then
        gcc -g -c src/dictionary.cpp -lstdc++ -std=c++23 -Wall -Wpedantic -Wextra -o dict.o
        gcc -g -c main.cpp -lstdc++ -std=c++23 -Wall -Wpedantic -Wextra -o main.o
        gcc dict.o main.o -lstdc++ -std=c++23 -o main
        rm dict.o main.o
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
