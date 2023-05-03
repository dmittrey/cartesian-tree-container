#pragma once

#include <random>

namespace Trees
{
    class CartesianTree
    {
        struct CartesianNode
        {
            int key_;
            int prior_ = std::rand();
            int size_ = 1; /* Размер поддерева */

            CartesianNode *l = nullptr;
            CartesianNode *r = nullptr;

            CartesianNode(int key) : key_(key) {}

            /* Метод для пересчёта полей вершины */
            void recalc() noexcept
            {
                size_ = 1;

                if (l != nullptr)
                    size_ += l->size_;
                if (r != nullptr)
                    size_ += r->size_;
            }
        };

    private:
        CartesianNode *top = nullptr;

    public: // Конструкторы
        CartesianTree(int key) : top(new CartesianNode(key)) {}

    private: // Обслуживающие
        /* Метод для разделения дерева по ключу(ключ в правом поддереве) */
        static CartesianNode *merge(CartesianNode *lTree, CartesianNode *rTree);
        /* Метод для слияния двух деревьев */
        static std::pair<CartesianNode *, CartesianNode *> split(CartesianNode *tree, int index);
        /* Метод для вставки */
        static CartesianNode *insert(CartesianNode *tree, CartesianNode *node) noexcept;
        /* Метод для получения размера поддерева */
        static int size(CartesianNode *node) noexcept;

    public: // Селекторы
        int findKthStats(int k) const noexcept;
        int countLess(int upperBound) const noexcept;

    public: // Модификаторы
        void insert(int key) noexcept;
    };
}