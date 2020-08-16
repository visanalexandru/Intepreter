//
// Created by gvisan on 16.08.2020.
//

#include "ReturnStmt.h"

namespace AST {

    ReturnStmt::ReturnStmt(std::unique_ptr<ExpNode> to_return) : expression(std::move(to_return)) {


    }

    void ReturnStmt::execute() {
        setReturnValue(expression->evaluate());
    }

}