%{
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <cstring> // strerror
# include <string>
# include "Driver.h"
# include "Value.h"
# include "parser.hpp"
%}


%option noyywrap nounput noinput


%{
    yy::parser::symbol_type make_INT (const std::string &s, const yy::parser::location_type& loc);
%}

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
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
"-"        return yy::parser::make_MINUS  (loc);
"+"        return yy::parser::make_PLUS   (loc);
"*"        return yy::parser::make_STAR   (loc);
"/"        return yy::parser::make_SLASH  (loc);
"("        return yy::parser::make_LPAREN (loc);
")"        return yy::parser::make_RPAREN (loc);
{int}      return make_INT(yytext,loc);
<<EOF>>    return yy::parser::make_YYEOF (loc);
%%


yy::parser::symbol_type make_INT (const std::string &s, const yy::parser::location_type& loc)
{
  errno = 0;
  long n = strtol (s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "integer is out of range: " + s);
  return yy::parser::make_LITERAL ((int) n, loc);
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