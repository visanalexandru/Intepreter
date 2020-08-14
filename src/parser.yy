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
  #include "UnaryOpExp.h"
  #include "BinaryOpExp.h"
  #include "LiteralExp.h"
  #include "AssignmentExp.h"
  #include "DeclarationStmt.h"
  #include "VariableExp.h"
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
  VAR "var";
;

%token <AST::Value> LITERAL
%token <std::string> IDENTIFIER
%nterm <std::unique_ptr<AST::ExpNode>> expression
%nterm <std::unique_ptr<AST::StmtNode>> statement
%nterm <std::unique_ptr<AST::StmtNode>> declaration_stmt
%nterm <std::vector<std::unique_ptr<AST::StmtNode>>> statement_list

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
| IDENTIFIER "=" expression   { $$=std::make_unique<AST::AssignmentExp>($1,std::move($3));}
| IDENTIFIER                  { $$=std::make_unique<AST::VariableExp>($1);}
;


statement_list:
%empty                    {$$=std::vector<std::unique_ptr<AST::StmtNode>>();}
|statement_list statement { $1.push_back(std::move($2));$$=std::move($1);}
;

statement:declaration_stmt {$$=std::move($1);}

declaration_stmt: "var" IDENTIFIER "=" expression ";" {$$=std::make_unique<AST::DeclarationStmt>($2,std::move($4));}
| "var" IDENTIFIER ";"                                {$$=std::make_unique<AST::DeclarationStmt>($2);}

%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
