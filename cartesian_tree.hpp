#pragma once

#include "cartesian_node.hpp"

namespace Trees
{
    class CartesianTree
    {
    private:
        CartesianNode *top;

    public:
        void insert(int key);
        int findKthStats();
        int countLess(int upperBound);
    }
}