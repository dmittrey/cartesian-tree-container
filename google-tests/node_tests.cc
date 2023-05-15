#include <gtest/gtest.h>

#include "cartesian_node.hpp"

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

TEST(CartesianNodeTests, MergeBothNullptr)
{
    auto l_node = std::shared_ptr<CartesianNode<int>>(nullptr);
    auto r_node = std::shared_ptr<CartesianNode<int>>(nullptr);

    auto top = CartesianNode<int>::merge(l_node, r_node);

    EXPECT_EQ(nullptr, top);
}

TEST(CartesianNodeTests, MergeWithLeftNullptr)
{
    auto l_node = std::shared_ptr<CartesianNode<int>>(nullptr);
    auto r_node = std::make_shared<CartesianNode<int>>(5);

    auto top = CartesianNode<int>::merge(l_node, r_node);

    EXPECT_EQ(top->key_, r_node->key_);
}

TEST(CartesianNodeTests, MergeWithRightNullptr)
{
    auto l_node = std::make_shared<CartesianNode<int>>(5);
    auto r_node = std::shared_ptr<CartesianNode<int>>(nullptr);

    auto top = CartesianNode<int>::merge(l_node, r_node);

    EXPECT_EQ(top->key_, l_node->key_);
}

TEST(CartesianNodeTests, MergeWithLeftHigher)
{
    auto l_t1_node = std::make_shared<CartesianNode<int>>(3);
    l_t1_node->prior_ = 6000;
    auto r_t1_node = std::make_shared<CartesianNode<int>>(6);
    r_t1_node->prior_ = 5000;
    auto l_t2_node = std::make_shared<CartesianNode<int>>(2);
    auto r_t2_node = std::make_shared<CartesianNode<int>>(4);
    l_t1_node->hangL(l_t2_node);
    l_t1_node->hangR(r_t2_node);

    auto top = CartesianNode<int>::merge(l_t1_node, r_t1_node);

    EXPECT_EQ(top->key_, l_t1_node->key_);
}

TEST(CartesianNodeTests, MergeWithRightHigher)
{
    auto l_t1_node = std::make_shared<CartesianNode<int>>(3);
    l_t1_node->prior_ = 5000;
    auto r_t1_node = std::make_shared<CartesianNode<int>>(6);
    r_t1_node->prior_ = 6000;
    auto l_t2_node = std::make_shared<CartesianNode<int>>(2);
    auto r_t2_node = std::make_shared<CartesianNode<int>>(4);
    r_t1_node->hangL(l_t2_node);
    r_t1_node->hangR(r_t2_node);

    auto top = CartesianNode<int>::merge(l_t1_node, r_t1_node);

    EXPECT_EQ(top->key_, r_t1_node->key_);
}

/* Разделение по самому правому ключу
    Ключ должен остаться в левом поддереве 
*/
TEST(CartesianNodeTests, SplitByMostRightKey)
{
    auto top_node = std::make_shared<CartesianNode<int>>(5);
    auto r_node = std::make_shared<CartesianNode<int>>(6);
    auto l_node = std::make_shared<CartesianNode<int>>(4);
    top_node->hangL(l_node);
    top_node->hangR(r_node);

    auto [l, r] = CartesianNode<int>::split(top_node, 6);

    EXPECT_EQ(nullptr, r);
    EXPECT_EQ(top_node->key_, l->key_);
}

/* Разделение по самому левому ключу
    Ключ должен остаться в левом поддереве 
*/
TEST(CartesianNodeTests, SplitByMostLeftKey)
{
    auto top_node = std::make_shared<CartesianNode<int>>(5);
    auto r_node = std::make_shared<CartesianNode<int>>(6);
    auto l_node = std::make_shared<CartesianNode<int>>(4);
    top_node->hangL(l_node);
    top_node->hangR(r_node);

    auto [l, r] = CartesianNode<int>::split(top_node, 4);

    EXPECT_EQ(top_node->key_, r->key_);
    EXPECT_EQ(l_node->key_, l->key_);
}

/* Разделение по корню
    Корень + левое поддерево слева, остальное справа
*/

TEST(CartesianNodeTests, SplitByTop)
{
    auto top_node = std::make_shared<CartesianNode<int>>(5);
    auto r_node = std::make_shared<CartesianNode<int>>(6);
    auto l_node = std::make_shared<CartesianNode<int>>(4);
    top_node->hangL(l_node);
    top_node->hangR(r_node);

    auto [l, r] = CartesianNode<int>::split(top_node, 5);

    EXPECT_EQ(top_node->key_, l->key_);
    EXPECT_EQ(r_node->key_, r->key_);
}