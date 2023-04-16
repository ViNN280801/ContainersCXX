#ifndef BINTREE_HPP
#define BINTREE_HPP

#include <string>
#include <vector>
#include <memory>

/*
 * @brief This is an implementation of the binary tree container
 * Container uses smart pointers to store the data, thus there is no memory leaks
 * (checked with Valgrind tool)
 * @tparam T is the type of stored parameter of the container
 * @tparam Allocator default assigned to an STL allocator class with 'T' type
 */
template <typename T, typename Allocator = std::allocator<T>>
class BinaryTree
{
private:
    /// Node of the binary tree with hidden implementation, represents a structure of data
    struct Node;

    // Main node (root of binary tree)
    std::shared_ptr<Node> root;

    /// For multiple use 'certainNode(void)' method
    static size_t counter;

protected:
    /*
     * @brief Converts 'T' type to a string
     * @tparam value value to convert
     * @returns 'value' in a string representation
     */
    std::string T_to_str(const T &value) const noexcept;

    /*
     * @param node node from which to start count
     * @returns Count of levels (nodes) of binary tree
     */
    inline size_t count(std::shared_ptr<Node> node) const;

    /*
     * @brief Struct of cells with hidden implementation
     * this struct is helper for display nodes of the binary tree
     */
    struct cell_display;

    /*
     * @brief Builds a std::vector of std::vectors of cell_display structs
     * each std::vector of cell_display structs represents one row, starting at the root
     * this struct is helper for display nodes of the binary tree
     * @returns 2d vector of 'cell_display' struct
     */
    std::vector<std::vector<struct cell_display>> getRowDisplay(void) const noexcept;

    /*
     * @brief Takes the std::vector of rows of cell_display structs
     * generated by get_row_display and formats it into a test representation
     * as a std::vector of std::strings
     * @param rowsDisplay const ref to 2d vector of 'cell_display' struct
     * @returns Formatted vector of string
     */
    std::vector<std::string> rowFormat(const std::vector<std::vector<struct cell_display>> &rowsDisplay) const;

    /*
     * @brief Trims an equal number of space characters from
     * the beginning of each std::string in the std::vector.
     * At least one std::string in the std::vector will end up beginning
     * with no space characters
     * @param rows ref to vector of string to trim
     */
    static void trimRows(std::vector<std::string> &);

    /*
     * @brief Turns int number to std::string for splitting on digits for check -st, -nd,
     * -rd and -th postfixes of digits
     * @param num number that will transformed to a string with postfix
     * @returns Number with literal postfix such as -st, -nd, etc.
     */
    std::string transformNumber(int num) const noexcept;

    /*
     * @brief Adding node to the binary tree
     * @tparam value which will be added to the node
     * @param node pointer to 'Node' struct
     */
    virtual void addNode(const T &value, std::shared_ptr<Node> &node);

    /*
     * @brief Helper method that returns certain node by it's number
     * @param node pointer to 'Node' struct
     * @param nodeNumber node number by which search will take place
     * @returns Certain node by node number
     */
    std::shared_ptr<Node> certainNode(std::shared_ptr<Node> &node, size_t nodeNumber) const;

    /*
     * @brief Helper method that returns certain node by it's value
     * @param node pointer to 'Node' struct
     * @tparam value value of binary tree by which search will take place
     * @returns Node if value exists in this binary tree
     */
    std::shared_ptr<Node> certainNode(std::shared_ptr<Node> &node, const T &value) const;

    /*
     * @brief Helper method that returns node number by it's value
     * @param node pointer to 'Node' struct
     * @tparam value value of binary tree by which search will take place
     * @returns Number of node if value exists in this binary tree
     */
    size_t searchNodeNumberByValue(std::shared_ptr<Node> &node, const T &value) const;

    /*
     * @brief Helper method
     * @param node pointer to 'Node' struct
     * @param nodeNumber node number by which counting of branches will take place
     * @returns Count of branches of certain node
     */
    size_t branches(std::shared_ptr<Node> &node, size_t nodeNumber) const;

    /*
     * @brief Helper method (Non-recursive function)
     * @param node pointer to 'Node' struct
     * @returns Minimal node in binary tree (lower left element)
     * starting from the specified number
     */
    std::shared_ptr<Node> minValue(std::shared_ptr<Node> &node) const;

    /*
     * @brief Helper method (Recursive function)
     * @param node pointer to 'Node' struct
     * @returns Max element in binary tree (lower right element)
     */
    std::shared_ptr<Node> maxValue(std::shared_ptr<Node> &node) const;

    /*
     * @brief Helper method to find the previous node with specified node number
     * @param node pointer to 'Node' struct
     * @param nodeNumber node number as a pivot
     * @returns Previous node by node number
     */
    static std::shared_ptr<Node> previousNode(std::shared_ptr<Node> &node, size_t nodeNumber);

    /*
     * @brief Helper method to find the next node with specified node number
     * @param node pointer to 'Node' struct
     * @param nodeNumber node number as a pivot
     * @returns Next node by node number
     */
    static std::shared_ptr<Node> nextNode(std::shared_ptr<Node> &node, size_t nodeNumber);

    /*
     * @brief Helper method that removes node from binary tree by value
     * @param node pointer to 'Node' struct
     * @tparam value value of the node which you want to erase from the binary tree
     * @returns Node which you want to delete
     */
    std::shared_ptr<Node> removeNodeByValue(std::shared_ptr<Node> node, const T &value);

public:
    /// Zero-argument, default ctor
    explicit BinaryTree(void) = default;

    /*
     * @brief Default ctor with 1 template parameter
     * @tparam value value which will initialize the binary tree (head node value)
     */
    explicit BinaryTree(const T &value);

    /// Ctor with main param (it is also copy ctor)
    explicit BinaryTree(const BinaryTree *&);

    /// Assignment operator
    BinaryTree &operator=(const BinaryTree *&);

    /// Getter for max depth
    inline size_t getMaxDepth(void) const;

    /// Printing binary tree to the terminal
    void show(void) const;

    /*
     * @brief Adding node to the tree binary tree
     * @tparam value value which you want to add into the binary tree
     */
    virtual void addNode(const T &value) final;

    /// Printing count of nodes
    void printCountOfNodes(void) const;

    /*
     * @brief Printing branches of certain node (keep in mind that the countdown starts from 0)
     * @param nodeNumber node number from which will start printing
     */
    void printBranchesOfCertainNode(size_t nodeNumber);

    /*
     * @brief Printing value of certain node. Searching by node number
     * @param nodeNumber node number that specifes some value
     */
    void printValueByNode(size_t nodeNumber);

    /*
     * @brief Printing node number which found by searching by value
     * @tparam value value to search node number
     */
    void printNodeNumberByValue(const T &value);

    /// Printing min value from binary tree
    void searchMin(void);

    /// Printing max value from binary tree
    void searchMax(void);

    /*
     * @brief Removes element in binary tree by value
     * @tparam value value of the node which you want to remove
     */
    void removeNode(const T &value);

    /// Virtual dtor
    virtual ~BinaryTree(void) = default;
};

#endif // BINTREE_HPP
