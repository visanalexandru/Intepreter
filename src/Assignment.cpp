//
// Created by gvisan on 14.08.2020.
//

#include "Assignment.h"

namespace AST {
    Assignment::Assignment(std::string name, std::unique_ptr<ExpNode> value) :
            varname(std::move(name)),
            exp(std::move(value)) {


    }

    Value Assignment::evaluate() const {
        Value result = exp->evaluate();
        globalContext.setVar(varname, result);
        return result;
    }
}