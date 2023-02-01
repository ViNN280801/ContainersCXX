#ifndef __CYCLICBUFFER_HPP__
#define __CYCLICBUFFER_HPP__

#include <iostream>
#include <memory>

template <typename T, class Allocator = std::allocator<T>>
class CyclicBuffer
{
private:
    static constexpr size_t m_kMaxSize{255UL};
    struct BufData;
    BufData m_bufData;
    Allocator allocator;

protected:
    void copyObj(const CyclicBuffer &);
    void clearObj(CyclicBuffer &);

public:
    explicit CyclicBuffer();
    explicit CyclicBuffer(const size_t &);
    explicit CyclicBuffer(const CyclicBuffer &);
    explicit CyclicBuffer(CyclicBuffer &&);
    CyclicBuffer &operator=(const CyclicBuffer &);
    CyclicBuffer &operator=(CyclicBuffer &&) noexcept;
    virtual ~CyclicBuffer();

    constexpr size_t getSize() const;
    constexpr size_t getCapacity() const;
    constexpr void resizeCapacity(const size_t &);

    constexpr void insert(const T &);
    constexpr T &getData(const size_t &) const;
    constexpr void clear();
    constexpr void printBuffer() const;
};

#endif // __CYCLICBUFFER_HPP__