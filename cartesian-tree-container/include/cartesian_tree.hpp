#pragma once

#include "cartesian_node.hpp"

namespace Trees
{
    class CartesianTree
    {
    private:
        /* Корень дерева */
        CartesianNode *top = nullptr;

    public:
        class Iterator;

        /* Первый элемент в контейнере */
        Iterator begin();
        /* Следующий после последнего элемента в контейнере */
        Iterator end();

        /* Поиск k-ой меньшей статистики начиная с индекса 0 */
        int findKthStats(int k) const;
        /* Поиск кол-ва элементов в дереве меньших чем upperBound */
        int countLess(int upperBound) const noexcept;

        /* Вставка ключа в дерево */
        void insert(int key) noexcept;

        ~CartesianTree();
    };

    class CartesianTree::Iterator
    {
    private:
        CartesianNode *p_;

    public:
        Iterator(CartesianNode *p) : p_(p) {}

    public:
        bool operator!=(Iterator const &other) const;

        int operator*() const;

        Iterator &operator++();
    };
}