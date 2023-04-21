# Stack

## Description

This is a simple implementation of the stack data container, which is gets template type parameter. Linear data structure that stores template type of object. Serves as a container of objects that are inserted and removed according with LIFO rule (Last-In-First-Out) like a stack of plates.

## Compiling

There is file [autoconf.sh](https://github.com/ViNN280801/ContainersCXX/blob/main/Stack/autoconf.sh) that will compiles this project for you automatically. But if you want to do this by yourself, below are presented commands to do that:

### GNU GCC

```console
gcc -g -c main.cpp -lstdc++ -std=c++14 -Wall -Wpedantic -Wextra -o main.o
gcc main.o -lstdc++ -std=c++14 -o main
rm main.o
./main
```

### CMake

```console
cmake .
cmake --build .
./main
```
