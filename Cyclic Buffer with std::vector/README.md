# Cyclic Buffer

## Description

This container implemented using STL std::vector for greated reliability, safety and performance. Using [Rule of zero](https://en.cppreference.com/w/cpp/language/rule_of_three). Shown below:

```cpp
explicit VectorCyclicBuffer(const VectorCyclicBuffer &) = default;
explicit VectorCyclicBuffer(VectorCyclicBuffer &&) = default;
VectorCyclicBuffer &operator=(const VectorCyclicBuffer &) = default;
VectorCyclicBuffer &operator=(VectorCyclicBuffer &&) = default;
virtual ~VectorCyclicBuffer() = default;
```

## Methods

1. explicit VectorCyclicBuffer(const size_t &) -> the only one constructor that isn't marked as "default". You should use it to create an object of this class.
2. constexpr size_t getSize() const -> returns size of vector.
3. constexpr size_t getCapacity() const -> returns capacity of vector.
4. constexpr T &getData(const size_t &) const -> returns certain element which index you specify.
5. auto &getBack() const -> returns last element from vector.
6. auto &getFront() const -> returns first element from vector.
7. constexpr bool empty() const -> returns "true" if vector is empty.
8. constexpr bool try_pushBack(const T &) -> returns true if vector can insert an element to the end.
9. constexpr bool try_pushFront(const T &) -> returns true if vector can insert an element to the beginning.
10. constexpr bool try_popBack() -> returns true if vector can erase an element from the end.
11. constexpr bool try_popFront() -> returns true if vector can erase an element from the beginning.
12. constexpr void printBuffer() const -> printing all elements from vector to the terminal.

## Compile

### GCC command:

```console
gcc main.cpp -lstdc++ -std=c++20 -Wall -Wpedantic -Wextra -o main
```

### Using CMake:

#### 1st

```console
cmake .
cmake --build .
```

#### 2nd

```console
cmake .
make
```

## Memory Leak Check

Because this container is implemented with STL container, there is no memory leaks or any errors. Command to check:

```console
valgrind --leak-check=yes -s ./main
```

Or if you want to dump it to file:

```console
valgrind --leak-check=yes -s --log-file="<your_file_name>" ./main
```

### Result

```
==26938== Memcheck, a memory error detector
==26938== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==26938== Using Valgrind-3.20.0 and LibVEX; rerun with -h for copyright info
==26938== Command: ./main
==26938== Parent PID: 19338
==26938==
==26938==
==26938== HEAP SUMMARY:
==26938==     in use at exit: 0 bytes in 0 blocks
==26938==   total heap usage: 3 allocs, 3 frees, 73,888 bytes allocated
==26938==
==26938== All heap blocks were freed -- no leaks are possible
==26938==
==26938== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

If you compare with [cyclic buffer implemented earlier](https://github.com/ViNN280801/ContainersCXX/tree/main/Cyclic%20Buffer), you will see a huge difference using the STL wrapper std::vector.
