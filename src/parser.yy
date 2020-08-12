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


%code requires {//add includes here
  #include <string>
  #include "UnaryOp.h"
  #include "BinaryOp.h"
  #include "Literal.h"
  class Driver;
}

%param { Driver& drv } //parameters to the parser

%code {
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

%token <AST::Value> LITERAL
%nterm <std::unique_ptr<AST::ExpNode>> expression

//Precedence
%left "+" "-";
%left "*" "/";
%precedence UMINUS



%%
%start unit;
unit: expression  { drv.result = std::move($1); };

expression: LITERAL {$$=std::make_unique<AST::Literal>($1);}
| expression "+" expression   { $$ =std::make_unique<AST::BinaryOp>(AST::BinaryOperator::Addition,std::move($1),std::move($3)); }
| expression "-" expression   { $$ =std::make_unique<AST::BinaryOp>(AST::BinaryOperator::Subtraction,std::move($1),std::move($3));}
| expression "*" expression   { $$ =std::make_unique<AST::BinaryOp>(AST::BinaryOperator::Multiplication,std::move($1),std::move($3)); }
| expression "/" expression   { $$ =std::make_unique<AST::BinaryOp>(AST::BinaryOperator::Division,std::move($1),std::move($3)); }
| "-" expression %prec UMINUS { $$= std::make_unique<AST::UnaryOp>(AST::UnaryOperator::Minus,std::move($2)); }
| "(" expression ")"   { $$ = std::move($2); }
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
