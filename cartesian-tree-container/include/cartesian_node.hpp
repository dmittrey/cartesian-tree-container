#pragma once

#include <random>

namespace Trees
{
    template <typename T>
    struct CartesianNode
    {
        /* Ключ */
        T key_;
        /* Приоритет балансирования */
        int prior_ = std::rand();
        /* Размер поддерева */
        int size_ = 1;

        /* Родительская вершина для поддержки прямого обхода дерева */
        CartesianNode<T> *root = nullptr;

        CartesianNode<T> *l = nullptr;
        CartesianNode<T> *r = nullptr;

        CartesianNode(T key) : key_(key) {}

        /* Метод для получения размера поддерева */
        static int size(CartesianNode<T> *node) noexcept;

        /* Метод для пересчёта полей вершины */
        void recalc() noexcept;

        /* Методы подвешивающие вершины */
        void hangL(CartesianNode<T> *node) noexcept;
        void hangR(CartesianNode<T> *node) noexcept;

        /* Метод для разделения дерева по ключу(ключ в правом поддереве) */
        static CartesianNode<T> *merge(CartesianNode<T> *lTree, CartesianNode<T> *rTree);
        /* Метод для слияния двух деревьев */
        static std::pair<CartesianNode<T> *, CartesianNode<T> *> split(CartesianNode<T> *tree, int index);
        /* Метод для вставки */
        static CartesianNode<T> *insert(CartesianNode<T> *tree, CartesianNode<T> *node) noexcept;

        ~CartesianNode();
    };

    template <typename T>
    int CartesianNode<T>::size(CartesianNode<T> *node) noexcept
    {
        return (node == nullptr) ? 0 : node->size_;
    }

    template <typename T>
    void CartesianNode<T>::recalc() noexcept
    {
        size_ = 1;

        if (l != nullptr)
            size_ += l->size_;
        if (r != nullptr)
            size_ += r->size_;
    }

    template <typename T>
    void CartesianNode<T>::hangL(CartesianNode<T> *node) noexcept
    {
        l = node;
        if (node != nullptr)
            node->root = this;
    }

    template <typename T>
    void CartesianNode<T>::hangR(CartesianNode<T> *node) noexcept
    {
        r = node;
        if (node != nullptr)
            node->root = this;
    }

    template <typename T>
    CartesianNode<T> *CartesianNode<T>::merge(CartesianNode<T> *lTree, CartesianNode<T> *rTree)
    {
        if (lTree == nullptr && rTree == nullptr)
            return nullptr;
        if (lTree == nullptr)
            return rTree;
        if (rTree == nullptr)
            return lTree;

        if (lTree->prior_ >= rTree->prior_)
        {
            lTree->hangR(merge(lTree->r, rTree));
            lTree->recalc();
            return lTree;
        }
        else
        {
            rTree->hangL(merge(lTree, rTree->l));
            rTree->recalc();
            return rTree;
        }
    }

    template <typename T>
    std::pair<CartesianNode<T> *, CartesianNode<T> *> CartesianNode<T>::split(CartesianNode<T> *tree, int index)
    {
        if (tree == nullptr)
            return {nullptr, nullptr};

        if (index < tree->key_) //  Ключ в правом поддереве
        {
            auto [l, r] = split(tree->l, index);
            tree->hangL(r);
            tree->recalc();
            return {l, tree};
        }
        else
        {
            auto [l, r] = split(tree->r, index);
            tree->hangR(l);
            tree->recalc();
            return {tree, r};
        }
    }

    template <typename T>
    CartesianNode<T> *CartesianNode<T>::insert(CartesianNode<T> *tree, CartesianNode<T> *node) noexcept
    {
        if (tree == nullptr)
        {
            return node;
        }

        if (node->prior_ > tree->prior_)
        {
            auto [l, r] = split(tree, node->key_);
            node->hangL(l);
            node->hangR(r);
            node->recalc();
            return node;
        }
        else
        {
            if (node->key_ < tree->key_)
                tree->hangL(insert(tree->l, node));
            else
                tree->hangR(insert(tree->r, node));

            tree->recalc();
            return tree;
        }
    }

    template <typename T>
    CartesianNode<T>::~CartesianNode()
    {
        if (l != nullptr && r != nullptr)
        {
            /* Правая вершина заменит нас */
            if (r->prior_ >= l->prior_)
            {
                /* Правое поддерево без изменений, а левое поддерево будет результатом слияния
                    текущего левого поддерева и левого поддерева r*/
                r->hangL(merge(l, r->l));
                r->root = root;
                if (root != nullptr)
                {
                    if (root->r == this)
                    {
                        root->r = r;
                    }
                    else
                    {
                        root->l = r;
                    }
                }
            }
            /* Левая вершина заменит нас (аналогичный алгоритм) */
            else
            {
                l->hangR(merge(l->r, r));
                l->root = root;
                if (root != nullptr)
                {
                    if (root->r == this)
                    {
                        root->r = l;
                    }
                    else
                    {
                        root->l = l;
                    }
                }
            }
        }
        else
        {
            /* Поменяли родителя правого ребёнка на нашего родителя */
            if (l != nullptr)
            {
                l->root = root;
                if (root != nullptr)
                {
                    if (root->r == this)
                    {
                        root->r = l;
                    }
                    else
                    {
                        root->l = l;
                    }
                }
            }
            else if (r != nullptr)
            {
                r->root = root;
                if (root != nullptr)
                {
                    if (root->r == this)
                    {
                        root->r = r;
                    }
                    else
                    {
                        root->l = r;
                    }
                }
            }
            else
            {
                if (root != nullptr)
                {
                    if (root->r == this)
                    {
                        root->r = nullptr;
                    }
                    else
                    {
                        root->l = nullptr;
                    }
                }
            }
        }
    }
};