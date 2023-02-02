#include "VectorCyclicBuffer.hpp"
#include "VectorCyclicBuffer.cpp"

int main()
{
    VectorCyclicBuffer<std::string> cb(5UL);
    std::cout << "Size = " << cb.getSize() << std::endl;
    std::cout << "Capacity = " << cb.getCapacity() << std::endl;
    cb.try_pushFront("asfhi278");
    cb.printBuffer();
    cb.try_pushBack("73489");
    cb.printBuffer();
    cb.try_pushBack("H@IO@AD@30i");
    cb.printBuffer();
    cb.try_pushFront("38940fipok");
    cb.printBuffer();
    cb.try_pushFront("123");
    cb.printBuffer();
    cb.try_pushBack("FRONT");
    cb.printBuffer();
    cb.try_popBack();
    cb.printBuffer();
    cb.try_popBack();
    cb.printBuffer();
    cb.try_popFront();
    cb.printBuffer();
    cb.try_popBack();
    cb.printBuffer();
    cb.try_popFront();
    cb.printBuffer();
    cb.try_pushBack("2738hudA!12");
    cb.printBuffer();
    cb.try_pushBack("4RIJOAP");
    cb.printBuffer();
    cb.try_pushBack("3iopk");
    cb.printBuffer();
    cb.try_pushBack("3oe3");
    cb.printBuffer();
    cb.try_pushBack("2g387idu");
    cb.printBuffer();

    return EXIT_SUCCESS;
}
