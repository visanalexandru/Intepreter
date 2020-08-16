//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_VARDECLARATIONSTMT_H
#define INTERPRETER_VARDECLARATIONSTMT_H

#include "StmtNode.h"
#include "AST/Context.h"
#include "AST/Expression/ExpNode.h"

namespace AST {
    /*This class is responsible for the declaration of a variable at runtime*/
    class VarDeclarationStmt : public StmtNode {
    private:
        const std::string name;

        /*The expression on the right side of the declaration*/
        std::shared_ptr<ExpNode> value;
    public:
        /*Declares the variable, using the global context object*/
        void execute() override;

        /*Declares the variable with value None*/
        explicit VarDeclarationStmt(std::string varname);

        /*Declares the variable with the value of the expression*/
        VarDeclarationStmt(std::string varname, std::shared_ptr<ExpNode> exp);

    };
}


#endif //INTERPRETER_VARDECLARATIONSTMT_H
