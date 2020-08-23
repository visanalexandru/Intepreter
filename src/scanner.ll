%{
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <cstring> // strerror
# include <string>
# include "Driver.h"
#include "AST/SymbolTable.h"
# include "parser.hpp"
%}


%option noyywrap nounput noinput


%{
    yy::parser::symbol_type make_INT (const std::string &s, const yy::parser::location_type& loc);
    yy::parser::symbol_type make_STRING (const std::string &s, const yy::parser::location_type& loc);
    yy::parser::symbol_type make_FLOAT(const std::string&s,const yy::parser::location_type& loc);
    yy::parser::symbol_type make_SYMBOL(const std::string&s,const yy::parser::location_type& loc);
%}
string \"[a-zA-Z0-9 ]*\"
id    [a-zA-Z][a-zA-Z0-9]*
int   [0-9]+
float [0-9]*\.[0-9]+
blank [ \t\r]


%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}

%%
%{
  // Code run each time yylex is called.
   yy::location&loc=drv.location;
   loc.step();
%}

{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();
"-"        return yy::parser::make_SUBTRACTION(loc);
"+"        return yy::parser::make_ADDITION(loc);
"*"        return yy::parser::make_MULTIPLICATION(loc);
"=="       return yy::parser::make_EQUAL(loc);
"!="       return yy::parser::make_NEQUAL(loc);
">"        return yy::parser::make_GREATER(loc);
"<"        return yy::parser::make_LESS(loc);
">="       return yy::parser::make_GREATEREQ(loc);
"<="       return yy::parser::make_LESSEQ(loc);
"||"       return yy::parser::make_OR(loc);
"&&"       return yy::parser::make_AND(loc);
"!"        return yy::parser::make_NOT(loc);
"/"        return yy::parser::make_DIVISION(loc);
"("        return yy::parser::make_LPAREN (loc);
")"        return yy::parser::make_RPAREN (loc);
"="        return yy::parser::make_ASSIGNMENT(loc);
"var"      return yy::parser::make_VAR(loc);
"if"       return yy::parser::make_IF(loc);
"else"       return yy::parser::make_ELSE(loc);
";"        return yy::parser::make_SEMICOLON(loc);
","        return yy::parser::make_COMMA(loc);
"func"     return yy::parser::make_FUNC(loc);
"{"        return yy::parser::make_LBLOCK(loc);
"}"        return yy::parser::make_RBLOCK(loc);
"return"   return yy::parser::make_RETURN(loc);
"false"    return yy::parser::make_LITERAL(AST::Value(false),loc);
"true"    return yy::parser::make_LITERAL(AST::Value(true),loc);
{int}      return make_INT(std::string(yytext),loc);
{string}   return make_STRING(std::string(yytext),loc);
{float}    return make_FLOAT(std::string(yytext),loc);
{id}       return make_SYMBOL(std::string(yytext),loc);
<<EOF>>    return yy::parser::make_YYEOF (loc);
%%


yy::parser::symbol_type make_INT (const std::string &s, const yy::parser::location_type& loc)
{
   try{
        int i=std::stoi(s);
        return yy::parser::make_LITERAL(AST::Value(i),loc);
   }
   catch(const std::out_of_range&e){
        throw yy::parser::syntax_error (loc, "integer is out of range: " + s);
   }

}
yy::parser::symbol_type make_FLOAT(const std::string &s, const yy::parser::location_type& loc)
{
   try{
        double i=std::stod(s);
        return yy::parser::make_LITERAL(AST::Value(i),loc);
   }
   catch(const std::out_of_range&e){
        throw yy::parser::syntax_error (loc, "float is out of range: " + s);
   }
}

yy::parser::symbol_type make_STRING(const std::string &s, const yy::parser::location_type& loc)
{
  return yy::parser::make_LITERAL (AST::Value(s.substr(1,s.size()-2)), loc);
}

yy::parser::symbol_type make_SYMBOL(const std::string &s, const yy::parser::location_type& loc)
{
    return yy::parser::make_IDENTIFIER(AST::globalSymtable.addSymbol(s),loc);
}


void Driver::scan_begin ()
{
   if (!(yyin = fopen (current_file.c_str (), "r")))
    {
      std::cerr << "cannot open " << current_file << ": " << strerror (errno) << '\n';
      exit (EXIT_FAILURE);
    }
}

void Driver::scan_end ()
{
  fclose (yyin);
}