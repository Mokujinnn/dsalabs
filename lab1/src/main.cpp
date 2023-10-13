#include <iostream>
#include <string>

#include "rbtree.hpp"

int main()
{

    Rbtree Tree;

    int n = 20;

    for (int i = 0; i < n; i++)
    {
        Tree.add(i, "");
    }

    Tree.print();

    Tree.del(7);
    Tree.del(1);

    Tree.print();

    return 0;
}