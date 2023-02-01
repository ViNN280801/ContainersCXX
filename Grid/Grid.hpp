#pragma once

#include <iostream>
#include <optional>
#include <utility>
#include <vector>
#include <string>

// Describes grid that can be used for: chess, checkers, spreadsheet, and so on
template <typename T>
class Grid
{
private:
    // Width of grid, measured in unsigned long integer number
    size_t m_width{0UL};

    // Height of grid, measured in unsigned long integer number
    size_t m_height{0UL};

    // Vector of vectors of cells
    // 'std::optional' manages an optional contained value, i. e. a value that may not be presented
    std::vector<std::vector<std::optional<T>>> m_cells;

    // Verifies coordinates on grid
    void verify_coordinates(const size_t &__x, const size_t &__y) const;

public:
    // Variable which store default value of width of grid
    static const size_t default_width{10UL};

    // Variable which store default value of height of grid
    static const size_t default_height{10UL};

    // Constructor with parameters
    explicit Grid(size_t __width = default_width, size_t __height = default_height);

    // Virtual default destructor
    virtual ~Grid() = default;

    // Default copy constructor
    Grid(const Grid<T> &__src) = default;

    // Default assignment operator
    Grid &operator=(const Grid<T> &__rhs) = default;

    // Copy constructor
    // Type 'E' here serves for convert from 'T' to 'E' if they are not equal
    template <typename E>
    Grid(const Grid<E> &__src);

    // Assignment operator
    // Type 'E' here serves for convert from 'T' to 'E' if they are not equal
    template <typename E>
    Grid &operator=(const Grid<E> &__rhs);

    // Swaping instances of object 'Grid'
    void swap(Grid &__other) noexcept;

    // Default move constructor
    Grid(Grid<T> &&__src) = default;

    // Default move-assignament operator
    Grid &operator=(Grid<T> &&__src) = default;

    // Returns mutable reference on cell
    std::optional<T> &at(const size_t &__x, const size_t &__y);

    // Returns constant reference on cell
    const std::optional<T> &at(const size_t &__x, const size_t &__y) const;

    // Returns width of grid
    inline constexpr size_t width() const { return m_width; }

    // Returns height of grid
    inline constexpr size_t height() const { return m_height; }
};

template <typename T>
void Grid<T>::swap(Grid &__other) noexcept
{
    std::swap(m_width, __other.m_width);
    std::swap(m_height, __other.m_height);
    std::swap(m_cells, __other.m_cells);
}

template <typename T>
template <typename E>
Grid<T>::Grid(const Grid<E> &__src) : Grid{__src.width(), __src.height()}
{
    // Copying data
    for (size_t i{0UL}; i < m_width; i++)
    {
        for (size_t j{0UL}; j < m_height; j++)
        {
            m_cells[i][j] = __src.at(i, j);
        }
    }
}

template <typename T>
template <typename E>
Grid<T> &Grid<T>::operator=(const Grid<E> &__rhs)
{
    /* Note: This assignment operator takes a 'const Grid<E> &', returns 'Grid<T> &' */
    // Copy-and-swap
    Grid<T> tmp{__rhs};
    swap(tmp);

    // Returning current object
    return *this;
}

template <typename T>
Grid<T>::Grid(size_t __width, size_t __height) : m_width(__width), m_height(__height)
{
    // Resizing width of cell
    m_cells.resize(m_width);

    // Iteration by columns in cells
    for (auto &column : m_cells)
    {
        // Resizing height of cell
        column.resize(m_height);
    }
}

template <typename T>
void Grid<T>::verify_coordinates(const size_t &__x, const size_t &__y) const
{
    // Checking if coordinates out of range on the grid. If coordinates >= ranges of grid -> throw 'std::out_of_range' exception with message
    if (__x >= m_width)
    {
        // Initializing message to throw exception with it
        std::string err{__x + " must be less than " + m_width};
        throw std::out_of_range{err};
    }
    if (__y >= m_height)
    {
        std::string err{__y + " must be less than " + m_height};
        throw std::out_of_range{err};
    }
}

template <typename T>
std::optional<T> &Grid<T>::at(const size_t &__x, const size_t &__y)
{
    // Returning mutable reference on cell
    return const_cast<std::optional<T> &>(std::as_const(*this).at(__x, __y));
}

template <typename T>
const std::optional<T> &Grid<T>::at(const size_t &__x, const size_t &__y) const
{
    // Verifying coordinates
    verify_coordinates(__x, __y);

    // Returning constant reference on cell
    return m_cells[__x][__y];
}
