#pragma once

#include "cartesian_node.hpp"

namespace Trees
{
    class CartesianTree
    {
    public:
        using iterator = CartesianNode *;

    private:
        using split_pair = std::pair<CartesianNode *, CartesianNode *>;

    private:
        CartesianNode *top;

    private: // Обслуживающие
        /* Метод для разделения дерева по ключу(ключ в правом поддереве) */
        static CartesianNode *merge(CartesianNode *lTree, CartesianNode *rTree);
        /* Метод для слияния двух деревьев */
        static split_pair split(CartesianNode *tree, int index);

    public: // Селекторы
        iterator findKthStats() const;
        int countLess(int upperBound) const;

    public: // Модификаторы
        void insert(int key);
    };
}