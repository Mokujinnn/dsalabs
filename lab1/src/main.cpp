#include <iostream>
#include <string>

#include "rbtree.hpp"

int main()
{

    Rbtree Tree;

    int n = 100;

    for (int i = 0; i < n; i++)
    {
        Tree.add(i, "");
    }

    Tree.print();


    return 0;
}