#include "../include/cartesian_tree.hpp"

namespace Trees
{
    bool CartesianTree::Iterator::operator!=(Iterator const &other) const
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

    int CartesianTree::Iterator::operator*() const
    {
        if (p_ == nullptr)
        {
            throw new std::out_of_range("Dereference invalid iterator");
        }

        return this->p_->key_;
    }

    CartesianTree::Iterator &CartesianTree::Iterator::operator++()
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