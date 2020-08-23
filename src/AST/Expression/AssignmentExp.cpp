//
// Created by gvisan on 14.08.2020.
//

#include "AssignmentExp.h"

namespace AST {
    AssignmentExp::AssignmentExp(yy::location loc, Symbol sym, std::unique_ptr<ExpNode> value) :
            ExpNode(loc),
            symbol(std::move(sym)),
            exp(std::move(value)) {


    }

    Value AssignmentExp::evaluate() const {
        Value result = exp->evaluate();
        if(!globalContext.isVarDeclared(symbol)){
            throw std::runtime_error(Error("runtime error, variable has not been declared: " + symbol.symbol_name,location).toString());
        }
        globalContext.setVar(symbol, result);
        return result;
    }
}