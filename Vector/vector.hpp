#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <concepts>
#include <memory>
#include <ostream>

/**
 * @brief Concept that checks if variable has output operator
 * @tparam a variable to check
 * @param os output stream
 */
template <typename T>
concept Printable = requires(T a, std::ostream &os) {
    {
        os << a
    } -> std::same_as<std::ostream &>;
};

/**
 * @brief Class that tries to repeat after the STL "std::vector" implementation.
 * Implements with using of smart ptr, not with the std::allocator.
 */
template <typename T>
class Vector
{
    // Restrictions on 'T' type. Other restrictions are within some method
    static_assert(std::equality_comparable<T> && std::swappable<T>);

public:
    /// @brief Default ctor
    explicit Vector();

    /// @brief Ctors (copy|move) with template arg
    explicit Vector(T const &data);
    explicit Vector(T &&data) noexcept;

    /// @brief Copy ctor
    explicit Vector(Vector const &vec);

    /// @brief Move ctor
    explicit Vector(Vector &&vec) noexcept;

    /// @brief Copy-assignment operator
    Vector &operator=(Vector const &vec);

    /// @brief Move-assignment operator
    Vector &operator=(Vector &&vec) noexcept;

    /// @brief Dtor
    virtual ~Vector() {}

    /**
     * @brief Adding new element to the vector
     * @tparam value value to add
     */
    void push_back(const T &value);

    /**
     * @brief Adding new element to the vector. Move version
     * @tparam value value to add
     */
    constexpr void push_back(T &&value);

    /**
     * @brief Appends a new elements to the end of the vector
     * @tparam Args types of arguments
     */
    template <typename... Args>
    constexpr void emplace_back(Args &&...args);

    /**
     * @brief Checker for emptiness of the vector
     * @return "true" if vector is empty, otherwise "false"
     */
    [[nodiscard]] constexpr bool empty() const noexcept;

    /// @return Size of the vector
    constexpr size_t size() const noexcept;

    /// @return Capacity of the vector - how many elements can it contain
    constexpr size_t capacity() const noexcept;

    /**
     * @brief Increases capacity of the vector
     * @param capacity new value of the capacity
     */
    constexpr void reserve(size_t capacity);

    /// @return Maximum number of elements the container is able to hold
    constexpr size_t max_size() const noexcept;

    /**
     * @brief Access the element at the specified index with bounds checking
     * @param index The index of the element to access
     * @return A reference to the element at the specified index
     * @throws "std::out_of_range" if the index is out of bounds
     */
    constexpr T &at(size_t index);

    /**
     * @brief Access the element at the specified index with bounds checking (const version)
     * @param index The index of the element to access
     * @return A constant reference to the element at the specified index
     * @throws "std::out_of_range" if the index is out of bounds
     */
    constexpr T const &at(size_t index) const;

    /**
     * @brief Access the element at the specified index without bounds checking
     * @param index The index of the element to access
     * @return A reference to the element at the specified index
     */
    constexpr T &operator[](size_t index);

    /**
     * @brief Access the element at the specified index without bounds checking (const version)
     * @param index The index of the element to access
     * @return A constant reference to the element at the specified index
     */
    constexpr T const &operator[](size_t index) const;

    /**
     * @brief Returns a reference to the first element of the vector.
     * This function provides access to the first element of the vector.
     * If the vector is empty, it throws a std::out_of_range exception.
     * @returns A reference to the first element
     * @throws std::out_of_range if the vector is empty
     */
    constexpr T &front();

    /**
     * @brief Returns a reference to the first element of the vector (const version).
     * This function provides read-only access to the first element of the vector.
     * If the vector is empty, it throws a std::out_of_range exception.
     * @returns A constant reference to the first element
     * @throws std::out_of_range if the vector is empty
     */
    constexpr T const &front() const;

    /**
     * @brief Accesses the last element in the vector
     * @returns A reference to the last element
     */
    constexpr T &back();

    /**
     * @brief Accesses the last element in the vector (const version)
     * @returns A const reference to the last element
     */
    constexpr T const &back() const;

    /// @brief Erases all elements from the vector
    constexpr void clear() noexcept;

    /**
     * @brief Resizes the container to contain 'new_size' elements.
     * If the current size is greater than 'new_size', the container is reduced to its first 'new_size' elements.
     * If the current size is less than 'new_size', additional default-inserted elements are appended
     * @param new_size The new size of the container
     */
    constexpr void resize(size_t new_size);

    /**
     * @brief Resizes the container to contain 'new_size' elements.
     * If the current size is greater than 'new_size', the container is reduced to its first 'new_size' elements.
     * If the current size is less than 'new_size', additional default-inserted elements are appended.
     * @param new_size The new size of the container
     * @param value The value to initialize the new elements with
     */
    constexpr void resize(size_t new_size, T const &value);

    /// @brief Prints all elements of the vector to the terminal
    void print() const;

private:
    std::unique_ptr<T[]> m_data; // Data that stores in the vector as a template param
    size_t m_size;               // Real size
    size_t m_capacity;           // Reserved size

    /**
     * @brief Copies passed object content to current object
     * @param rhs object to copy
     */
    void copyObj(Vector const &rhs);

    /**
     * @brief Moves passed object content to current object
     * @param rhs object to move
     */
    void moveObj(Vector &&rhs) noexcept;

    /**
     * @brief Erases all data from object
     * @param obj object to erase all data within
     */
    void clearObj(Vector &obj);

    /// @brief Helper function that increases capacity
    void increaseCapacity();
};

#endif // !VECTOR_HPP
