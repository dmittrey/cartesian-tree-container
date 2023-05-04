#pragma once

#include <fstream>
#include <iostream>
#include <numeric>

#include <iostream>
#include <vector>

#include <FlexLexer.h>
#include "parser.tab.hh"

#include "include/cartesian_tree.hpp"

namespace yy
{
    class Driver
    {
        Trees::CartesianTree *tree_;
        FlexLexer *plex_;

    public:
        Driver(Trees::CartesianTree *tree, FlexLexer *plex) : tree_(tree), plex_(plex) {}

        parser::token_type yylex(parser::semantic_type *yylval)
        {
            parser::token_type tt = static_cast<parser::token_type>(plex_->yylex());

            switch (tt)
            {
            case yy::parser::token_type::INT:
                yylval->as<int>() = std::stoi(plex_->YYText());
                break;
            default:
                break;
            }

            return tt;
        }

        bool parse()
        {
            parser parser(this);
            while (true)
            {
                parser.parse();
            }
        }

        void insert(int key)
        {
            tree_->insert(key);
        }

        void find_kth(int index)
        {
            std::cout << tree_->findKthStats(index - 1) << " ";
        }

        void count_less(int upperBound)
        {
            std::cout << tree_->countLess(upperBound) << " ";
        }
    };
}