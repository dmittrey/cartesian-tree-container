#pragma once

#include <random>

namespace Trees
{
    class CartesianNode
    {
    private:
        int key_;
        int prior_ = std::rand();
        int size_ = 0;

    public:
        CartesianNode *lNode = nullptr;
        CartesianNode *rNode = nullptr;

    public:
        CartesianNode(int key) : key_(key) {}

    public:
        int size() const;

    public:
        void recalc() const;
    };
}