#include <iostream>
#include <iomanip>
#include <chrono>
#include "Prefixtree.hpp"

int main()
{
    Prefixtree tree;

    tree.insert("zxc");
    tree.insert("aboba");
    tree.insert("apple");
    tree.insert("pineapple");

    tree.print();

    tree.remove("zxc");
    tree.remove("apple");

    tree.print();
    return 0;
}