# Binary Tree

## Description

This repository stores implementation of the [binary tree](https://en.wikipedia.org/wiki/Binary_tree) container with template parameter, also, it has some usefull methods for interoperate with it. A binary tree is a tree data structure where each node has up to two child nodes, creating the branches of the tree. The two children are usually called the left and right nodes. Parent nodes are nodes with children, while child nodes may include references to their parents.

## Compiling

There is file [autoconf.sh](https://github.com/ViNN280801/ContainersCXX/blob/main/Binary%20Tree/autoconf.sh) that will compiles this project for you automatically. But if you want to do this by yourself, below are presented commands to do that:

### GNU GCC

```console
gcc -g -c bintree.cpp -lstdc++ -std=c++23 -Wall -Wpedantic -Wextra -o bintree.o
gcc -g -c main.cpp -lstdc++ -std=c++23 -Wall -Wpedantic -Wextra -o main.o
gcc main.o bintree.o -lstdc++ -std=c++23 -o main
rm bintree.o main.o
./main
```

### CMake

```console
cmake .
cmake --build .
./main
```

## Dependencies

As you can see in the [Compiling](https://github.com/ViNN280801/ContainersCXX/tree/main/Binary%20Tree#compiling) section this project is compiled minimum from [C++ 17](https://en.cppreference.com/w/cpp/17) standard version, because this container uses [if constexpr](https://en.cppreference.com/w/cpp/language/if) and [std::is_copy_assignable_v<>](https://en.cppreference.com/w/cpp/types/is_copy_assignable):

```cpp
if ((nodeNumber == 0) or (nodeNumber >= count(root)))
        if constexpr (std::is_copy_assignable_v<T>)
            pnode->value = T{};
```

## Example

This example will run tests from the 'main.cpp'

#### View binary tree

<img src=img/1.png>

#### Removing node

<img src=img/2.png>
