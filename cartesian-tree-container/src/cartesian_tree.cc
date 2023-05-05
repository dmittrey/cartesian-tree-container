#include "../include/cartesian_tree.hpp"

namespace Trees
{
    CartesianTree::CartesianNode *CartesianTree::merge(CartesianNode *lTree, CartesianNode *rTree)
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

    std::pair<CartesianTree::CartesianNode *, CartesianTree::CartesianNode *> CartesianTree::split(CartesianNode *tree, int index)
    {
        if (tree == nullptr)
            return {nullptr, nullptr};

        if (index >= tree->key_) //  Ключ в правом поддереве
        {
            auto [l, r] = split(tree->r, index);
            tree->hangR(l);
            tree->recalc();
            return {tree, r};
        }
        else
        {
            auto [l, r] = split(tree->l, index);
            tree->hangL(r);
            tree->recalc();
            return {l, tree};
        }
    }

    CartesianTree::CartesianNode *CartesianTree::insert(CartesianNode *tree, CartesianNode *node) noexcept
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
            if (node->key_ >= tree->key_)
            {
                tree->hangR(insert(tree->r, node));
            }
            else
            {
                tree->hangL(insert(tree->l, node));
            }
            tree->recalc();
            return tree;
        }
    }

    CartesianTree::iterator CartesianTree::begin()
    {
        return {top};
    }

    CartesianTree::iterator CartesianTree::end()
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
        top = insert(top, new CartesianNode(key));
    }
}