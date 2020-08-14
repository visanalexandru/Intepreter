#ifndef DRIVER_H
#define DRIVER_H

#include"parser.hpp"
#include"AST/Value/Value.h"
#include "AST/Statement/StmtNode.h"
#define YY_DECL yy::parser::symbol_type yylex(Driver&drv)

YY_DECL;

/*This class is responsible for starting the parse over a file.
 * At the end of the parsing it will hold an AST representing the parsed file.*/
class Driver {
public:
    /* parse the file,return 0 on success, 1 otherwise*/
    int parse(const std::string &f);

    /*variable that holds the current location of the scanning*/
    yy::location location;

    /* the result of the parse*/
    std::vector<std::unique_ptr<AST::StmtNode>> result;
private:
    /*the file that is currently being scanned */
    std::string current_file;

    /*begin the scanning phase,implemented in the flex scanner file*/
    void scan_begin();

    /*end the scanning phase,implemented in the flex scanner file*/
    void scan_end();

};

#endif //DRIVER_H
