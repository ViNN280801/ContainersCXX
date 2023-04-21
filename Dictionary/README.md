# Dictionary

## Description

This container is something like a std::map, but very simple version. Base of this container is binary search tree, therefore there is no template parameter 'Comp' that which would sort the elements in special order, i.e. there is no possibility of custrom comparing elements in a dictionary. Keys are sorted by using the comparison function Compare. Search, removal, and insertion operations have logarithmic complexity. Maps are usually implemented as [red-black trees](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree). And so far there are no any type of iterators.

## Compiling

There is file [autoconf.sh](https://github.com/ViNN280801/ContainersCXX/blob/main/Binary%20Tree/autoconf.sh) that will compiles this project for you automatically. But if you want to do this by yourself, below are presented commands to do that:

### GNU GCC

```console
gcc -g -c main.cpp -lstdc++ -std=c++23 -Wall -Wpedantic -Wextra -o main.o
gcc main.o -lstdc++ -std=c++23 -o main
rm main.o
./main
```

### CMake

```console
cmake .
cmake --build .
./main
```

## Methods

There are some simple method that allow to get an element by passing key, inserting new element, erasing element by key, etc.

```cpp
// Returns count of elements in the dictionary
constexpr size_t size() const;

// Checks if container is empty
// Returns "true" if empty, ohterwise - "false"
constexpr bool empty() const;

// ReturnsErasing all elements from the container
void clear() noexcept;

// ReturnsThrows an exception if there is no such key
// Returns Key of root (head) node if exists
virtual Key const &get_key() const noexcept override;

// Gets a value in dictionary by specified key
// Template parameter key - key of element that you want to find
// Returns Value associated with 'key' parameter
// If there is no specified key in the container
// returns standard null value for 'Value' type (works like an "operator[]")
virtual const Value &get(Key const &key) const override;

// Gets a value in dictionary by specified key
// @throw Exception "std::out_of_range" if there is no key in the container
// Template parameter key - key of element that you want to find
// Returns Value associated with 'key' parameter
const Value &at(Key const &key) const;

// Modifies value associated with 'key'
// Template parameter key - certain key that stores value
// Template parameter value - new value to set
virtual constexpr void set(Key const &key, const Value &value) override;

// Checks if 'key' stores any element
// Template parameter key - key which is being checked on availavility of value
// Returns "true" if 'key' is associated with some value, otherwise - "false"
virtual constexpr bool is_set(Key const &key) const override;

// Inserting new element to the container
// Template parameter key - key to which will be inserted value
// Template parameter value - value to insert
constexpr void insert(Key const &key, Value const &value);

// ReturnsErases node by it key, if container is empty or there
// is no node with specified key - calling "return;"
// Template parameter key - key to search to erase node
constexpr void erase(Key const &key);

// Access to the min element
// Returns Min value from container
constexpr Value &min() const;

// Access to the max element
// Returns Max value from container
constexpr Value &max() const;
```
