#include <iostream>

#include "vector.hpp"
#include "vector_impl.hpp"

int main()
{
    Vector<int> v(5);
    v.push_back(-9);
    v.push_back(69);
    v.push_back(56);
    v.push_back(45);
    v.push_back(-1);

    v.print();

    std::cout << v.at(2) << '\t' << v[0] << '\n';

    v.resize(3);
    v.print();

    return EXIT_SUCCESS;
}
