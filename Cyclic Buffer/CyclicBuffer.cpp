#include "CyclicBuffer.hpp"

template <typename T, class Allocator>
struct CyclicBuffer<T, Allocator>::BufData
{
    T *m_buf;
    size_t m_pos;
    size_t m_size;
    size_t m_capacity;
};

template <typename T, class Allocator>
void CyclicBuffer<T, Allocator>::copyObj(const CyclicBuffer &obj)
{
    m_bufData.m_buf = std::move(obj.m_bufData.m_buf);
    m_bufData.m_pos = obj.m_bufData.m_pos;
    m_bufData.m_size = obj.m_bufData.m_size;
    m_bufData.m_capacity = obj.m_bufData.m_capacity;
}

template <typename T, class Allocator>
void CyclicBuffer<T, Allocator>::clearObj(CyclicBuffer &lhs)
{
    delete lhs.m_bufData.m_buf;
    lhs.m_bufData.m_buf = nullptr;

    lhs.m_bufData.m_pos = 0UL;
    lhs.m_bufData.m_size = 0UL;
}

template <typename T, class Allocator>
CyclicBuffer<T, Allocator>::CyclicBuffer()
{
    m_bufData.m_buf = allocator.allocate(m_kMaxSize);
    m_bufData.m_pos = 0UL;
    m_bufData.m_size = 0UL;
    m_bufData.m_capacity = m_kMaxSize;
}

template <typename T, class Allocator>
CyclicBuffer<T, Allocator>::CyclicBuffer(const size_t &size)
{
    m_bufData.m_buf = allocator.allocate(size);
    m_bufData.m_pos = 0UL;
    m_bufData.m_size = 0UL;
    m_bufData.m_capacity = size;
}

template <typename T, class Allocator>
CyclicBuffer<T, Allocator>::CyclicBuffer(const CyclicBuffer &obj)
{
    copyObj(obj);
}

template <typename T, class Allocator>
CyclicBuffer<T, Allocator>::CyclicBuffer(CyclicBuffer &&lhs)
{
    copyObj(lhs);
    clearObj(lhs);
}

template <typename T, class Allocator>
CyclicBuffer<T, Allocator> &CyclicBuffer<T, Allocator>::operator=(const CyclicBuffer &obj)
{
    if (this == &obj)
        return *this;
    copyObj(obj);
    return *this;
}

template <typename T, class Allocator>
CyclicBuffer<T, Allocator> &CyclicBuffer<T, Allocator>::operator=(CyclicBuffer &&lhs) noexcept
{
    if (this == &lhs)
        return *this;
    clearObj(*this);
    copyObj(lhs);
    clearObj(lhs);
    return *this;
}

template <typename T, class Allocator>
CyclicBuffer<T, Allocator>::~CyclicBuffer()
{
    clearObj(*this);
}

template <typename T, class Allocator>
constexpr size_t CyclicBuffer<T, Allocator>::getSize() const
{
    return m_bufData.m_size;
}

template <typename T, class Allocator>
constexpr size_t CyclicBuffer<T, Allocator>::getCapacity() const
{
    return m_bufData.m_capacity;
}

template <typename T, class Allocator>
constexpr void CyclicBuffer<T, Allocator>::resizeCapacity(const size_t &capacity)
{
    if (capacity <= m_bufData.m_size)
    {
        std::cerr
            << "Can't resize the capacity of cyclic buffer.\nCurrent size = "
            << m_bufData.m_size << "\nCurrent capacity = "
            << m_bufData.m_capacity << std::endl;
    }
    else
        m_bufData.m_capacity = capacity;
}

template <typename T, class Allocator>
constexpr void CyclicBuffer<T, Allocator>::insert(const T &data)
{
    if (m_bufData.m_buf == nullptr)
        m_bufData.m_buf = allocator.allocate(1UL);

    m_bufData.m_buf[m_bufData.m_pos++] = data;

    if (m_bufData.m_size < m_bufData.m_capacity)
        m_bufData.m_size++;

    if (m_bufData.m_pos == m_bufData.m_capacity)
        m_bufData.m_pos = 0UL;
}

template <typename T, class Allocator>
constexpr T &CyclicBuffer<T, Allocator>::getData(const size_t &pos) const
{
    return m_bufData.m_buf[pos];
}

template <typename T, class Allocator>
constexpr void CyclicBuffer<T, Allocator>::clear()
{
    clearObj(*this);
}

template <typename T, class Allocator>
constexpr void CyclicBuffer<T, Allocator>::printBuffer() const
{
    if (m_bufData.m_buf != nullptr)
    {
        for (size_t i{0UL}; i < getSize(); i++)
        {
            std::cout << getData(i) << '\t';
        }
        std::endl(std::cout);
    }
    else
        std::cout << "Can't print buffer. Buffer is empty." << std::endl;
}
