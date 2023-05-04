%language "c++"

%defines
%define api.value.type variant
%param {yy::Driver* driver}

%code requires
{

// forward decl of argument to parser
namespace yy { class Driver; }

}

%code
{

#include "driver.hpp"

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         Driver* driver);
}

}

%token INSERT
%token FIND_KTH
%token COUNT_LESS

%token <int> INT

%start query_list

%%

query_list: insert_query                    {  }
  | query_list insert_query                 {  }
  | find_kth_query                          {  }
  | query_list find_kth_query               {  }
  | count_less_query                        {  }
  | query_list count_less_query             {  }
;

insert_query: INSERT INT                    { driver->insert($2); }
;
find_kth_query: FIND_KTH INT                { driver->find_kth($2); }
;
count_less_query: COUNT_LESS INT            { driver->count_less($2); }
;

%%

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         Driver* driver)
{
  return driver->yylex(yylval);
}

void parser::error(const std::string&){}
}