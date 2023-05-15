#include <iostream>

#include "cartesian_tree.hpp"

int main()
{
    Trees::CartesianTree<int> tree;
    std::vector<int> vec;
    for (size_t i = 0; i < 10000; ++i)
    {
        for (size_t k = 0; k < 500; ++k)
        {
            auto i = std::rand();
            tree.insert(i);
            vec.push_back(i);
        }
        clock_t start1 = clock();
        auto count1 = tree.findKthStats(100);
        clock_t end1 = clock();
        double clocks1 = (double)(end1 - start1);

        auto count2 = 0;
        clock_t start2 = clock();
        for (size_t n = 0; n < vec.size(); ++n)
        {
            ++count2;
        }
        clock_t end2 = clock();
        double clocks2 = (double)(end2 - start2);
        std::cout << i * 500 << " " << clocks1 << " " << clocks2 << std::endl;
    }
}