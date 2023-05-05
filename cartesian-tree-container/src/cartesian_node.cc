#include "../include/cartesian_tree.hpp"

namespace Trees
{
    void CartesianTree::CartesianNode::recalc() noexcept
    {
        size_ = 1;

        if (l != nullptr)
            size_ += l->size_;
        if (r != nullptr)
            size_ += r->size_;
    }

    void CartesianTree::CartesianNode::hangL(CartesianNode *node) noexcept
    {
        l = node;
        if (node != nullptr)
        {
            node->root = this;
        }
    }

    void CartesianTree::CartesianNode::hangR(CartesianNode *node) noexcept
    {
        r = node;
        if (node != nullptr)
        {
            node->root = this;
        }
    }
}