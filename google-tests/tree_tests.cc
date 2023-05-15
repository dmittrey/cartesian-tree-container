#include <gtest/gtest.h>

#include "cartesian_tree.hpp"

using Trees::CartesianTree;

TEST(CartesianTreeTests, OpsForOneElement)
{
    Trees::CartesianTree<int> tree;

    tree.insert(12);

    EXPECT_EQ(tree.findKthStats(0), 12);
    EXPECT_EQ(tree.countLess(13), 1);
}

TEST(CartesianTreeTests, OpsForEmptyStructure)
{
    Trees::CartesianTree<int> tree;

    EXPECT_THROW(tree.findKthStats(1), std::invalid_argument);
    EXPECT_EQ(tree.countLess(10), 0);
}

TEST(CartesianTreeTests, OpsWithPositiveNumbers)
{
    Trees::CartesianTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    EXPECT_EQ(tree.findKthStats(1), 10);
    EXPECT_EQ(tree.countLess(5), 0);
    EXPECT_EQ(tree.countLess(10), 1);
}

TEST(CartesianTreeTests, OpsWithNegativeNumbers)
{
    Trees::CartesianTree<int> tree;

    tree.insert(-4);
    tree.insert(-8);
    tree.insert(-6);

    EXPECT_EQ(tree.findKthStats(1), -6);
    EXPECT_EQ(tree.countLess(-6), 1);
    EXPECT_EQ(tree.countLess(-4), 2);
}