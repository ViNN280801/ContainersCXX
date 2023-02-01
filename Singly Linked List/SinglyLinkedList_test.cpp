#include "SinglyLinkedList.hpp"

int main()
{
    List<int> list;
    list.push_back(5);
    list.push_back(7);
    list.push_back(10);

    list.fill_random(5UL, 1, 10);

    std::cout << "List: " << std::endl;
    list.show();
    list.pop_front();
    std::cout << std::endl << "List after removing 1st link of list: " << std::endl;
    list.show(true);

    std::cout << std::endl << "Size of list = " << list.size() << std::endl;
    std::cout << "Clearing list ... " << std::endl;
    list.clear();
    std::cout << "Size of list after clear = " << list.size() << std::endl;
    std::cout << "List after clear: " << std::endl;
    list.show(true);

    list.fill_random(5UL, 1, 10);
    std::cout << std::endl << "List: " << std::endl;
    list.show(true);
    list.push_front(6);
    std::cout << std::endl << "List after pushing element to front: " << std::endl;
    list.show(true);

    std::cout << std::endl << "List after inserting element to 3rd index: " << std::endl;
    list.insert(19, 3UL);
    list.show(true);

    std::cout << std::endl << "List after deleting element at 5th index: " << std::endl;
    list.remove_at(5UL);
    list.show(true);

    std::cout << std::endl << "List after deleting last link of list: " << std::endl;
    list.pop_back();
    list.show(true);
    
    // Trying to get access index which doesn't exist in list
    // Will provoke exception
    /* std::cout << list[10] << std::endl; */

    return EXIT_SUCCESS;
}