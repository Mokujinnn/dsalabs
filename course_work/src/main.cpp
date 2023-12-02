#include <iostream>
#include <ctime>
#include "Skiplist.hpp"

int main()
{
    srand(time(NULL));
    Skiplist list;

    list.insert(10,"aboba");
    list.insert(10,"aboba");
    list.insert(20, "");
    list.insert(22,"asd");
    list.insert(242,"assd");
    list.insert(1,"asd");
    list.insert(2,"asd");

    list.remove(10);
    list.remove(10);

    std::cout << list.search(20) << '\n' << list.search(10) << '\n';

    list.display();
    return 0;
}