#include "driver.hpp"

int main()
{
    Trees::CartesianTree *tree = new Trees::CartesianTree();
    FlexLexer *lexer = new yyFlexLexer;
    yy::Driver driver(tree, lexer);
    driver.parse();
    delete tree;
    delete lexer;
}