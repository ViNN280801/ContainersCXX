#ifndef BINTREE_IMPL_HPP
#define BINTREE_IMPL_HPP

#include <algorithm>
#include <sstream>
#include <type_traits>

#include "bintree.hpp"

/*
 * @brief Struct 'Node' describes node of the binary tree that has two branches
 * left branch value - value, that lower than node value, right branch value - greater than node value
 * @tparam T type of value of the node
 */
template <typename T, typename Allocator>
struct BinaryTree<T, Allocator>::Node
{
    T value{""};

    // Points on left root of tree
    std::shared_ptr<Node> leftRoot;
    // Points on right root of tree
    std::shared_ptr<Node> rightRoot;

    explicit Node() : leftRoot(nullptr), rightRoot(nullptr) {}
    explicit Node(const T &value) : value(std::move(value)), leftRoot(nullptr), rightRoot(nullptr) {}

    // Returns max depth from two roots
    size_t max() const noexcept
    {
        const size_t left_depth{leftRoot ? leftRoot->max() : 0};
        const size_t right_depth{rightRoot ? rightRoot->max() : 0};
        return (left_depth > right_depth ? left_depth : right_depth) + 1;
    }

    virtual ~Node() = default;
};

template <typename T, typename Allocator>
struct BinaryTree<T, Allocator>::cell_display
{
    std::string str;
    bool flag{false};

    // Ctors
    explicit cell_display() : flag(false) {}
    explicit cell_display(const std::string &str) : str(str), flag(true) {}
};

template <typename T, typename Allocator>
size_t BinaryTree<T, Allocator>::counter = 0;

template <typename T, typename Allocator>
std::string BinaryTree<T, Allocator>::T_to_str(const T &value) const noexcept
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template <typename T, typename Allocator>
size_t BinaryTree<T, Allocator>::count(std::shared_ptr<BinaryTree<T, Allocator>::Node> node) const
{
    return (node == nullptr) ? 0 : (1U + count(node->leftRoot) + count(node->rightRoot));
}

template <typename T, typename Allocator>
std::vector<std::vector<struct BinaryTree<T, Allocator>::cell_display>> BinaryTree<T, Allocator>::getRowDisplay()
    const noexcept
{
    // Build a std::vector of std::vectors of Node pointers
    std::vector<std::shared_ptr<Node>> travers{};
    std::vector<std::vector<std::shared_ptr<Node>>> rows{};

    if (root == nullptr)
        return std::vector<std::vector<struct cell_display>>();

    std::shared_ptr<Node> pNode(root);
    const size_t maxDepth{root.get()->max()};

    rows.resize(maxDepth);
    size_t depth{0};

    while (true)
    {
        // Max-depth Nodes are always a node or null
        // This special case blocks deeper traversal
        if (depth == maxDepth - 1)
        {
            rows.at(depth).push_back(pNode);
            if (depth == 0)
                break;
            --depth;
            continue;
        }

        // At first go to left child.
        if (travers.size() == depth)
        {
            rows.at(depth).push_back(pNode);
            travers.push_back(pNode);
            if (pNode != nullptr)
                pNode = pNode->leftRoot;
            ++depth;
            continue;
        }

        // If child count is odd -> go to right child.
        if (rows[depth + 1UL].size() % 2UL)
        {
            pNode = travers.back();
            if (pNode)
                pNode = pNode->rightRoot;
            ++depth;
            continue;
        }

        // Exit loop if this is the root
        if (depth == 0)
            break;

        travers.pop_back();
        pNode = travers.back();
        --depth;
    }

    /* Using rows of Node pointers to populate rows of cell_display structs.
    All possible slots in the tree get a cell_display struct,
    so if there is no actual Node at a struct's location,
    its boolean "present" field is set to false.
    The struct also contains a string representation of
    its Node's value, created using a std::stringstream object. */
    std::vector<std::vector<struct cell_display>> rowsDisplay{};
    std::stringstream ss;

    for (const auto &row : rows)
    {
        rowsDisplay.emplace_back();
        for (const auto &p : row)
        {
            if (p not_eq nullptr)
            {
                ss << p->value;
                rowsDisplay.back().push_back(cell_display(ss.str()));
                ss = std::stringstream();
            }
            else
                rowsDisplay.back().push_back(cell_display());
        }
    }

    return rowsDisplay;
}

template <typename T, typename Allocator>
std::vector<std::string>
BinaryTree<T, Allocator>::rowFormat(const std::vector<std::vector<struct cell_display>> &rowsDisplay) const
{
    // First find the maximum value string length and put it in declared variable in follows line
    size_t cellWidth{0};

    for (const auto &rowDisplay : rowsDisplay)
    {
        for (const auto &a : rowDisplay)
        {
            if (a.flag and a.str.length() > cellWidth)
                cellWidth = a.str.length();
        }
    }

    if (cellWidth % 2 == 0)
        ++cellWidth;

    // Allows node nodes to be connected when they are all with size of a single character
    if (cellWidth < 3)
        cellWidth = 3;

    std::vector<std::string> formattedRows;
    size_t rowCount{rowsDisplay.size()};
    size_t rowElementCount{1UL << (rowCount - 1UL)};
    size_t leftPad{0};

    for (size_t r{0}; r < rowCount; ++r)
    {
        // r reverse-indexes the row
        const auto &cd_row{rowsDisplay.at(rowCount - r - 1UL)};
        // "space" will be the number of rows of slashes needed to get
        // from this row to the next.  It is also used to determine other
        // text offsets.
        size_t space{(1UL << r) * (cellWidth + 1UL) / 2UL - 1UL};
        // "row" holds the line of text currently being assembled
        std::string row{""};
        // iterate over each element in this row
        for (size_t c{0}; c < rowElementCount; ++c)
        {
            // add padding, more when this is not the leftmost element
            row += std::string(c ? leftPad * 2UL + 1UL : leftPad, ' ');

            if (cd_row.at(c).flag)
            {
                // This position corresponds to an existing Node
                const std::string &str{cd_row.at(c).str};

                // Try to pad the left and right sides of the value string
                // with the same number of spaces.  If padding requires an
                // odd number of spaces, right-sided children get the longer
                // padding on the right side, while left-sided children
                // get it on the left side.
                size_t longPadding{cellWidth - str.length()};
                size_t shortPadding{longPadding / 2UL};

                longPadding -= shortPadding;

                row += std::string(c % 2UL ? shortPadding : longPadding, ' ');
                row += str;
                row += std::string(c % 2UL ? longPadding : shortPadding, ' ');
            }
            else
                // This position is empty, Nodeless...
                row += std::string(cellWidth, ' ');
        }
        // A row of spaced-apart value strings is ready, add it to the result std::vector
        formattedRows.push_back(row);

        // The root has been added, so this loop is finsished
        if (rowElementCount == 1UL)
            break;

        // Add rows of forward- and back- slash characters, spaced apart
        // to "connect" two rows' Node value strings.
        // The "space" variable counts the number of rows needed here.
        size_t left_space{space + 1UL};
        size_t right_space{space - 1UL};

        for (size_t sr{0}; sr < space; ++sr)
        {
            std::string row{};
            for (size_t c{0}; c < rowElementCount; ++c)
            {
                if (c % 2UL == 0)
                {
                    row += std::string(c ? left_space * 2UL + 1UL : left_space, ' ');
                    row += cd_row.at(c).flag ? '/' : ' ';
                    row += std::string(right_space + 1UL, ' ');
                }
                else
                {
                    row += std::string(right_space, ' ');
                    row += cd_row.at(c).flag ? '\\' : ' ';
                }
            }
            formattedRows.push_back(row);
            ++left_space;
            --right_space;
        }
        leftPad += space + 1UL;
        rowElementCount /= 2UL;
    }

    // Reverse the result, placing the root node at the beginning (top)
    std::reverse(formattedRows.begin(), formattedRows.end());

    return formattedRows;
}

template <typename T, typename Allocator>
void BinaryTree<T, Allocator>::trimRows(std::vector<std::string> &rows)
{
    if (not rows.size())
        return;

    size_t minSpace{rows.front().length()};

    for (const auto &row : rows)
    {
        auto i{row.find_first_not_of(' ')};
        if (i == std::string::npos)
            i = row.length();

        if (i == 0)
            return;

        if (i < minSpace)
            minSpace = i;
    }

    for (auto &row : rows)
    {
        row.erase(0, minSpace);
    }
}

template <typename T, typename Allocator>
std::string BinaryTree<T, Allocator>::transformNumber(int num) const noexcept
{
    std::string digits{std::to_string(num)};

    if (digits.at(digits.size() - 1) == '1')
        digits += "st";
    else if (digits.at(digits.size() - 1) == '2')
        digits += "nd";
    else if (digits.at(digits.size() - 1) == '3')
        digits += "rd";
    else
        digits += "th";

    return digits;
}

template <typename T, typename Allocator>
void BinaryTree<T, Allocator>::addNode(const T &value, std::shared_ptr<Node> &node)
{
    if (node == nullptr)
        node = std::make_shared<Node>(value);
    else
    {
        if (value < node->value)
        {
            if (node->leftRoot not_eq nullptr)
                addNode(value, node->leftRoot);
            else
                node->leftRoot = std::make_shared<Node>(value);
        }
        else if (value >= node->value)
        {
            if (node->rightRoot not_eq nullptr)
                addNode(value, node->rightRoot);
            else
                node->rightRoot = std::make_shared<Node>(value);
        }
    }
}

template <typename T, typename Allocator>
std::shared_ptr<struct BinaryTree<T, Allocator>::Node> BinaryTree<T, Allocator>::certainNode(std::shared_ptr<Node> &node, size_t nodeNumber) const
{
    static std::shared_ptr<Node> pnode;

    if (node == nullptr)
        return nullptr;
    else
    {
        counter++;

        if (counter == nodeNumber)
            pnode = node;

        certainNode(node->leftRoot, nodeNumber);
        certainNode(node->rightRoot, nodeNumber);

        return pnode;
    }
}

template <typename T, typename Allocator>
std::shared_ptr<struct BinaryTree<T, Allocator>::Node>
BinaryTree<T, Allocator>::certainNode(std::shared_ptr<Node> &node, const T &value) const
{
    static std::shared_ptr<Node> pnode;

    if (node == nullptr)
        return nullptr;
    else
    {
        if (value == node->value)
            pnode = node;

        certainNode(node->leftRoot, value);
        certainNode(node->rightRoot, value);

        return pnode;
    }
}

template <typename T, typename Allocator>
size_t
BinaryTree<T, Allocator>::searchNodeNumberByValue(std::shared_ptr<Node> &node, const T &value) const
{
    static size_t nodeNumber{};

    if (node == nullptr)
        return 0;
    else
    {
        counter++;
        if (value == node->value)
            nodeNumber = counter;

        searchNodeNumberByValue(node->leftRoot, value);
        searchNodeNumberByValue(node->rightRoot, value);

        return nodeNumber;
    }
}

template <typename T, typename Allocator>
size_t BinaryTree<T, Allocator>::branches(std::shared_ptr<Node> &node, size_t nodeNumber) const
{
    size_t countOfBranches{};

    if (counter not_eq 0)
        counter = 0;

    static std::shared_ptr<Node> pNode{certainNode(node, nodeNumber)};

    if ((pNode->leftRoot not_eq nullptr) and (pNode->rightRoot not_eq nullptr))
        countOfBranches = 2;
    else if ((pNode->leftRoot not_eq nullptr) or (pNode->rightRoot not_eq nullptr))
        countOfBranches = 1;
    else
        countOfBranches = 0;

    return countOfBranches;
}

template <typename T, typename Allocator>
std::shared_ptr<struct BinaryTree<T, Allocator>::Node> BinaryTree<T, Allocator>::minValue(std::shared_ptr<Node> &node) const
{
    std::shared_ptr<Node> pnode{node};
    while (pnode->leftRoot not_eq nullptr)
        pnode = pnode->leftRoot;
    return pnode;
}

template <typename T, typename Allocator>
std::shared_ptr<struct BinaryTree<T, Allocator>::Node>
BinaryTree<T, Allocator>::maxValue(std::shared_ptr<Node> &node) const
{
    // Tree is empty
    if (node == nullptr)
        return nullptr;
    // Tree is not empty
    else
        return (node->rightRoot == nullptr) ? node : maxValue(node->rightRoot);
}

template <typename T, typename Allocator>
std::shared_ptr<struct BinaryTree<T, Allocator>::Node>
BinaryTree<T, Allocator>::previousNode(std::shared_ptr<Node> &node, size_t nodeNumber)
{
    static std::shared_ptr<Node> pprev;

    if (node == nullptr)
        return nullptr;
    else
    {
        counter++;

        if (counter == (nodeNumber - 1))
            pprev = node;

        previousNode(node->leftRoot, nodeNumber);
        previousNode(node->rightRoot, nodeNumber);

        return pprev;
    }
}

template <typename T, typename Allocator>
std::shared_ptr<struct BinaryTree<T, Allocator>::Node>
BinaryTree<T, Allocator>::nextNode(std::shared_ptr<Node> &node, size_t nodeNumber)
{
    static std::shared_ptr<Node> pnext;

    if (node == nullptr)
        return nullptr;
    else
    {
        counter++;

        if (counter == (nodeNumber + 1))
            pnext = node;

        nextNode(node->leftRoot, nodeNumber);
        nextNode(node->rightRoot, nodeNumber);

        return pnext;
    }
}

template <typename T, typename Allocator>
std::shared_ptr<struct BinaryTree<T, Allocator>::Node>
BinaryTree<T, Allocator>::removeNodeByValue(std::shared_ptr<Node> node, const T &value)
{
    // If tree is emplty -> return null
    if (node == nullptr)
        return nullptr;
    else
    {
        // If node value which we want to delete is smaller than the root's value, then it lies in left subtree
        if (value < node->value)
            node->leftRoot = removeNodeByValue(node->leftRoot, value);
        // If node value which we want to delete is greater than the root's value, then it lies in left subtree
        else if (value > node->value)
            node->rightRoot = removeNodeByValue(node->rightRoot, value);
        // If node value equals specified value -> found node which we want to delete
        else
        {
            // Case 1: Node has no child or has only 1 (left) child
            if (node->rightRoot == nullptr)
                return node->leftRoot;
            // Case 2: Node has no child or has only 1 (right) child
            else if (node->leftRoot == nullptr)
                return node->rightRoot;
            else
            {
                // Case 3: Node has 2 children
                // Smallest in the right subtree
                std::shared_ptr<Node> ptmp{minValue(node->rightRoot)};
                // Copy the inorder successor's data to this node
                node->value = ptmp->value;
                // Delete the inorder successor
                node->rightRoot = removeNodeByValue(node->rightRoot, ptmp->value);
            }
        }
    }
    return node;
}

template <typename T, typename Allocator>
BinaryTree<T, Allocator>::BinaryTree(const T &value)
{
    root = std::make_shared<Node>(value);
    root->value = value;
}

template <typename T, typename Allocator>
BinaryTree<T, Allocator>::BinaryTree(const BinaryTree *&binary_tree)
{
    root = binary_tree->root;
}

template <typename T, typename Allocator>
BinaryTree<T, Allocator> &BinaryTree<T, Allocator>::operator=(const BinaryTree *&binary_tree)
{
    // Checking self-assignment
    if (this == binary_tree)
        return *this;

    root = binary_tree->root;

    return *this;
}

template <typename T, typename Allocator>
inline size_t BinaryTree<T, Allocator>::getMaxDepth() const { return root ? root->max() : 0; }

template <typename T, typename Allocator>
void BinaryTree<T, Allocator>::show() const
{
    const size_t d{getMaxDepth()};

    // Check if tree is empty
    if (d == 0)
    {
        std::cout << "Tree is empty " << std::endl;
        return;
    }

    // This tree is not empty, so get a list of node values
    const auto rowDisp{getRowDisplay()};

    // Format these into a text representation
    auto formattedRows{rowFormat(rowDisp)};

    // Trim excess space characters from the left sides of the text
    trimRows(formattedRows);

    for (const auto &row : formattedRows)
        std::cout << ' ' << row << std::endl;
}

template <typename T, typename Allocator>
void BinaryTree<T, Allocator>::addNode(const T &value)
{
    addNode(value, root);
}

template <typename T, typename Allocator>
void BinaryTree<T, Allocator>::printCountOfNodes() const
{
    size_t nodes{count(root)};
    std::cout << "Count of nodes = " << nodes << std::endl;
}

template <typename T, typename Allocator>
void BinaryTree<T, Allocator>::printBranchesOfCertainNode(size_t nodeNumber)
{
    size_t branchesCount{branches(root, nodeNumber)};

    if ((nodeNumber == 0) or (nodeNumber >= count(root)))
        branchesCount = 0;

    std::cout << "Count of branches on node " << nodeNumber << " is " << branchesCount << std::endl;
}

template <typename T, typename Allocator>
void BinaryTree<T, Allocator>::printValueByNode(size_t nodeNumber)
{
    if (counter not_eq 0)
        counter = 0;

    std::shared_ptr<Node> pnode{certainNode(root, nodeNumber)};
    if ((nodeNumber == 0) or (nodeNumber >= count(root)))
        if constexpr (std::is_copy_assignable_v<T>)
            pnode->value = T{};
    std::cout << "Value of " << transformNumber(nodeNumber) << " node is " << T_to_str(pnode->value) << std::endl;
}

template <typename T, typename Allocator>
void BinaryTree<T, Allocator>::printNodeNumberByValue(const T &value)
{
    if (counter not_eq 0)
        counter = 0;

    size_t nodeNumber{searchNodeNumberByValue(root, value)};
    if (nodeNumber == 0)
        std::cout << "The binary tree does not contain value " << T_to_str(value) << std::endl;
    else
        std::cout << "The value \"" << T_to_str(value) << "\" is in " << transformNumber(nodeNumber) << " node " << std::endl;
}

template <typename T, typename Allocator>
void BinaryTree<T, Allocator>::searchMin()
{
    std::shared_ptr<Node> pnode{minValue(root)};
    std::cout << "Min value = " << T_to_str(pnode->value) << std::endl;
}

template <typename T, typename Allocator>
void BinaryTree<T, Allocator>::searchMax()
{
    std::shared_ptr<Node> pnode = maxValue(root);
    std::cout << "Max value = " << T_to_str(pnode->value) << std::endl;
}

template <typename T, typename Allocator>
void BinaryTree<T, Allocator>::removeNode(const T &value)
{
    if (counter not_eq 0)
        counter = 0;

    if (root == nullptr)
        std::cout << "There is no value " << T_to_str(value) << std::endl;
    else
        removeNodeByValue(root, value);
}

#endif // BINTREE_IMPL_HPP
