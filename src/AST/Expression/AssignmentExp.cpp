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
        globalContext.getVar(var_location) = result;
        return result;
    }

    void AssignmentExp::solveVarReferences(AST::DeclarationStack &stack, std::vector<Error> &errors) {
        if (!stack.getVariableLocation(symbol, var_location))
            errors.emplace_back("semantic error, variable is not declared: " + symbol.symbol_name, location);
        exp->solveVarReferences(stack,errors);
    }
}