#pragma once

#include <random>

namespace Trees
{
    template <typename T>
    struct CartesianNode : public std::enable_shared_from_this<CartesianNode<T>>
    {
        /* Ключ */
        T key_;
        /* Приоритет балансирования */
        int prior_ = std::rand();
        /* Размер поддерева */
        int size_ = 1;

        /* Родительская вершина для поддержки прямого обхода дерева */
        std::weak_ptr<CartesianNode<T>> root;

        std::shared_ptr<CartesianNode<T>> left, right;

        CartesianNode(T key) : key_(key) {}

        /* Метод для получения размера поддерева */
        static int size(std::shared_ptr<CartesianNode<T>> node) noexcept;

        /* Метод для пересчёта полей вершины */
        void recalc() noexcept;

        /* Методы подвешивающие вершины */
        void hangL(std::shared_ptr<CartesianNode<T>> node) noexcept;
        void hangR(std::shared_ptr<CartesianNode<T>> node) noexcept;

        void assignParent(std::shared_ptr<CartesianNode<T>> node) noexcept;

        /* Метод для разделения дерева по ключу(ключ в правом поддереве) */
        static std::shared_ptr<CartesianNode<T>> merge(std::shared_ptr<CartesianNode<T>> lTree, std::shared_ptr<CartesianNode<T>> rTree) noexcept;
        /* Метод для слияния двух деревьев */
        static std::pair<std::shared_ptr<CartesianNode<T>>, std::shared_ptr<CartesianNode<T>>> split(std::shared_ptr<CartesianNode<T>> tree, int index) noexcept;
        /* Метод для вставки */
        static std::shared_ptr<CartesianNode<T>> insert(std::shared_ptr<CartesianNode<T>> tree, std::shared_ptr<CartesianNode<T>> node) noexcept;

        /* Можем отнаследоваться */
        virtual ~CartesianNode();
    };

    template <typename T>
    int CartesianNode<T>::size(std::shared_ptr<CartesianNode<T>> node) noexcept
    {
        return (node) ? node->size_ : 0;
    }

    template <typename T>
    void CartesianNode<T>::recalc() noexcept
    {
        size_ = 1 + size(left) + size(right);
    }

    template <typename T>
    void CartesianNode<T>::hangL(std::shared_ptr<CartesianNode<T>> node) noexcept
    {
        left = node;
        if (node)
            node->root = this->shared_from_this();
    }

    template <typename T>
    void CartesianNode<T>::hangR(std::shared_ptr<CartesianNode<T>> node) noexcept
    {
        right = node;
        if (node)
            node->root = this->shared_from_this();
    }

    template <typename T>
    std::shared_ptr<CartesianNode<T>> CartesianNode<T>::merge(std::shared_ptr<CartesianNode<T>> lTree, std::shared_ptr<CartesianNode<T>> rTree) noexcept
    {
        if (lTree == nullptr && rTree == nullptr)
            return nullptr;
        if (lTree == nullptr)
            return rTree;
        if (rTree == nullptr)
            return lTree;

        if (lTree->prior_ >= rTree->prior_)
        {
            lTree->hangR(merge(lTree->right, rTree));
            lTree->recalc();
            return lTree;
        }
        else
        {
            rTree->hangL(merge(lTree, rTree->left));
            rTree->recalc();
            return rTree;
        }
    }

    template <typename T>
    std::pair<std::shared_ptr<CartesianNode<T>>, std::shared_ptr<CartesianNode<T>>> CartesianNode<T>::split(std::shared_ptr<CartesianNode<T>> tree, int index) noexcept
    {
        if (tree == nullptr)
            return {nullptr, nullptr};

        if (index < tree->key_) //  Ключ в правом поддереве
        {
            auto [left, right] = split(tree->left, index);
            tree->hangL(right);
            tree->recalc();
            return {left, tree};
        }
        else
        {
            auto [left, right] = split(tree->right, index);
            tree->hangR(left);
            tree->recalc();
            return {tree, right};
        }
    }

    template <typename T>
    std::shared_ptr<CartesianNode<T>> CartesianNode<T>::insert(std::shared_ptr<CartesianNode<T>> tree, std::shared_ptr<CartesianNode<T>> node) noexcept
    {
        if (tree == nullptr)
            return node;

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
                tree->hangL(insert(tree->left, node));
            else
                tree->hangR(insert(tree->right, node));

            tree->recalc();
            return tree;
        }
    }

    template <typename T>
    CartesianNode<T>::~CartesianNode()
    {
        auto shd_root = root.lock();

        if (left && right)
        {
            if (right->prior_ >= left->prior_)
            {
                right->hangL(merge(left, right->left));
                if (shd_root)
                {
                    if (&(*shd_root->right) == this)
                        shd_root->hangR(right);
                    else
                        shd_root->hangL(right);
                }
            }
            else
            {
                left->hangR(merge(left->right, right));
                if (shd_root)
                {
                    if (&(*shd_root->right) == this)
                        shd_root->hangR(left);
                    else
                        shd_root->hangL(left);
                }
            }
        }
        else
        {
            if (shd_root)
            {
                if (left)
                {
                    if (&(*shd_root->right) == this)
                        shd_root->hangR(left);
                    else
                        shd_root->hangL(left);
                }
                else if (right)
                {
                    if (&(*shd_root->right) == this)
                        shd_root->hangR(right);
                    else
                        shd_root->hangL(right);
                }
                else
                {
                    if (&(*shd_root->right) == this)
                        shd_root->hangR(nullptr);
                    else
                        shd_root->hangL(nullptr);
                }
            }
        }
    }
};