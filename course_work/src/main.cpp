#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <fstream>
#include <vector>
#include "Skiplist.hpp"

int main()
{
    srand(time(NULL));

    
    std::ofstream file("output.txt", std::ios_base::out);
    std::ofstream file1("output1.txt", std::ios_base::out);
    std::ofstream file2("output2.txt", std::ios_base::out);

    file << std::fixed << std::setprecision(9);
    file1 << std::fixed << std::setprecision(9);
    file2 << std::fixed << std::setprecision(9);

    std::cout << std::fixed << std::setprecision(9);

    file << "n," << "t\n";
    file1 << "n," << "t\n";
    file2 << "n," << "t\n";

    int n = 100000;
    int sravn = 2000;

    int max = n / sravn;
    std::vector<double> v(max, 0);

    int k = 0;

    Skiplist *l = new Skiplist;

    for (int i = 0; i < 1000; ++i)
    {
        l->insert(i, "");
    }

    delete l;
    auto start = std::chrono::steady_clock::now();

    for (int j = 0; j < 10; ++j)
    {
        Skiplist list(8, 0.5);
        k = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i % sravn == 0)
            {
                list.insert(i, "");
                auto s = std::chrono::steady_clock::now();

                list.search(i);

                auto e = std::chrono::steady_clock::now();
                auto sec = std::chrono::duration_cast<std::chrono::nanoseconds>(e - s);

                v[k] += sec.count() / 1.0e+9;
                ++k;
                // file << i + 1 << ", " << sec.count() / 1.0e+9 << std::endl;

            }
            else
            {
                list.insert(i, "");
            }
        }
    }

    for (int i = 0; i < v.size(); ++i)
    {
        v[i] /= 10;

        file << i * sravn << ", " << v[i] << '\n';
    }

    v.clear();
    v.resize(max, 0);

    for (int j = 0; j < 10; ++j)
    {
        Skiplist list25(8, 0.25);
        k = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i % sravn == 0)
            {
                list25.insert(i, "");
                auto s = std::chrono::steady_clock::now();

                list25.search(i);

                auto e = std::chrono::steady_clock::now();
                auto sec = std::chrono::duration_cast<std::chrono::nanoseconds>(e - s);

                v[k] += sec.count() / 1.0e+9;
                ++k;
                // file1 << i + 1 << ", " << sec.count() / 1.0e+9 << std::endl;
            }
            else
            {
                list25.insert(i, "");
            }
        }
    }

    for (int i = 0; i < v.size(); ++i)
    {
        v[i] /= 10;

        file1 << i * sravn << ", " << v[i] << '\n';
    }

    v.clear();
    v.resize(max, 0);

    for (int j = 0; j < 10; ++j)
    {
        Skiplist list33(8, 0.35);
        k = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i % sravn == 0)
            {
                list33.insert(i, "");
                auto s = std::chrono::steady_clock::now();

                list33.search(i);

                auto e = std::chrono::steady_clock::now();
                auto sec = std::chrono::duration_cast<std::chrono::nanoseconds>(e - s);

                v[k] += sec.count() / 1.0e+9;
                ++k;
                // file1 << i + 1 << ", " << sec.count() / 1.0e+9 << std::endl;
            }
            else
            {
                list33.insert(i, "");
            }
        }
    }

    for (int i = 0; i < v.size(); ++i)
    {
        v[i] /= 10;

        file2 << i * sravn << ", " << v[i] << '\n';
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsedtime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    file.close();
    file1.close();
    file2.close();

    // list.display();

    std::cout << "elapsed time: " << elapsedtime.count() / 1.0e+9 << " seconds\n";

    // std::cout << list.search(20) << '\n' << list.search(10) << '\n';

    // list.display();
    return 0;
}