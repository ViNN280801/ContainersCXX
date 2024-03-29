#include <iostream>

#include "bintree.hpp"
#include "bintree_impl.hpp"

int main()
{
    BinaryTree<int> bin_tree;
    std::cout << "Customly created binary tree: " << std::endl;

    bin_tree.addNode(9);
    bin_tree.addNode(1);
    bin_tree.addNode(46);
    bin_tree.addNode(20);
    bin_tree.addNode(68);
    bin_tree.addNode(15);
    bin_tree.addNode(5);
    bin_tree.addNode(0);
    bin_tree.addNode(6);
    bin_tree.addNode(55);
    bin_tree.addNode(95);

    bin_tree.show();
    bin_tree.printCountOfNodes();
    bin_tree.printBranchesOfCertainNode(2);
    bin_tree.printValueByNode(2);
    bin_tree.printNodeNumberByValue(1);
    bin_tree.searchMin();
    bin_tree.searchMax();

    std::cout << "Which value you want to delete from binary tree: ";
    int toRemove{};
    std::cin >> toRemove;
    bin_tree.removeNode(toRemove);

    std::cout << "\nBinary tree after removing " << toRemove << ": " << std::endl;
    bin_tree.show();

    BinaryTree<std::string> bin_tree_str;
    std::cout << "Customly created binary tree: " << std::endl;

    bin_tree_str.addNodes("i", "b", "jk", "asda", "gh", "ri");

    bin_tree_str.show();
    bin_tree_str.printCountOfNodes();
    bin_tree_str.printBranchesOfCertainNode(1);
    bin_tree_str.printValueByNode(1);
    bin_tree_str.printNodeNumberByValue("gh");
    bin_tree_str.searchMin();
    bin_tree_str.searchMax();

    return EXIT_SUCCESS;
}