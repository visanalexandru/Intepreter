//
// Created by gvisan on 14.08.2020.
//

#include "AssignmentExp.h"

namespace AST {
    AssignmentExp::AssignmentExp(std::string name, std::unique_ptr<ExpNode> value) :
            varname(std::move(name)),
            exp(std::move(value)) {


    }

    Value AssignmentExp::evaluate() const {
        Value result = exp->evaluate();
        globalContext.setVar(varname, result);
        return result;
    }
}