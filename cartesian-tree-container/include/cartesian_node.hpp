#pragma once

#include <random>

namespace Trees
{
    struct CartesianNode
    {
        /* Ключ */
        int key_;
        /* Приоритет балансирования */
        int prior_ = std::rand();
        /* Размер поддерева */
        int size_ = 1;

        /* Родительская вершина для поддержки прямого обхода дерева */
        CartesianNode *root = nullptr;

        CartesianNode *l = nullptr;
        CartesianNode *r = nullptr;

        CartesianNode(int key) : key_(key) {}

        /* Метод для получения размера поддерева */
        static int size(CartesianNode *node) noexcept;

        /* Метод для пересчёта полей вершины */
        void recalc() noexcept;

        /* Методы подвешивающие вершины */
        void hangL(CartesianNode *node) noexcept;
        void hangR(CartesianNode *node) noexcept;

        /* Метод для разделения дерева по ключу(ключ в правом поддереве) */
        static CartesianNode *merge(CartesianNode *lTree, CartesianNode *rTree);
        /* Метод для слияния двух деревьев */
        static std::pair<CartesianNode *, CartesianNode *> split(CartesianNode *tree, int index);
        /* Метод для вставки */
        static CartesianNode *insert(CartesianNode *tree, CartesianNode *node) noexcept;

        ~CartesianNode();
    };
}