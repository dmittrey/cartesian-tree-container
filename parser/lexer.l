%option c++ noyywrap

%{

#include "parser.tab.hh"

%}

WS      [ \t\n\v]+
DIGIT   [0-9]
DIGIT1  [1-9]

%%

{WS}                                        /* skip blanks and tabs */

k                                           return yy::parser::token_type::INSERT;
m                                           return yy::parser::token_type::FIND_KTH;
n                                           return yy::parser::token_type::COUNT_LESS;
q                                           return yy::parser::token_type::EXIT;

(-?){DIGIT1}{DIGIT}*                        return yy::parser::token_type::INT;

.			                                /* skip other */

%%