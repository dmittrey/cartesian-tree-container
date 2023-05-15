#include <gtest/gtest.h>

#include <set>

#include "cartesian_tree.hpp"

using Trees::CartesianNode;
using Trees::CartesianTree;

struct TestCartesianTree : public CartesianTree<int>
{
    TestCartesianTree() : CartesianTree() {}
    TestCartesianTree(std::shared_ptr<CartesianNode<int>> top) : CartesianTree(top) {}
};

/* Итератор заявляет прямой проход дерева => следует проверить */
TEST(CartesianTreeIteratorTests, ForwardInLeft)
{
    auto top_node = std::make_shared<CartesianNode<int>>(5);
    auto left_t1_node = std::make_shared<CartesianNode<int>>(4);
    auto left_t2_node = std::make_shared<CartesianNode<int>>(3);
    top_node->hangL(left_t1_node);
    left_t1_node->hangL(left_t2_node);
    TestCartesianTree tree(top_node);

    auto it = tree.begin();
    EXPECT_EQ(*it, 5);
    ++it;
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, tree.end());
}

TEST(CartesianTreeIteratorTests, ForwardInRight)
{
    auto top_node = std::make_shared<CartesianNode<int>>(5);
    auto right_t1_node = std::make_shared<CartesianNode<int>>(6);
    auto right_t2_node = std::make_shared<CartesianNode<int>>(7);
    top_node->hangR(right_t1_node);
    right_t1_node->hangL(right_t2_node);
    TestCartesianTree tree(top_node);

    auto it = tree.begin();
    EXPECT_EQ(*it, 5);
    ++it;
    EXPECT_EQ(*it, 6);
    ++it;
    EXPECT_EQ(*it, 7);
    ++it;
    EXPECT_EQ(it, tree.end());
}

TEST(CartesianTreeIteratorTests, UpInAnotherTreeFromTearOne)
{
    auto top_node = std::make_shared<CartesianNode<int>>(5);
    auto r_node = std::make_shared<CartesianNode<int>>(6);
    auto l_node = std::make_shared<CartesianNode<int>>(4);
    top_node->hangL(l_node);
    top_node->hangR(r_node);
    TestCartesianTree tree(top_node);

    auto it = tree.begin();
    EXPECT_EQ(*it, 5);
    ++it;
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_EQ(*it, 6);
    ++it;
    EXPECT_EQ(it, tree.end());
}

TEST(CartesianTreeIteratorTests, UpInAnotherTreeFromTearTwo)
{
    auto top_node = std::make_shared<CartesianNode<int>>(5);
    auto r_node = std::make_shared<CartesianNode<int>>(6);
    auto l_t1_node = std::make_shared<CartesianNode<int>>(4);
    auto l_t2_node = std::make_shared<CartesianNode<int>>(3);
    top_node->hangL(l_t1_node);
    top_node->hangR(r_node);
    l_t1_node->hangL(l_t2_node);
    TestCartesianTree tree(top_node);

    auto it = tree.begin();
    EXPECT_EQ(*it, 5);
    ++it;
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 6);
    ++it;
    EXPECT_EQ(it, tree.end());
}

/* Проверка на то, что итератор точно обойдет все вершины */
TEST(CartesianTreeIteratorTests, IterateOverAll)
{
    TestCartesianTree tree;
    std::set<int> keys = {1, 2, 3, 5, 10, 100, -5, -9, 1000, 2500};
    for (int i : keys)
        tree.insert(i);

    for (auto it = tree.begin(); it != tree.end(); ++it)
        EXPECT_EQ(keys.erase(*it), 1);

    EXPECT_EQ(keys.size(), 0);
}