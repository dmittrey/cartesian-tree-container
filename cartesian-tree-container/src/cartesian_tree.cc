#include "../include/cartesian_tree.hpp"

namespace Trees
{
    CartesianTree::Iterator CartesianTree::begin()
    {
        return {top};
    }

    CartesianTree::Iterator CartesianTree::end()
    {
        return {nullptr};
    }

    int CartesianTree::findKthStats(int k) const
    {
        CartesianNode *cur = top;
        while (cur != nullptr)
        {
            int sizeLeft = CartesianNode::size(cur->l);

            if (sizeLeft == k)
                return cur->key_;

            cur = (sizeLeft > k) ? cur->l : cur->r;
            if (sizeLeft < k)
                k -= sizeLeft + 1;
        }

        throw std::invalid_argument("Element not found");
    }

    int CartesianTree::countLess(int upperBound) const noexcept
    {
        if (top == nullptr)
            return 0;

        CartesianNode *cur = top;
        auto prev_less = 0;
        while (cur != nullptr)
        {
            if (cur->key_ < upperBound)
            {
                prev_less += CartesianNode::size(cur) - CartesianNode::size(cur->r);
                cur = cur->r;
            }
            else
            {
                cur = cur->l;
            }
        }

        return prev_less;
    }

    void CartesianTree::insert(int key) noexcept
    {
        top = CartesianNode::insert(top, new CartesianNode(key));
    }

    CartesianTree::~CartesianTree()
    {
        if (top != nullptr)
        {
            while (top->l != nullptr)
            {
                delete top->l;
            }

            while (top->r != nullptr)
            {
                delete top->r;
            }
        }

        delete top;
    }
}