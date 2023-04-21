#ifndef STACK_HPP
#define STACK_HPP

#include <memory>
#include <type_traits>

/// @brief Linear data structure that stores template type of object
/// Serves as a container of objects that are inserted and removed according
/// LIFO rule (Last-In-First-Out) like a stack of plates
/// @tparam T
/// @tparam Allocator
template <typename T>
class Stack
{
    static_assert(std::is_copy_assignable<T>::value, "Type 'T' must be copyable and assignable");

    /// @brief Pointer that contains data of 'T' type
    std::unique_ptr<T> m_data;

    /// @brief Size of stack
    size_t m_size;

    /// @brief Index of top element
    size_t m_indexTop;

public:
    /// @brief Default ctor
    explicit Stack();

    /// @brief Ctor with specifying size of the stack container
    /// @param size what size will stack be
    explicit Stack(size_t size);

    /// @brief Defaulter copy ctor
    /// @param obj obj to copy data from it to current obj
    explicit Stack(const Stack &) = default;

    /// @brief Defaulter move ctor
    /// @param obj obj to move data from it to current obj
    explicit Stack(Stack &&) = default;

    /// @brief Defaulted copy-assignment operator
    /// @param obj obj to copy from it to current obj
    /// @return Object of stack
    Stack &operator=(const Stack &) = default;

    /// @brief Defaulted move-assignment operator
    /// @param obj obj to move from it to current obj
    /// @return Object of stack
    Stack &operator=(Stack &&) noexcept = default;

    /// @brief Defaulted virtual dtor
    virtual ~Stack() = default;

    /// @brief Counts size of stack
    /// @return Size of stack
    constexpr size_t size() const;

    /// @brief Checks if stack is empty
    /// @return "true" if stack is empty, otherwise - "false"
    constexpr bool empty() const;

    /// @brief Adds specified value to the stack
    /// @tparam value value to add in the stack
    constexpr void push(const T &value);

    /// @brief Adds specified value to the stack
    /// @tparam value rvalue ref to value which will be added to the vector
    constexpr void push(T &&value);

    /// @brief Removes the top element
    void pop();

    /// @brief Acceses top element
    /// @return non-const ref to top element
    T &top();

    /// @brief Accesses top element
    /// @return const ref to top element
    const T &top() const;

    /// @brief Erasing all elements from the stack
    void clear();
};

#endif // !STACK_HPP
