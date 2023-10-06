#ifndef VECTOR_IMPL_HPP
#define VECTOR_IMPL_HPP

#include <iostream>
#include <stdexcept>
#include <limits>

#include "vector.hpp"

#define VECTOR_MAX_SIZE std::numeric_limits<int>::max()

template <typename T>
void Vector<T>::copyObj(Vector const &rhs)
{
    m_data = std::move(rhs.m_data);
    m_size = rhs.m_size;
    m_capacity = rhs.m_capacity;
}

template <typename T>
void Vector<T>::moveObj(Vector &&rhs) noexcept
{
    m_data = std::move(rhs.m_data);
    m_size = std::move(rhs.m_size);
    m_capacity = std::move(rhs.m_capacity);
}

template <typename T>
void Vector<T>::clearObj(Vector &obj)
{
    obj.m_data.reset();
    obj.m_size = 0ul;
    obj.m_capacity = 0ul;
}

template <typename T>
void Vector<T>::increaseCapacity() { m_capacity = m_size * 2ul; }

template <typename T>
Vector<T>::Vector() : m_size(0ul), m_capacity(1ul) { m_data.reset(); }

template <typename T>
Vector<T>::Vector(T const &data) : m_data(new T(data)),
                                   m_size(1ul) { increaseCapacity(); }

template <typename T>
Vector<T>::Vector(T &&data) noexcept : m_data(new T(std::move(data))),
                                       m_size(1ul) { increaseCapacity(); }

template <typename T>
Vector<T>::Vector(Vector const &vec) { copyObj(vec); }

template <typename T>
Vector<T>::Vector(Vector &&vec) noexcept { moveObj(std::move(vec)); }

template <typename T>
Vector<T> &Vector<T>::operator=(Vector const &vec)
{
    if (this == &vec)
        return *this;
    copyObj(vec);
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&vec) noexcept
{
    if (this == &vec)
        return *this;
    moveObj(vec);
    return *this;
}

template <typename T>
void Vector<T>::push_back(const T &value)
{
    static_assert(std::copyable<T> && std::is_copy_assignable_v<T>);

    if (m_size >= m_capacity)
    {
        increaseCapacity();
        std::unique_ptr<T[]> data = std::make_unique<T[]>(m_capacity);
        for (size_t i{}; i < m_size; i++)
            data.get()[i] = std::move(m_data.get()[i]);
        m_data = std::move(data);
    }
    m_data.get()[m_size++] = value;
}

template <typename T>
constexpr void Vector<T>::push_back(T &&value)
{
    static_assert(std::movable<T> && std::is_move_assignable_v<T>);

    if (m_size >= m_capacity)
    {
        increaseCapacity();
        std::unique_ptr<T[]> data = std::make_unique<T[]>(m_capacity);
        for (size_t i{}; i < m_size; i++)
            data.get()[i] = std::move(m_data.get()[i]);
        m_data = std::move(data);
    }
    m_data.get()[m_size++] = std::move(value);
}

/* template <typename T>
template <typename... Args>
constexpr void Vector<T>::emplace_back(Args &&...args)
{
    if (m_size >= m_capacity)
        increaseCapacity();
    new (dynamic_cast<T *>(m_data.get() + m_size)) T(std::forward<Args>(args)...);
    m_size += sizeof...(Args);
}*/

template <typename T>
constexpr bool Vector<T>::empty() const noexcept { return !m_size; }

template <typename T>
constexpr size_t Vector<T>::size() const noexcept { return m_size; }

template <typename T>
constexpr size_t Vector<T>::capacity() const noexcept { return m_capacity; }

template <typename T>
constexpr void Vector<T>::reserve(size_t capacity)
{
    if (capacity < VECTOR_MAX_SIZE)
        m_capacity = capacity;
}

template <typename T>
constexpr size_t Vector<T>::max_size() const noexcept { return VECTOR_MAX_SIZE; }

template <typename T>
constexpr T &Vector<T>::at(size_t index)
{
    if (index >= m_size)
        throw std::out_of_range("Index out of bounds");
    return m_data[index];
}

template <typename T>
constexpr T const &Vector<T>::at(size_t index) const
{
    if (index >= m_size)
        throw std::out_of_range("Index out of bounds");
    return m_data[index];
}

template <typename T>
constexpr T &Vector<T>::operator[](size_t index) { return m_data[index]; }

template <typename T>
constexpr T const &Vector<T>::operator[](size_t index) const { return m_data[index]; }

template <typename T>
constexpr T &Vector<T>::front()
{
    if (!m_size)
        throw std::out_of_range("Vector is empty. Cannot access front element.");
    return m_data[0];
}

template <typename T>
constexpr T const &Vector<T>::front() const
{
    if (!m_size)
        throw std::out_of_range("Vector is empty. Cannot access front element.");
    return m_data[0];
}

template <typename T>
constexpr T &Vector<T>::back()
{
    if (empty())
        throw std::out_of_range("back(): vector is empty");
    return m_data[m_size - 1];
}

template <typename T>
constexpr T const &Vector<T>::back() const
{
    if (empty())
        throw std::out_of_range("back() const: vector is empty");
    return m_data[m_size - 1];
}

template <typename T>
constexpr void Vector<T>::clear() noexcept { clearObj(*this); }

template <typename T>
constexpr void Vector<T>::resize(size_t new_size)
{
    if (new_size < m_size)
        // If size is smaller, just update the size
        m_size = new_size;
    else if (new_size > m_capacity)
    {
        // If size is larger than the current capacity, we need to reallocate memory
        // Call reserve to ensure enough capacity
        reserve(new_size);
        for (size_t i{m_size}; i < new_size; ++i)
            // Default-initialize the new elements
            m_data[i] = T();
        m_size = new_size;
    }
    else
        // If size is in the current capacity range, just update the size
        m_size = new_size;
}

template <typename T>
constexpr void Vector<T>::resize(size_t new_size, T const &value)
{
    // No need to resize, the size is the same
    if (new_size == m_size)
        return;
    if (new_size < m_size)
    {
        // Resize down
        m_size = new_size;
        return;
    }
    if (new_size <= m_capacity)
    {
        // Resize up without reallocation
        for (size_t i{m_size}; i < new_size; ++i)
            m_data[i] = value;
        m_size = new_size;
    }
    else
    {
        // Resize up with reallocation
        size_t newCapacity{std::max(new_size, m_capacity * 2)};
        std::unique_ptr<T[]> newData{std::make_unique<T[]>(newCapacity)};
        for (size_t i{}; i < m_size; ++i)
            newData[i] = m_data[i];
        for (size_t i{m_size}; i < new_size; ++i)
            newData[i] = value;
        m_data = std::move(newData);
        m_capacity = newCapacity;
        m_size = new_size;
    }
}

template <typename T>
void Vector<T>::print() const
{
    static_assert(Printable<T>, "Type of the vector elements has to be printable");

    for (size_t i{}; i < m_size; i++)
        std::cout << m_data.get()[i] << ' ';
    std::endl(std::cout);
}

#endif // !VECTOR_IMPL_HPP
