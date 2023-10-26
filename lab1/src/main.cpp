#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "rbtree.hpp"

int main()
{

    Rbtree Tree;

    int n = 100;

    for (int i = 0; i < n; i++)
    {
        Tree.add(rand()%n, "");
    }

	Tree.print();

    Tree.del(11);
    Tree.del(4);
	Tree.del(3);

    Tree.print();

	std::cout << Tree.isRbtree();

	return 0;
}