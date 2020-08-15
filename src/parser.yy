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
  #include "AST/Expression/UnaryOpExp.h"
  #include "AST/Expression/BinaryOpExp.h"
  #include "AST/Expression/LiteralExp.h"
  #include "AST/Expression/AssignmentExp.h"
  #include "AST/Expression/VariableExp.h"
  #include "AST/Expression/FuncCallExp.h"
  #include "AST/Statement/DeclarationStmt.h"
  #include "AST/Statement/ExpressionStmt.h"
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
  EQUALS "="
  SEMICOLON ";"
  VAR "var"
  COMMA ","
;

%token <AST::Value> LITERAL
%token <std::string> IDENTIFIER
%nterm <std::unique_ptr<AST::ExpNode>> expression
%nterm <std::unique_ptr<AST::StmtNode>> statement
%nterm <std::unique_ptr<AST::DeclarationStmt>> declaration_stmt
%nterm <std::unique_ptr<AST::ExpressionStmt>> expression_stmt
%nterm <std::vector<std::unique_ptr<AST::StmtNode>>> statement_list
%nterm <std::vector<std::unique_ptr<AST::ExpNode>>>  expression_list//1 or more comma-separated expressions
%nterm <std::unique_ptr<AST::FuncCallExp>> function_call;

//Precedence
%right "="
%left "+" "-";
%left "*" "/";
%precedence UMINUS



%%
%start unit;
unit:statement_list{ drv.result = std::move($1); };


expression: LITERAL {$$=std::make_unique<AST::LiteralExp>($1);}
| expression "+" expression   { $$ =std::make_unique<AST::BinaryOpExp>(AST::BinaryOperator::Addition,std::move($1),std::move($3)); }
| expression "-" expression   { $$ =std::make_unique<AST::BinaryOpExp>(AST::BinaryOperator::Subtraction,std::move($1),std::move($3));}
| expression "*" expression   { $$ =std::make_unique<AST::BinaryOpExp>(AST::BinaryOperator::Multiplication,std::move($1),std::move($3)); }
| expression "/" expression   { $$ =std::make_unique<AST::BinaryOpExp>(AST::BinaryOperator::Division,std::move($1),std::move($3)); }
| "-" expression %prec UMINUS { $$= std::make_unique<AST::UnaryOpExp>(AST::UnaryOperator::Minus,std::move($2)); }
| "(" expression ")"          { $$ = std::move($2); }
| IDENTIFIER "=" expression   { $$=std::make_unique<AST::AssignmentExp>(std::move($1),std::move($3));}
| IDENTIFIER                  { $$=std::make_unique<AST::VariableExp>(std::move($1));}
| function_call               { $$=std::move($1);}
;

expression_list: expression {$$=std::vector<std::unique_ptr<AST::ExpNode>>();$$.push_back(std::move($1));}
|expression_list "," expression {$1.push_back(std::move($3));$$=std::move($1);}
;

function_call: IDENTIFIER "(" expression_list ")" {$$=std::make_unique<AST::FuncCallExp>(std::move($1),std::move($3));}
|IDENTIFIER "(" ")"                               {$$=std::make_unique<AST::FuncCallExp>(std::move($1),std::vector<std::unique_ptr<AST::ExpNode>>());}
;

statement_list:
%empty                    {$$=std::vector<std::unique_ptr<AST::StmtNode>>();}
|statement_list statement { $1.push_back(std::move($2));$$=std::move($1);}
;

statement:declaration_stmt {$$=std::move($1);}
|         expression_stmt  {$$=std::move($1);}
;

declaration_stmt: "var" IDENTIFIER "=" expression ";" {$$=std::make_unique<AST::DeclarationStmt>(std::move($2),std::move($4));}
| "var" IDENTIFIER ";"                                {$$=std::make_unique<AST::DeclarationStmt>(std::move($2));}
;

expression_stmt: expression ";" {$$=std::make_unique<AST::ExpressionStmt>(std::move($1));}
;
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
