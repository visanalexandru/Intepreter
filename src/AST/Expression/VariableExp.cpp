//
// Created by gvisan on 14.08.2020.
//

#include "VariableExp.h"

namespace AST {

    VariableExp::VariableExp(yy::location loc, Symbol sym) : ExpNode(loc), symbol(std::move(sym)) {


    }

    Value VariableExp::evaluate() const {
        if (!globalContext.isVarDeclared(symbol)) {
            throw std::runtime_error(Error("runtime error, variable has not been declared: " + symbol.symbol_name,location).toString());
        }
        return globalContext.getVar(symbol);
    }
}