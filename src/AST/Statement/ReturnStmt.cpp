//
// Created by gvisan on 16.08.2020.
//

#include "ReturnStmt.h"

namespace AST {

    ReturnStmt::ReturnStmt(std::unique_ptr<ExpNode> to_return) : expression(std::move(to_return)) {


    }

    ReturnStmt::ReturnStmt() : expression(nullptr) {

    }

    void ReturnStmt::execute() {
        if (expression != nullptr)
            setReturnValue(expression->evaluate());
        else setReturnValue(Value());
    }


}