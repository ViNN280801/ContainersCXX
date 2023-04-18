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
    std::cout << "Min = " << dict.min() << std::endl;
    std::cout << "Max = " << dict.max() << std::endl;
    dict.get_key();
    dict.erase(5);
    dict.erase(4);
    std::cout << "Size after deleting element = " << dict.size() << std::endl;
    dict.insert(56, "1928ufij");
    dict.insert(56, "29347");
    dict.insert(10, "test");
    dict.insert(0, "MAXIMAL VALUE");
    std::cout << dict.at(56) << std::endl;
    std::cout << "Min = " << dict.min() << std::endl;
    std::cout << "Max = " << dict.max() << std::endl;

    return 0;
}
