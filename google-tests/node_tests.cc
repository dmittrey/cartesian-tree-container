#include <gtest/gtest.h>
#include "include/cartesian_node.hpp"

using Trees::CartesianNode;

TEST(CartesianNodeTests, SizeFromNullptr)
{
    auto shd_node = std::shared_ptr<CartesianNode<int>>(nullptr);
    EXPECT_EQ(CartesianNode<int>::size(shd_node), 0);
}

TEST(CartesianNodeTests, SizeFromSingleNode)
{
    auto shd_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));
    EXPECT_EQ(CartesianNode<int>::size(shd_node), 1);
}

TEST(CartesianNodeTests, RecalcWithoutChildren)
{
    auto shd_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));

    shd_node->recalc();

    EXPECT_EQ(CartesianNode<int>::size(shd_node), 1);
}

TEST(CartesianNodeTests, RecalcWithOneChild)
{
    auto shd_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));
    auto shd_child_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));
    shd_child_node->size_ = 5;
    shd_node->hangR(shd_child_node);

    shd_node->recalc();
    
    EXPECT_EQ(CartesianNode<int>::size(shd_node), 6);
}

TEST(CartesianNodeTests, RecalcWithTwoChildren)
{
    auto shd_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));
    auto shd_child_r_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));
    auto shd_child_l_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));
    shd_child_r_node->size_ = 5;
    shd_child_l_node->size_ = 10;
    shd_node->hangL(shd_child_l_node);
    shd_node->hangR(shd_child_r_node);

    shd_node->recalc();
    
    EXPECT_EQ(CartesianNode<int>::size(shd_node), 16);
}

TEST(CartesianNodeTests, HangRNullptr)
{
    auto shd_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));
    auto shd_r_child_node = std::shared_ptr<CartesianNode<int>>(nullptr);

    shd_node->hangR(shd_r_child_node);
    
    EXPECT_EQ(shd_node->right, nullptr);
}

TEST(CartesianNodeTests, HangRExistNode)
{
    auto shd_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));
    auto shd_r_child_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));

    shd_node->hangR(shd_r_child_node);
    
    EXPECT_EQ(shd_r_child_node->key_, shd_node->right->key_);
    EXPECT_EQ(shd_r_child_node->prior_, shd_node->right->prior_);
    EXPECT_EQ(shd_r_child_node->size_, shd_node->right->size_);
    auto shd_r_child_node_root = shd_r_child_node->root.lock();
    EXPECT_EQ(shd_r_child_node_root, shd_node);
}

TEST(CartesianNodeTests, HangLNullptr)
{
    auto shd_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));
    auto shd_l_child_node = std::shared_ptr<CartesianNode<int>>(nullptr);

    shd_node->hangL(shd_l_child_node);
    
    EXPECT_EQ(shd_node->left, nullptr);
}

TEST(CartesianNodeTests, HangLExistNode)
{
    auto shd_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));
    auto shd_l_child_node = std::shared_ptr<CartesianNode<int>>(new CartesianNode<int>(5));

    shd_node->hangR(shd_l_child_node);
    
    EXPECT_EQ(shd_l_child_node->key_, shd_node->right->key_);
    EXPECT_EQ(shd_l_child_node->prior_, shd_node->right->prior_);
    EXPECT_EQ(shd_l_child_node->size_, shd_node->right->size_);
    auto shd_l_child_node_root = shd_l_child_node->root.lock();
    EXPECT_EQ(shd_l_child_node_root, shd_node);
}

TEST(CartesianNodeTests, Merge)
{

}

TEST(CartesianNodeTests, Split)
{

}

TEST(CartesianNodeTests, Insert)
{

}