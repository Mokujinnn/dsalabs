#include <iostream>
#include "Skiplist.hpp"

int main()
{

    Skiplist list;

    list.insert(10,"aboba");
    list.insert(10,"aboba");
    list.insert(20, "");
    list.insert(22,"asd");

    list.remove(10);
    list.remove(10);

    std::cout << list.search(20) << '\n' << list.search(10);

    return 0;
}