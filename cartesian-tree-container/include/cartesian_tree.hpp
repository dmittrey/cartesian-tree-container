#pragma once

#include "cartesian_node.hpp"

namespace Trees
{
    template <typename T>
    class CartesianTree
    {
    private:
        /* Корень дерева */
        std::shared_ptr<CartesianNode<T>> top;

    protected:
        /* Метод для подвешивание детерминированной иерархии нод */
        CartesianTree(std::shared_ptr<CartesianNode<T>> top_node) : top(top_node) {}

    public:
        class Iterator;

        CartesianTree() = default;

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

        /* Поддержка наследования */
        virtual ~CartesianTree() {}
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
        Iterator(const Iterator &it) : p_(it.p_) {}

        bool operator!=(Iterator const &other) const;
        bool operator==(Iterator const &other) const;
        T &operator*() const;
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
    bool CartesianTree<T>::Iterator::operator==(Iterator const &other) const
    {
        return !(*this != other);
    }

    template <typename T>
    T &CartesianTree<T>::Iterator::operator*() const
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
        if (p_->left != nullptr)
        {
            p_ = p_->left;
            return *this;
        }

        if (p_->right != nullptr)
        {
            p_ = p_->right;
            return *this;
        }

        while (true)
        {
            auto shd_root = p_->root.lock();

            if (!shd_root)
            {
                p_ = nullptr;
                return *this;
            }

            auto old_p = p_;
            p_ = shd_root;

            if ((old_p != p_->right) && (p_->right != nullptr))
            {
                p_ = p_->right;
                return *this;
            }
        }
    }
}