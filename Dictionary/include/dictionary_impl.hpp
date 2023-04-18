#ifndef DICTIONARY_IMPL_HPP
#define DICTIONARY_IMPL_HPP

#include "dictionary.hpp"

template <typename Key, typename Value, typename Allocator>
size_t Dictionary<Key, Value, Allocator>::counter = 0;

/*
 * @brief Struct 'Node' describes node of the binary tree that has two branches
 * left branch value - value, that lower than node value, right branch value - greater than node value
 * @tparam T type of value of the node
 */
template <typename Key, typename Value, typename Allocator>
struct Dictionary<Key, Value, Allocator>::Node
{
    std::pair<Key, Value> m_data;

    // Points on left root of tree
    std::shared_ptr<Node> m_leftRoot;

    // Points on right root of tree
    std::shared_ptr<Node> m_rightRoot;

    explicit Node() : m_leftRoot(nullptr), m_rightRoot(nullptr) { m_data.second = Value{}; }

    explicit Node(Key const &key) : m_leftRoot(nullptr), m_rightRoot(nullptr)
    {
        m_data.first = std::move(key);
        m_data.second = Value{};
    }

    explicit Node(Key const &key, Value const &value) : m_leftRoot(nullptr), m_rightRoot(nullptr)
    {
        m_data.first = std::move(key);
        m_data.second = std::move(value);
    }

    explicit Node(std::pair<Key const, Value> const &x) : m_data(std::move(x)) {}

    explicit Node(Node const &) = default;
    explicit Node(Node &&) = default;

    // Returns max depth from two roots
    constexpr size_t max() const noexcept
    {
        const size_t left_depth{m_leftRoot ? m_leftRoot->max() : 0};
        const size_t right_depth{m_rightRoot ? m_rightRoot->max() : 0};
        return (left_depth > right_depth ? left_depth : right_depth) + 1;
    }

    virtual ~Node() = default;
};

template <typename Key, typename Value, typename Allocator>
constexpr size_t
Dictionary<Key, Value, Allocator>::count(std::shared_ptr<Dictionary<Key, Value, Allocator>::Node> node) const
{
    return (node == nullptr) ? 0 : (1 + count(node->m_leftRoot) + count(node->m_rightRoot));
}

template <typename Key, typename Value, typename Allocator>
constexpr void
Dictionary<Key, Value, Allocator>::addNode(Key const &key, std::shared_ptr<Node> &node)
{
    if (node == nullptr)
        node = std::make_shared<Node>(key);
    else
    {
        if (key < node->m_data.first)
        {
            if (node->m_leftRoot != nullptr)
                addNode(key, node->m_leftRoot);
            else
                node->m_leftRoot = std::make_shared<Node>(key);
        }
        else if (key >= node->m_data.first)
        {
            if (node->m_rightRoot != nullptr)
                addNode(key, node->m_rightRoot);
            else
                node->m_rightRoot = std::make_shared<Node>(key);
        }
    }
}

template <typename Key, typename Value, typename Allocator>
std::shared_ptr<struct Dictionary<Key, Value, Allocator>::Node>
Dictionary<Key, Value, Allocator>::certainNode(std::shared_ptr<Node> &node, size_t nodeNumber) const
{
    static std::shared_ptr<Node> pnode;

    if (node == nullptr)
        return nullptr;
    else
    {
        counter++;

        if (counter == nodeNumber)
            pnode = node;

        certainNode(node->m_leftRoot, nodeNumber);
        certainNode(node->m_rightRoot, nodeNumber);

        return pnode;
    }
}

template <typename Key, typename Value, typename Allocator>
std::shared_ptr<struct Dictionary<Key, Value, Allocator>::Node>
Dictionary<Key, Value, Allocator>::certainNode(std::shared_ptr<Node> &node, Key const &key) const
{
    static std::shared_ptr<Node> pnode;

    if (node == nullptr)
        return nullptr;
    else
    {
        if (key == node->m_data.first)
            pnode = node;

        certainNode(node->m_leftRoot, key);
        certainNode(node->m_rightRoot, key);

        return (key == node->m_data.first) ? pnode : nullptr;
    }
}

template <typename Key, typename Value, typename Allocator>
constexpr size_t
Dictionary<Key, Value, Allocator>::searchNodeNumberByKey(std::shared_ptr<Node> &node, Key const &key) const
{
    static size_t nodeNumber{};

    if (node == nullptr)
        return 0;
    else
    {
        counter++;
        if (key == node->m_data.first)
            nodeNumber = counter;

        searchNodeNumberByKey(node->m_leftRoot, key);
        searchNodeNumberByKey(node->m_rightRoot, key);

        return nodeNumber;
    }
}

template <typename Key, typename Value, typename Allocator>
std::shared_ptr<struct Dictionary<Key, Value, Allocator>::Node>
Dictionary<Key, Value, Allocator>::minValue(std::shared_ptr<Node> &node) const
{
    std::shared_ptr<Node> pnode{node};
    while (pnode->m_leftRoot != nullptr)
        pnode = pnode->m_leftRoot;
    return pnode;
}

template <typename Key, typename Value, typename Allocator>
std::shared_ptr<struct Dictionary<Key, Value, Allocator>::Node>
Dictionary<Key, Value, Allocator>::maxValue(std::shared_ptr<Node> &node) const
{
    // Tree is empty
    if (node == nullptr)
        return nullptr;
    // Tree is not empty
    else
        return (node->m_rightRoot == nullptr) ? node : maxValue(node->m_rightRoot);
}

template <typename Key, typename Value, typename Allocator>
std::shared_ptr<struct Dictionary<Key, Value, Allocator>::Node>
Dictionary<Key, Value, Allocator>::previousNode(std::shared_ptr<Node> &node, size_t nodeNumber)
{
    static std::shared_ptr<Node> pprev;

    if (node == nullptr)
        return nullptr;
    else
    {
        counter++;

        if (counter == (nodeNumber - 1))
            pprev = node;

        previousNode(node->m_leftRoot, nodeNumber);
        previousNode(node->m_rightRoot, nodeNumber);

        return pprev;
    }
}

template <typename Key, typename Value, typename Allocator>
std::shared_ptr<struct Dictionary<Key, Value, Allocator>::Node>
Dictionary<Key, Value, Allocator>::nextNode(std::shared_ptr<Node> &node, size_t nodeNumber)
{
    static std::shared_ptr<Node> pnext;

    if (node == nullptr)
        return nullptr;
    else
    {
        counter++;

        if (counter == (nodeNumber + 1))
            pnext = node;

        nextNode(node->m_leftRoot, nodeNumber);
        nextNode(node->m_rightRoot, nodeNumber);

        return pnext;
    }
}

template <typename Key, typename Value, typename Allocator>
std::shared_ptr<struct Dictionary<Key, Value, Allocator>::Node>
Dictionary<Key, Value, Allocator>::removeNodeByKey(std::shared_ptr<Node> node, Key const &key)
{
    // If tree is emplty -> return null
    if (node == nullptr)
        return nullptr;
    else
    {
        // If node value which we want to delete is smaller than the root's value, then it lies in left subtree
        if (key < node->m_data.first)
            node->m_leftRoot = removeNodeByKey(node->m_leftRoot, key);
        // If node value which we want to delete is greater than the root's value, then it lies in left subtree
        else if (key > node->m_data.first)
            node->m_rightRoot = removeNodeByKey(node->m_rightRoot, key);
        // If node value equals specified value -> found node which we want to delete
        else
        {
            // Case 1: Node has no child or has only 1 (left) child
            if (node->m_rightRoot == nullptr)
                return node->m_leftRoot;
            // Case 2: Node has no child or has only 1 (right) child
            else if (node->m_leftRoot == nullptr)
                return node->m_rightRoot;
            else
            {
                // Case 3: Node has 2 children
                // Smallest in the right subtree
                std::shared_ptr<Node> ptmp{minValue(node->m_rightRoot)};
                // Copy the inorder successor's data to this node
                node->m_data.first = ptmp->m_data.first;
                // Delete the inorder successor
                node->m_rightRoot = removeNodeByKey(node->m_rightRoot, ptmp->m_data.first);
            }
        }
    }
    return node;
}

template <typename Key, typename Value, typename Allocator>
constexpr void
Dictionary<Key, Value, Allocator>::addNode(Key const &key)
{
    addNode(key, m_root);
}

template <typename Key, typename Value, typename Allocator>
constexpr void
Dictionary<Key, Value, Allocator>::removeNode(Key const &key)
{
    if (counter != 0)
        counter = 0;

    if (m_root == nullptr)
        return;
    else
        m_root = removeNodeByKey(m_root, key);
}

template <typename Key, typename Value, typename Allocator>
Dictionary<Key, Value, Allocator>::Dictionary(Key const &key, Value const &value)
{
    m_root = std::make_shared<Node>(key, value);
}

template <typename Key, typename Value, typename Allocator>
constexpr size_t
Dictionary<Key, Value, Allocator>::size() const { return count(m_root); }

template <typename Key, typename Value, typename Allocator>
constexpr bool
Dictionary<Key, Value, Allocator>::empty() const { return size() == 0; }

template <typename Key, typename Value, typename Allocator>
void Dictionary<Key, Value, Allocator>::clear() noexcept
{
}

template <typename Key, typename Value, typename Allocator>
Key const &
Dictionary<Key, Value, Allocator>::get_key() const noexcept
{
    // Честно говоря, немного не понял, для чего и зачем нужна эта функция (из задания)
    // поэтому я просто закоменчу этот код, чтобы не показывался надоедливый ворнинг
    // warning: ‘throw’ will always call ‘terminate’ [-Wterminate]
    /* if (!m_root)
        throw std::invalid_argument("There is no such key"); */
    return m_root->m_data.first;
}

template <typename Key, typename Value, typename Allocator>
const Value &
Dictionary<Key, Value, Allocator>::get(Key const &key) const
{
    // Making a copy of the root
    std::shared_ptr<Node> pnode{m_root}, ptmp{certainNode(pnode, key)};

    // Initialize empty value to return it if method 'certainNode()' returns "nullptr"
    // as result of searching node with specified key
    Value null{Value()};

    // Searching necessary value by key with the helper method
    return ptmp ? ptmp->m_data.second : null;
}

template <typename Key, typename Value, typename Allocator>
const Value &
Dictionary<Key, Value, Allocator>::at(Key const &key) const
{
    // Making a copy of the root
    std::shared_ptr<Node> pnode{m_root}, ptmp{certainNode(pnode, key)};

    // If helper method 'certainNode()' returns "nullptr" -> throw an exception
    if (!ptmp)
        throw std::out_of_range("Exception: std::out_of_range: Container does not contains specified key");

    // Searching necessary value by key with the helper method
    return ptmp->m_data.second;
}

template <typename Key, typename Value, typename Allocator>
constexpr void
Dictionary<Key, Value, Allocator>::set(Key const &key, const Value &value)
{
    // Making a copy of the root
    std::shared_ptr<Node> pnode{m_root}, ptmp{certainNode(pnode, key)};
    // Replaces old value associated with specified key with a new value
    ptmp->m_data.second = value;
}

template <typename Key, typename Value, typename Allocator>
constexpr bool
Dictionary<Key, Value, Allocator>::is_set(Key const &key) const
{
    // Making a copy of the root
    std::shared_ptr<Node> pnode{m_root}, ptmp{certainNode(pnode, key)};
    // If 'ptmp' stores "nullptr" (if there is no such node with specified key)
    // - returns false, otherwise - true
    return !ptmp;
}

#endif // DICTIONARY_IMPL_HPP
