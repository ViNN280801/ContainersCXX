# Simple Cyclic Buffer

## Description

This container presents ring buffer. This is a data structure that uses a single, fixed-size buffer as if it were connected end-to-end. This structure lends itself easily to buffering data streams.
More details [there](https://en.wikipedia.org/wiki/Circular_buffer).

## Methods

There is a template class with standard allocator that will be allocate memory for specified template parameter of a container. Default capacity of the cyclic buffer is 256 elements.
Capacity - is a value that determines how many elements this container can hold.
Size - is the direct number of elements that are currently stored in it.
Implementation uses 'struct' that contains raw pointer, current pos, current size of container and it capacity.

1.  void copyObj(const CyclicBuffer &) - auxiliary method for copying object to current object.
2.  void clearObj(CyclicBuffer &) - auxiliary method for clearing up specified object.
3.  explicit CyclicBuffer() - default constructor.
4.  explicit CyclicBuffer(const size_t &) - variety of default constructor.
5.  explicit CyclicBuffer(const CyclicBuffer &) - copy constructor.
6.  explicit CyclicBuffer(CyclicBuffer &&) - move constructor.
7.  CyclicBuffer &operator=(const CyclicBuffer &) - assignment operator.
8.  CyclicBuffer &operator=(CyclicBuffer &&) noexcept - move assignment operator.
9.  virtual ~CyclicBuffer() - virtual desctructor.
10. constexpr size_t getSize() const - returns current size of the container.
11. constexpr size_t getCapacity() const - returns current capacity of the container.
12. constexpr void resizeCapacity(const size_t &) - modifies default capacity of the container.
13. constexpr void insert(const T &) - inserting element to the container.
14. constexpr T &getData(const size_t &) const - returns element of container from the specified position.
15. constexpr void clear() - clearing up the container.
16. constexpr void printBuffer() const - prints elements of the container.

3 - 9 -> Using [Rule of five](https://en.cppreference.com/w/cpp/language/rule_of_three)

## Compile

For compile this. You need to write following commands:

```console
cmake .
cmake --build .
```

or

```console
cmake .
make
```

or

```console
gcc main.cpp -lstdc++ -std=c++14 -Wall -Wpedantic -Wextra -o main
```

## Memory Leak Check

To do memory leak check, I will use 'valgrind' tool. Log file will be located in this directory under the name "leaks_errors.log". How you could see, this class is badly designed, because i have a 18 errors, some of them in 'printBuffer()', some of them in 'insert()' methods.
To launch check you have to write following command:

```console
valgrind --leak-check=yes -s ./main
```

or if you want to redirect output to file:

```console
valgrind --leak-check=yes -s --log-file="<your_file_name>" ./main
```

Below you can see the output of the Valgrind leak check command.

### Output from Valgrind

```
==44089== Memcheck, a memory error detector
==44089== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==44089== Using Valgrind-3.20.0 and LibVEX; rerun with -h for copyright info
==44089== Command: ./main
==44089== Parent PID: 33452
==44089==
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4014E7: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e504 is 0 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x401501: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e508 is 4 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40151B: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e50c is 8 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x401535: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e510 is 12 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40154F: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e514 is 16 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x401569: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e518 is 20 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089== Invalid read of size 4
==44089==    at 0x401926: CyclicBuffer<int, std::allocator<int> >::printBuffer() const (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4015E1: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e504 is 0 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089== Invalid read of size 4
==44089==    at 0x401926: CyclicBuffer<int, std::allocator<int> >::printBuffer() const (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x401673: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e504 is 0 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089==
==44089== HEAP SUMMARY:
==44089==     in use at exit: 0 bytes in 0 blocks
==44089==   total heap usage: 4 allocs, 4 frees, 74,752 bytes allocated
==44089==
==44089== All heap blocks were freed -- no leaks are possible
==44089==
==44089== ERROR SUMMARY: 18 errors from 8 contexts (suppressed: 0 from 0)
==44089==
==44089== 1 errors in context 1 of 8:
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x401569: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e518 is 20 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089==
==44089== 1 errors in context 2 of 8:
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40154F: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e514 is 16 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089==
==44089== 1 errors in context 3 of 8:
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x401535: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e510 is 12 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089==
==44089== 1 errors in context 4 of 8:
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40151B: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e50c is 8 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089==
==44089== 1 errors in context 5 of 8:
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x401501: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e508 is 4 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089==
==44089== 1 errors in context 6 of 8:
==44089== Invalid write of size 4
==44089==    at 0x40187D: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4014E7: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e504 is 0 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089==
==44089== 6 errors in context 7 of 8:
==44089== Invalid read of size 4
==44089==    at 0x401926: CyclicBuffer<int, std::allocator<int> >::printBuffer() const (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x401673: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e504 is 0 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089==
==44089== 6 errors in context 8 of 8:
==44089== Invalid read of size 4
==44089==    at 0x401926: CyclicBuffer<int, std::allocator<int> >::printBuffer() const (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4015E1: main (in ${PATH}/Cyclic Buffer/main)
==44089==  Address 0x4d9e504 is 0 bytes after a block of size 4 alloc'd
==44089==    at 0x4843FF5: operator new(unsigned long) (vg_replace_malloc.c:434)
==44089==    by 0x401AD7: std::__new_allocator<int>::allocate(unsigned long, void const*) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x40184A: CyclicBuffer<int, std::allocator<int> >::insert(int const&) (in ${PATH}/Cyclic Buffer/main)
==44089==    by 0x4013CE: main (in ${PATH}/Cyclic Buffer/main)
==44089==
==44089== ERROR SUMMARY: 18 errors from 8 contexts (suppressed: 0 from 0)
```
