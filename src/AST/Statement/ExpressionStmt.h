//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_EXPRESSIONSTMT_H
#define INTERPRETER_EXPRESSIONSTMT_H

#include"StmtNode.h"
#include"AST/Expression/ExpNode.h"

namespace AST {
    /*This class represents an expresion followed by a semicolon*/
    class ExpressionStmt : public StmtNode {
    private:
        std::shared_ptr<ExpNode> exp;
    public:
        explicit ExpressionStmt(std::shared_ptr<ExpNode> expression);

        /*Just evaluate the expression*/
        void execute() override;
    };


}


#endif //INTERPRETER_EXPRESSIONSTMT_H
