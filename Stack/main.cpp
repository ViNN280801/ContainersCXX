#include <iostream>

#include "stack.hpp"
#include "stack_impl.hpp"

int main()
{
    Stack<int> s;
    s.push(5);
    s.push(4);
    s.push(10);
    s.pop();
    s.push(7);

    while (!s.empty())
    {
        std::cout << s.top() << '\t';
        s.pop();
    }
    std::endl(std::cout);

    std::cout << s.empty() << std::endl;

    s.push(-4508);
    s.push(34758);
    s.push(-1289);
    s.push(12794);
    s.push(19842);
    s.clear();
    std::cout << s.empty() << std::endl;

    return EXIT_SUCCESS;
}