#include "cartesian_tree.hpp"

namespace Trees
{
    CartesianNode *CartesianTree::merge(CartesianNode *lTree, CartesianNode *rTree)
    {
        if (lTree == nullptr)
            return rTree;
        if (rTree == nullptr)
            return lTree;

        if (lTree->prior_ > rTree->prior_)
        {
            lTree->rNode = merge(lTree->rNode, rTree);
            return lTree;
        }
        else
        {
            rTree->lNode = merge(lTree, rTree->lNode);
            return rTree;
        }
    }

    CartesianTree::split_pair CartesianTree::split(CartesianNode *tree, int index)
    {
        if (tree == nullptr)
            return {0, 0};

        if (index >= tree->key_) //  Ключ в правом поддереве
        {
            CartesianTree::split_pair q = split(tree->rNode, index);
            tree->rNode = q.first;
            return {tree, q.second};
        }
        else
        {
            CartesianTree::split_pair q = split(tree->lNode, index);
            tree->lNode = q.second;
            return {q.first, tree};
        }
    }

    void CartesianTree::insert(int key)
    {
    }

    CartesianTree::iterator CartesianTree::findKthStats() const
    {
    }

    int CartesianTree::countLess(int upperBound) const
    {
    }
}