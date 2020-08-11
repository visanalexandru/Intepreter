%skeleton "lalr1.cc" // C++ skeleton 
%require "3.7.1"

%defines //create the header file

%define api.token.raw //avoid conversions fron characters to tokens

%define api.token.constructor //needed by variant value types

%define api.value.type variant //enable variant value types

%define parse.assert //check proper construction and destruction of variants

%locations //enable locations

%define parse.error detailed //detailed syntax errors

%define parse.lac full //improve syntax error handling


%code requires {
  class Driver;
}

%param { Driver& drv } //parameters to the parser

%code { //add includes here
# include <string>
#include "Driver.h"
}

%token
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
;

%token <int> NUMBER 
%nterm <int> expression

//Precedence
%left "+" "-";
%left "*" "/";



%%
%start unit;
unit: expression  { drv.result = $1; };

expression: NUMBER
| expression "+" expression   { $$ = $1 + $3; }
| expression "-" expression   { $$ = $1 - $3; }
| expression "*" expression   { $$ = $1 * $3; }
| expression "/" expression   { $$ = $1 / $3; }
| "(" expression ")"   { $$ = $2; }
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
