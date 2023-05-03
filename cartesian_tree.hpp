#pragma once

#include "cartesian_node.hpp"

namespace Trees
{
    class CartesianTree
    {
    public: 
        using iterator = CartesianNode *;

    private:
        using split_pair = std::pair<CartesianTree &, CartesianTree &>;

    private:
        CartesianNode *top;

    private: // Обслуживающие
        static CartesianTree &merge(CartesianTree &lTree, CartesianTree &rTree);
        static split_pair split(CartesianTree& tree, int index);

    public: // Селекторы
        iterator findKthStats() const;
        int countLess(int upperBound) const;

    public: // Модификаторы
        void insert(int key);
    };
}