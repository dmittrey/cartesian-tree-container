#pragma once

#include "cartesian_node.hpp"

namespace Trees
{
    template <typename T>
    class CartesianTree final
    {
    private:
        /* Корень дерева */
        std::shared_ptr<CartesianNode<T>> top;

    public:
        class Iterator;

        /* Первый элемент в контейнере */
        Iterator begin();
        /* Следующий после последнего элемента в контейнере */
        Iterator end();

        /* Поиск k-ой меньшей статистики начиная с индекса 0 */
        T findKthStats(int k) const;
        /* Поиск кол-ва элементов в дереве меньших чем upperBound */
        int countLess(T upperBound) const noexcept;

        /* Вставка ключа в дерево */
        void insert(T key) noexcept;

        ~CartesianTree();
    };

    template <typename T>
    typename CartesianTree<T>::Iterator CartesianTree<T>::begin()
    {
        return {top};
    }

    template <typename T>
    typename CartesianTree<T>::Iterator CartesianTree<T>::end()
    {
        return {nullptr};
    }

    template <typename T>
    T CartesianTree<T>::findKthStats(int k) const
    {
        std::shared_ptr<CartesianNode<T>> cur = top;
        while (cur != nullptr)
        {
            int sizeLeft = CartesianNode<T>::size(cur->left);

            if (sizeLeft == k)
                return cur->key_;

            cur = (sizeLeft > k) ? cur->left : cur->right;
            if (sizeLeft < k)
                k -= sizeLeft + 1;
        }

        throw std::invalid_argument("Element not found");
    }

    template <typename T>
    int CartesianTree<T>::countLess(T upperBound) const noexcept
    {
        if (top == nullptr)
            return 0;

        int prev_less = 0;
        std::shared_ptr<CartesianNode<T>> cur = top;
        while (cur != nullptr)
        {
            if (cur->key_ < upperBound)
            {
                prev_less += CartesianNode<T>::size(cur) - CartesianNode<T>::size(cur->right);
                cur = cur->right;
            }
            else
            {
                cur = cur->left;
            }
        }

        return prev_less;
    }

    template <typename T>
    void CartesianTree<T>::insert(T key) noexcept
    {
        top = CartesianNode<T>::insert(top, std::make_shared<CartesianNode<int>>(key));
    }

    template <typename T>
    class CartesianTree<T>::Iterator
    {
    private:
        std::shared_ptr<CartesianNode<T>> p_;

    public:
        Iterator(std::shared_ptr<CartesianNode<T>> p) : p_(p) {}

    public:
        bool operator!=(Iterator const &other) const;

        int operator*() const;

        Iterator &operator++();
    };

    template <typename T>
    bool CartesianTree<T>::Iterator::operator!=(Iterator const &other) const
    {
        if (p_ != nullptr && other.p_ != nullptr)
        {
            return p_->key_ != other.p_->key_;
        }
        else
        {
            return p_ != other.p_;
        }
    }

    template <typename T>
    int CartesianTree<T>::Iterator::operator*() const
    {
        if (p_ == nullptr)
        {
            throw new std::out_of_range("Dereference invalid iterator");
        }

        return this->p_->key_;
    }

    template <typename T>
    typename CartesianTree<T>::Iterator &CartesianTree<T>::Iterator::operator++()
    {
        if (p_ == nullptr)
        {
            throw new std::out_of_range("Increment invalid iterator");
        }
        if (p_->l != nullptr)
        {
            p_ = p_->l;
            return *this;
        }

        if (p_->r != nullptr)
        {
            p_ = p_->r;
            return *this;
        }

        while (true)
        {
            if (p_->root == nullptr)
            {
                p_ = nullptr;
                return *this;
            }

            auto old_p = p_;
            p_ = p_->root;

            if ((old_p != p_->r) && (p_->r != nullptr))
            {
                p_ = p_->r;
                return *this;
            }
        }
    }
}