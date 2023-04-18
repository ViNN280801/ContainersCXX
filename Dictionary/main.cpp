#include <iostream>

#include "include/dictionary.hpp"
#include "include/dictionary_impl.hpp"

using namespace std::string_literals;

int main()
{
    Dictionary<int, std::string> dict(4, "This is a string"s);
    std::cout << dict.at(4) << std::endl;
    std::cout << dict.get(4) << std::endl;
    // std::cout << dict.at(5) << std::endl;
    std::cout << dict.get(100) << std::endl;

    dict.set(4, "new string");
    std::cout << dict.at(4) << std::endl;

    std::cout << dict.is_set(4) << '\t' << dict.is_set(45) << std::endl;
    dict.get_key();

    return 0;
}
