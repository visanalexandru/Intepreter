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
  #include "AST/Expression/VariableExp.h"
  #include "AST/Statement/VarDeclarationStmt.h"
  #include "AST/Statement/ExpressionStmt.h"
  #include "AST/Statement/IfElseStmt.h"
  #include "AST/Statement/WhileStmt.h"
  #include "VM/SymbolTable/Symbol.h"
  #include "AST/Statement/CompoundStmt.h"
  #include "AST/Expression/FunctionCallExp.h"
  #include "AST/Statement/FuncDeclarationStmt.h"
  #include "AST/Statement/ReturnStmt.h"
  class Driver;
}

%param { Driver& drv } //parameters to the parser

%code {
#include "Driver.h"
}

%token
  SUBTRACTION "-"
  ADDITION "+"
  MULTIPLICATION "*"
  MODULUS "%"
  DIVISION "/"
  LPAREN  "("
  RPAREN  ")"
  ASSIGNMENT "="
  EQUAL "=="
  NEQUAL "!="
  GREATER ">"
  NOT "!"
  GREATEREQ ">="
  LESS "<"
  LESSEQ "<="
  AND "&&"
  OR  "||"
  SEMICOLON ";"
  VAR "var"
  COMMA ","
  FUNC "func"
  LBLOCK "{"
  RBLOCK "}"
  RETURN "return"
  IF "if"
  ELSE "else"
  WHILE "while"
;

%token <VM::Value> LITERAL
%token <VM::Symbol> IDENTIFIER
%nterm <std::unique_ptr<AST::ExpNode>> expression

%nterm <std::unique_ptr<AST::VarDeclarationStmt>> var_declaration_stmt
%nterm <std::unique_ptr<AST::ExpressionStmt>> expression_stmt
%nterm <std::unique_ptr<AST::IfElseStmt>> ifelse_stmt
%nterm <std::unique_ptr<AST::WhileStmt>> while_stmt
%nterm <std::unique_ptr<AST::FuncDeclarationStmt>> func_decl_stmt
%nterm <std::unique_ptr<AST::ReturnStmt>> return_stmt;
%nterm <std::unique_ptr<AST::StmtNode>> statement;
%nterm <std::unique_ptr<AST::CompoundStmt>> compound_stmt;
%nterm <std::vector<std::unique_ptr<AST::StmtNode>>> block //a list of statements

%nterm <std::vector<std::unique_ptr<AST::ExpNode>>> expression_list;//1 or more comma separated expressions
%nterm <std::vector<std::unique_ptr<AST::ExpNode>>> argument_list;//0 or more comma separated expressions between parentheses
%nterm <std::vector<VM::Symbol>> identifier_list;//1 or more comma separated identifiers
%nterm <std::vector<VM::Symbol>> argument_identifier_list;//0 or more comma separated identifiers between parentheses
//Precedence
%right "="
%left "||"
%left "&&"
%left "==" "!="
%left ">" "<" ">=" "<="
%left "+" "-";
%left "*" "/" "%"
%right "!"
%left  "("



%%
%start unit;
unit:block{ drv.result = std::move($1); };


expression: LITERAL {$$=std::make_unique<AST::LiteralExp>(@1,$1);}
| expression "+" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::Add,std::move($1),std::move($3)); }
| expression "-" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::Subtract,std::move($1),std::move($3));}
| expression "*" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::Multiply,std::move($1),std::move($3)); }
| expression "/" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::Divide,std::move($1),std::move($3)); }
| expression "%" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::Modulus,std::move($1),std::move($3)); }
| expression "==" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::Equal,std::move($1),std::move($3)); }
| expression "!=" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::NEqual,std::move($1),std::move($3)); }
| expression ">" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::Greater,std::move($1),std::move($3)); }
| expression "<" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::Less,std::move($1),std::move($3)); }
| expression ">=" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::GreaterEq,std::move($1),std::move($3)); }
| expression "<=" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::LessEq,std::move($1),std::move($3)); }
| expression "||" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::Or,std::move($1),std::move($3)); }
| expression "&&" expression   { $$ =std::make_unique<AST::BinaryOpExp>(@2,AST::BinaryOperator::And,std::move($1),std::move($3)); }
| "-" expression %prec "!"    { $$= std::make_unique<AST::UnaryOpExp>(@1,AST::UnaryOperator::Minus,std::move($2)); }
| "!" expression              { $$= std::make_unique<AST::UnaryOpExp>(@1,AST::UnaryOperator::Not,std::move($2)); }
| "(" expression ")"          { $$ = std::move($2); }
| IDENTIFIER "=" expression   { $$=std::make_unique<AST::VariableExp>(@2,std::move($1),std::move($3));}
| IDENTIFIER                  { $$=std::make_unique<AST::VariableExp>(@1,std::move($1));}
| expression argument_list  {$$=std::make_unique<AST::FunctionCallExp>(@1,std::move($1),std::move($2));}

;

expression_list: expression {$$.push_back(std::move($1));}
|expression_list "," expression {$1.push_back(std::move($3));$$=std::move($1);}
;

argument_list: "(" ")"      {}
|"(" expression_list ")"    {$$=std::move($2);}
;

identifier_list: IDENTIFIER {$$.push_back(std::move($1));}
|identifier_list "," IDENTIFIER {$1.push_back(std::move($3));$$=std::move($1);}

argument_identifier_list: "(" ")" {}
| "(" identifier_list ")" {$$=std::move($2);}




block:
%empty          {}
|block statement{ $1.push_back(std::move($2));$$=std::move($1);}
;

compound_stmt: "{" block "}" {$$=std::make_unique<AST::CompoundStmt>(@1,std::move($2));}

statement: var_declaration_stmt {$$=std::move($1);}
|expression_stmt {$$=std::move($1);}
|ifelse_stmt     {$$=std::move($1);}
|while_stmt      {$$=std::move($1);}
|func_decl_stmt  {$$=std::move($1);}
|return_stmt     {$$=std::move($1);}
|compound_stmt   {$$=std::move($1);}

var_declaration_stmt: "var" IDENTIFIER "=" expression ";" {$$=std::make_unique<AST::VarDeclarationStmt>(@1,std::move($2),std::move($4));}
| "var" IDENTIFIER ";"                                    {$$=std::make_unique<AST::VarDeclarationStmt>(@1,std::move($2));}
;

expression_stmt: expression ";" {$$=std::make_unique<AST::ExpressionStmt>(@1,std::move($1));}
;


ifelse_stmt: "if" "(" expression ")" compound_stmt{$$=std::make_unique<AST::IfElseStmt>(@1,std::move($3),std::move($5));}
|"if" "(" expression ")" compound_stmt "else" compound_stmt {$$=std::make_unique<AST::IfElseStmt>(@1,std::move($3),std::move($5),std::move($7));}

while_stmt: "while" "(" expression ")" compound_stmt{$$=std::make_unique<AST::WhileStmt>(@1,std::move($3),std::move($5));}

func_decl_stmt: "func" IDENTIFIER argument_identifier_list "{" block "}" {$$=std::make_unique<AST::FuncDeclarationStmt>(@1,std::move($2),std::move($3),std::move($5));}

return_stmt: "return" expression ";" {$$=std::make_unique<AST::ReturnStmt>(@1,std::move($2));}
| "return"  ";" {$$=std::make_unique<AST::ReturnStmt>(@1);}
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  drv.errors.push_back(Error(m,l));
}
