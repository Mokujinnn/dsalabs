#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <iomanip>
#include <chrono>

#include "rbtree.hpp"

int main()
{

    Rbtree Tree;

    int n = 10;

    auto s = std::chrono::steady_clock::now();

    for (int i = 0; i < n; i++)
    {
        Tree.add(i, "");
    }

    auto e = std::chrono::steady_clock::now();
    auto sec = std::chrono::duration_cast<std::chrono::nanoseconds>(e - s);
    std::cout << std::fixed << std::setprecision(9) << sec.count()/1.0e+9 << '\n';

	Tree.print();

    Tree.del(9);
    Tree.del(4);
	Tree.del(3);

    Tree.print();

    std::cout << Tree.lookupCountOfNods(49999) << '\n';

	std::cout << Tree.isRbtree();

	return 0;
}