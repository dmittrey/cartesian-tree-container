#include <iostream>

#include "driver.hpp"
#include "cartesian_tree.hpp"

int main()
{
    Trees::CartesianTree<int> *tree = new Trees::CartesianTree<int>();
    FlexLexer *lexer = new yyFlexLexer;
    yy::Driver driver(tree, lexer);
    driver.parse();
    delete tree;
    delete lexer;
}