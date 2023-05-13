#include <gtest/gtest.h>
#include "include/cartesian_tree.hpp"

using Trees::CartesianNode;
using Trees::CartesianTree;

TEST(CartesianTreeTests, Test1)
{
    Trees::CartesianTree<int> tree;

    tree.insert(12);

    EXPECT_EQ(tree.findKthStats(1), 12);
    EXPECT_EQ(tree.countLess(13), 1);
}

TEST(CartesianTreeTests, Test2)
{
    Trees::CartesianTree<int> tree;

    EXPECT_EQ(tree.findKthStats(2), 0); // Exception
    EXPECT_EQ(tree.countLess(10), 0);
}

TEST(CartesianTreeTests, Test3)
{
    Trees::CartesianTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    EXPECT_EQ(tree.findKthStats(2), 10);
    EXPECT_EQ(tree.countLess(5), 0);
    EXPECT_EQ(tree.countLess(10), 1);
}

TEST(CartesianTreeTests, Test4)
{
    Trees::CartesianTree<int> tree;

    tree.insert(-4);
    tree.insert(-8);
    tree.insert(-6);

    EXPECT_EQ(tree.findKthStats(2), -6);
    EXPECT_EQ(tree.countLess(-6), 1);
    EXPECT_EQ(tree.countLess(-4), 2);
}