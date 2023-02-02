#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <iterator>

template <typename T, class Allocator = std::allocator<T>>
class VectorCyclicBuffer
{
private:
    struct BufData;
    BufData m_bufData;

public:
    explicit VectorCyclicBuffer(const VectorCyclicBuffer &) = default;
    explicit VectorCyclicBuffer(VectorCyclicBuffer &&) = default;
    VectorCyclicBuffer &operator=(const VectorCyclicBuffer &) = default;
    VectorCyclicBuffer &operator=(VectorCyclicBuffer &&) = default;
    virtual ~VectorCyclicBuffer() = default;

    explicit VectorCyclicBuffer(const size_t &);

    constexpr size_t getSize() const;
    constexpr size_t getCapacity() const;
    constexpr T &getData(const size_t &) const;
    auto &getBack() const;
    auto &getFront() const;

    constexpr bool empty() const;

    constexpr bool try_pushBack(const T &);
    constexpr bool try_pushFront(const T &);
    constexpr bool try_popBack();
    constexpr bool try_popFront();

    constexpr void printBuffer() const;
};
