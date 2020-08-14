//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_DECLARATIONSTMT_H
#define INTERPRETER_DECLARATIONSTMT_H

#include "StmtNode.h"
#include "Context.h"
#include "ExpNode.h"

namespace AST {
    /*This class is responsible for the declaration of a variable at runtime*/
    class DeclarationStmt : public StmtNode {
    private:
        const std::string name;

        /*The expression on the right side of the declaration*/
        std::shared_ptr<ExpNode> value;
    public:
        /*Declares the variable, using the global context object*/
        void execute() override;

        /*Declares the variable with value None*/
        DeclarationStmt(std::string varname);

        /*Declares the variable with the value of the expression*/
        DeclarationStmt(std::string varname, std::shared_ptr<ExpNode> exp);

    };
}


#endif //INTERPRETER_DECLARATIONSTMT_H
