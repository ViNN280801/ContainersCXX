#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <memory>
#include <concepts>

template <class Key, class Value>
class IDictionary
{
public:
    virtual ~IDictionary() = default;
    virtual const Value &get(Key const &key) const = 0;
    virtual void set(Key const &key, const Value &value) = 0;
    virtual bool is_set(Key const &key) const = 0;
};

template <class Key>
class INotFoundException : public std::exception
{
public:
    virtual Key const &get_key() const noexcept = 0;
};

template <typename Key, typename Value, typename Alloc = std::allocator<std::pair<const Key, Value>>>
class Dictionary : public IDictionary<Key, Value>, public INotFoundException<Key>
{
    static_assert(std::equality_comparable<Key> && std::equality_comparable<Value>,
                  "Types of key and value have to be comparable (not together)");
    static_assert(std::is_copy_assignable_v<Value>, "Type of value have to be copyable, assignable and comparable.");

private:
    struct Node;
    std::shared_ptr<Node> m_root;

    /// @brief For multiple use 'certainNode(void)' method
    static size_t counter;

    /// @param node node from which to start count
    /// @return Count of levels (nodes) of binary tree
    constexpr size_t count(std::shared_ptr<Node> node) const;

    /// @brief Adding node to the binary tree
    /// @tparam key which will be added to the node
    /// @param node pointer to 'Node' struct
    virtual constexpr void addNode(Key const &key, std::shared_ptr<Node> &node);

    /// @brief Helper method that returns certain node by it's value
    /// @param node pointer to 'Node' struct
    /// @tparam key value of binary tree by which search will take place
    /// @return Node if value exists in this binary tree
    std::shared_ptr<Node> certainNode(std::shared_ptr<Node> &node, Key const &key) const;

    /// @brief Helper method that returns node number by it's value
    /// @param node pointer to 'Node' struct
    /// @tparam key value of binary tree by which search will take place
    /// @return Number of node if value exists in this binary tree
    constexpr size_t searchNodeNumberByKey(std::shared_ptr<Node> &node, Key const &key) const;

    ///  @brief Helper method (Non-recursive function)
    ///  @param node pointer to 'Node' struct
    ///  @return Minimal node in binary tree (lower left element)
    ///  starting from the specified number
    std::shared_ptr<Node> minValue(std::shared_ptr<Node> &node) const;

    /// @brief Helper method (Recursive function)
    /// @param node pointer to 'Node' struct
    /// @return Max element in binary tree (lower right element)
    std::shared_ptr<Node> maxValue(std::shared_ptr<Node> &node) const;

    ///  @brief Helper method to find the previous node with specified node number
    ///  @param node pointer to 'Node' struct
    ///  @param nodeNumber node number as a pivot
    ///  @return Previous node by node number
    static std::shared_ptr<Node> previousNode(std::shared_ptr<Node> &node, size_t nodeNumber);

    ///  @brief Helper method to find the next node with specified node number
    ///  @param node pointer to 'Node' struct
    ///  @param nodeNumber node number as a pivot
    ///  @return Next node by node number
    static std::shared_ptr<Node> nextNode(std::shared_ptr<Node> &node, size_t nodeNumber);

    ///  @brief Helper method that removes node from binary tree by value
    ///  @param node pointer to 'Node' struct
    ///  @tparam key value of the node which you want to erase from the binary tree
    ///  @return Node which you want to delete
    std::shared_ptr<Node> removeNodeByKey(std::shared_ptr<Node> node, Key const &key);

    /// @brief Adding node to the tree binary tree
    /// @tparam key value which you want to add into the binary tree
    virtual constexpr void addNode(Key const &key);

    /// @brief Removes element in binary tree by value
    /// @tparam key value of the node which you want to remove
    constexpr void removeNode(Key const &key);

public:
    /// @brief Defaulted ctor
    explicit Dictionary() = default;

    /// @brief Defaulted copy ctor
    explicit Dictionary(Dictionary const &) = default;

    /// @brief Defaulted move ctor
    explicit Dictionary(Dictionary &&) = default;

    /// @brief Defaulted copy assignment operator
    Dictionary &operator=(Dictionary const &) = default;

    /// @brief Defaulted move assignment operator
    Dictionary &operator=(Dictionary &&) noexcept = default;

    /// @brief Defaulted virtual dtor
    virtual ~Dictionary() = default;

    /// @brief Ctor with params
    /// @tparam key key parameter
    /// @tparam value value to add into the dictionary
    explicit Dictionary(Key const &key, Value const &value);

    /// @return Count of elements in the dictionary
    constexpr size_t size() const;

    /// @brief Checks if container is empty
    /// @return "true" if empty, ohterwise - "false"
    constexpr bool empty() const;

    /// @brief Erasing all elements from the container
    void clear() noexcept;

    /// @brief Throws an exception if there is no such key
    /// @return Key of root (head) node if exists
    virtual Key const &get_key() const noexcept override;

    /// @brief Gets a value in dictionary by specified key
    /// @tparam key key of element that you want to find
    /// @return Value associated with 'key' parameter
    /// If there is no specified key in the container
    /// returns standard null value for 'Value' type (works like an "operator[]")
    virtual const Value &get(Key const &key) const override;

    /// @brief Gets a value in dictionary by specified key
    /// @throw Exception "std::out_of_range" if there is no key in the container
    /// @tparam key key of element that you want to find
    /// @return Value associated with 'key' parameter
    const Value &at(Key const &key) const;

    /// @brief Modifies value associated with 'key'
    /// @tparam key certain key that stores value
    /// @tparam value new value to set
    virtual constexpr void set(Key const &key, const Value &value) override;

    /// @brief Checks if 'key' stores any element
    /// @tparam key key which is being checked on availavility of value
    /// @return "true" if 'key' is associated with some value, otherwise - "false"
    virtual constexpr bool is_set(Key const &key) const override;

    /// @brief Inserting new element to the container
    /// @tparam key key to which will be inserted value
    /// @tparam value value to insert
    constexpr void insert(Key const &key, Value const &value);

    /// @brief Erases node by it key, if container is empty or there
    /// is no node with specified key - calling "return;"
    /// @tparam key key to search to erase node
    constexpr void erase(Key const &key);

    /// @brief Getter for min value
    /// @return Min value from container
    constexpr Value &min() const;

    /// @brief Getter for max value
    /// @return Max value from container
    constexpr Value &max() const;
};

#endif // DICTIONARY_HPP
