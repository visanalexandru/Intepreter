//
// Created by gvisan on 14.08.2020.
//

#include "AssignmentExp.h"

namespace AST {
    AssignmentExp::AssignmentExp(Symbol sym, std::unique_ptr<ExpNode> value) :
            symbol(std::move(sym)),
            exp(std::move(value)) {


    }

    Value AssignmentExp::evaluate() const {
        Value result = exp->evaluate();
        globalContext.setVar(symbol.symbol_name, result);
        return result;
    }
}