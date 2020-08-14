//
// Created by gvisan on 14.08.2020.
//

#include "ExpressionStmt.h"


namespace AST {

    ExpressionStmt::ExpressionStmt(std::shared_ptr<ExpNode> expression) : exp(std::move(expression)) {

    }

    void ExpressionStmt::execute() {
        exp->evaluate();
    }
}