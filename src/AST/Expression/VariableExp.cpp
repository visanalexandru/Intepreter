//
// Created by gvisan on 14.08.2020.
//

#include "VariableExp.h"

namespace AST {

    VariableExp::VariableExp(Symbol sym) :symbol(std::move(sym)) {


    }

    Value VariableExp::evaluate() const {
        return globalContext.getVar(symbol.symbol_name);
    }
}