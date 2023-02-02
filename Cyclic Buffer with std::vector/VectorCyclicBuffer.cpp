#include "VectorCyclicBuffer.hpp"

template <typename T, class Allocator>
struct VectorCyclicBuffer<T, Allocator>::BufData
{
    std::vector<T, Allocator> m_buf;
    size_t m_pos;
    size_t m_size;
    size_t m_frontElem;
    size_t m_backElem;
};

template <typename T, class Allocator>
VectorCyclicBuffer<T, Allocator>::VectorCyclicBuffer(const size_t &size)
{
    m_bufData.m_buf.resize(size);
    m_bufData.m_pos = 0UL;
    m_bufData.m_size = size;
    m_bufData.m_frontElem = size - 1UL;
    m_bufData.m_backElem = 0UL;
}

template <typename T, class Allocator>
constexpr size_t VectorCyclicBuffer<T, Allocator>::getSize() const
{
    return m_bufData.m_buf.size();
}

template <typename T, class Allocator>
constexpr size_t VectorCyclicBuffer<T, Allocator>::getCapacity() const
{
    return m_bufData.m_buf.capacity();
}

template <typename T, class Allocator>
constexpr T &VectorCyclicBuffer<T, Allocator>::getData(const size_t &pos) const
{
    return m_bufData.m_buf.at(pos);
}

template <typename T, class Allocator>
auto &VectorCyclicBuffer<T, Allocator>::getBack() const
{
    return m_bufData.m_buf.at((m_bufData.m_backElem - 1UL + m_bufData.m_size) % m_bufData.m_size);
}

template <typename T, class Allocator>
auto &VectorCyclicBuffer<T, Allocator>::getFront() const
{
    return m_bufData.m_buf.at((m_bufData.m_frontElem + 1UL) % m_bufData.m_size);
}

template <typename T, class Allocator>
constexpr bool VectorCyclicBuffer<T, Allocator>::empty() const
{
    return m_bufData.m_buf.empty();
}

template <typename T, class Allocator>
constexpr bool VectorCyclicBuffer<T, Allocator>::try_pushBack(const T &data)
{
    if (m_bufData.m_pos == m_bufData.m_size)
        return false;
    m_bufData.m_buf[m_bufData.m_backElem] = data;
    m_bufData.m_backElem = (m_bufData.m_backElem + 1UL) % m_bufData.m_size;
    m_bufData.m_size++;
    return true;
}

template <typename T, class Allocator>
constexpr bool VectorCyclicBuffer<T, Allocator>::try_pushFront(const T &data)
{
    if (m_bufData.m_pos == m_bufData.m_size)
        return false;
    m_bufData.m_buf[m_bufData.m_frontElem] = data;
    m_bufData.m_frontElem = (m_bufData.m_frontElem - 1UL + m_bufData.m_size) % m_bufData.m_size;
    m_bufData.m_size++;
    return true;
}

template <typename T, class Allocator>
constexpr bool VectorCyclicBuffer<T, Allocator>::try_popBack()
{
    if (m_bufData.m_pos == m_bufData.m_size)
        return false;
    m_bufData.m_backElem = (m_bufData.m_backElem - 1UL + m_bufData.m_size) % m_bufData.m_size;
    m_bufData.m_size--;
    return true;
}

template <typename T, class Allocator>
constexpr bool VectorCyclicBuffer<T, Allocator>::try_popFront()
{
    if (m_bufData.m_pos == m_bufData.m_size)
        return false;
    m_bufData.m_frontElem = (m_bufData.m_frontElem + 1UL) % m_bufData.m_size;
    m_bufData.m_size--;
    return true;
}

template <typename T, class Allocator>
constexpr void VectorCyclicBuffer<T, Allocator>::printBuffer() const
{
    for (T elem : m_bufData.m_buf)
    {
        std::cout << elem << ' ';
    }
    std::endl(std::cout);
}
