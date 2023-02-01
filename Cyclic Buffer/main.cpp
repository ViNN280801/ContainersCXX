#include "CyclicBuffer.hpp"
#include "CyclicBuffer.cpp"

int main()
{
    CyclicBuffer<int> cb;

    cb.insert(5);
    cb.insert(3);
    cb.insert(7);
    cb.insert(9);
    cb.insert(1);

    std::cout << "Size = " << cb.getSize() << std::endl;
    std::cout << "Capacity = " << cb.getCapacity() << std::endl;
    cb.printBuffer();

    cb.clear();
    std::cout << "After clearing out: " << std::endl;
    std::cout << "Size = " << cb.getSize() << std::endl;
    std::cout << "Capacity = " << cb.getCapacity() << std::endl;
    cb.printBuffer();

    cb.insert(64);
    std::cout << "Size = " << cb.getSize() << std::endl;
    std::cout << "Capacity = " << cb.getCapacity() << std::endl;
    cb.printBuffer();

    cb.resizeCapacity(7UL);
    std::cout << "Size = " << cb.getSize() << std::endl;
    std::cout << "Capacity = " << cb.getCapacity() << std::endl;

    cb.insert(-6812);
    cb.insert(983);
    cb.insert(-1236);
    cb.insert(597);
    cb.insert(1347);
    cb.insert(42759);
    std::cout << "Size = " << cb.getSize() << std::endl;
    std::cout << "Capacity = " << cb.getCapacity() << std::endl;
    cb.printBuffer();

    cb.insert(-792);
    std::cout << "Size = " << cb.getSize() << std::endl;
    std::cout << "Capacity = " << cb.getCapacity() << std::endl;
    cb.printBuffer();

    cb.clear();
    cb.printBuffer();

    return EXIT_SUCCESS;
}
