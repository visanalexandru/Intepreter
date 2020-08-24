//
// Created by gvisan on 14.08.2020.
//

#include "VariableExp.h"

namespace AST {

    VariableExp::VariableExp(yy::location loc, Symbol sym) : ExpNode(loc), symbol(std::move(sym)) {


    }

    Value VariableExp::evaluate() const {
        return globalContext.getVar(var_location);
    }

    void VariableExp::solveVarReferences(AST::DeclarationStack &stack, std::vector<Error> &errors) {
        if (!stack.getVariableLocation(symbol, var_location))
            errors.emplace_back("semantic error, variable is not declared: " + symbol.symbol_name, location);
    }
}