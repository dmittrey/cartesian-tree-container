#pragma once

#include <random>

namespace Trees
{
    class CartesianTree
    {
    private:
        struct CartesianNode
        {
            /* Ключ */
            int key_;
            /* Приоритет балансирования */
            int prior_ = std::rand();
            /* Размер поддерева */
            int size_ = 1;

            /* Родительская вершина для поддержки прямого обхода дерева */
            CartesianNode *root = nullptr;

            CartesianNode *l = nullptr;
            CartesianNode *r = nullptr;

            CartesianNode(int key) : key_(key) {}

            /* Метод для получения размера поддерева */
            static int size(CartesianNode *node) noexcept;

            /* Метод для пересчёта полей вершины */
            void recalc() noexcept;

            /* Методы подвешивающие вершины */
            void hangL(CartesianNode *node) noexcept;
            void hangR(CartesianNode *node) noexcept;

            /*TODO NEED REFACTOR*/
            ~CartesianNode()
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
        };

    private:
        CartesianNode *top = nullptr;

    private: // Операции с деревом
        /* Метод для разделения дерева по ключу(ключ в правом поддереве) */
        static CartesianNode *merge(CartesianNode *lTree, CartesianNode *rTree);
        /* Метод для слияния двух деревьев */
        static std::pair<CartesianNode *, CartesianNode *> split(CartesianNode *tree, int index);
        /* Метод для вставки */
        static CartesianNode *insert(CartesianNode *tree, CartesianNode *node) noexcept;
        /* Метод для получения размера поддерева */
        static int size(CartesianNode *node) noexcept;

    public: // Итераторы
        class iterator
        {
        private:
            CartesianNode *p_;

        public:
            iterator(CartesianNode *p) : p_(p) {}

        public:
            bool operator!=(iterator const &other) const;

            int operator*() const;

            iterator &operator++();
        };

    public: // Итераторы
        /* Первый элемент в контейнере */
        iterator begin();
        /* Следующий после последнего элемента в контейнере */
        iterator end();

    public: // Селекторы
        /* Поиск k-ой меньшей статистики начиная с индекса 0 */
        int findKthStats(int k) const;
        /* Поиск кол-ва элементов в дереве меньших чем upperBound */
        int countLess(int upperBound) const noexcept;

    public: // Модификаторы
        void insert(int key) noexcept;

        ~CartesianTree()
        {
            if (top != nullptr)
            {
                while (top->l != nullptr)
                {
                    delete top->l;
                }

                while (top->r != nullptr)
                {
                    delete top->r;
                }
            }

            delete top;
        }
    };
}