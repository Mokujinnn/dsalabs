#include <iostream>
#include <string>

#include "rbtree.hpp"

int main()
{
    
    Rbtree tree;

    tree.add(1021, "pppapdds");
    tree.add(882, "hsy1");
    tree.add(2039, "pimpam");
    tree.add(12, "rapapa");
    tree.add(1488, "kepka");
    tree.add(1337, "shapka");

    tree.print(&tree);

    return 0;
}