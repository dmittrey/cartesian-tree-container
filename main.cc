#include "driver.hpp"

int main()
{
    Trees::CartesianTree<int> *tree = new Trees::CartesianTree<int>();
    FlexLexer *lexer = new yyFlexLexer;
    yy::Driver driver(tree, lexer);
    driver.parse();
    delete tree;
    delete lexer;
}