#include "../include/cartesian_node.hpp"

namespace Trees
{
    int CartesianNode::size(CartesianNode *node) noexcept
    {
        return (node == nullptr) ? 0 : node->size_;
    }

    void CartesianNode::recalc() noexcept
    {
        size_ = 1;

        if (l != nullptr)
            size_ += l->size_;
        if (r != nullptr)
            size_ += r->size_;
    }

    void CartesianNode::hangL(CartesianNode *node) noexcept
    {
        l = node;
        if (node != nullptr)
        {
            node->root = this;
        }
    }

    void CartesianNode::hangR(CartesianNode *node) noexcept
    {
        r = node;
        if (node != nullptr)
        {
            node->root = this;
        }
    }

    CartesianNode *CartesianNode::merge(CartesianNode *lTree, CartesianNode *rTree)
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

    std::pair<CartesianNode *, CartesianNode *> CartesianNode::split(CartesianNode *tree, int index)
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

    CartesianNode *CartesianNode::insert(CartesianNode *tree, CartesianNode *node) noexcept
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

    /*TODO NEED REFACTOR*/
    CartesianNode::~CartesianNode()
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
}