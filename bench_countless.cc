#include <iostream>

#include "cartesian_tree.hpp"

int main()
{
    Trees::CartesianTree<int> tree;
    std::vector<int> vec;
    for (size_t i = 0; i < 20000; ++i)
    {
        for (size_t k = 0; k < 1000; ++k)
        {
            auto i = std::rand();
            tree.insert(i);
            vec.push_back(i);
        }
        clock_t start1 = clock();
        auto count1 = tree.countLess(std::rand());
        clock_t end1 = clock();
        double clocks1 = (double)(end1 - start1);

        std::cout << i * 500 << " " << clocks1 << std::endl;
    }
}