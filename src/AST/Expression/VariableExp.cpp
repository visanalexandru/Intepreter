//
// Created by gvisan on 14.08.2020.
//

#include "VariableExp.h"

namespace AST {

    VariableExp::VariableExp(yy::location loc, Symbol sym) : ExpNode(loc), symbol(std::move(sym)), assign(nullptr) {


    }

    VariableExp::VariableExp(yy::location loc, Symbol sym, std::unique_ptr<ExpNode> to_assign) : ExpNode(loc),
                                                                                                 symbol(std::move(sym)),
                                                                                                 assign(std::move(to_assign)){

    }

    Value VariableExp::evaluate() const {
        Value&value=globalContext.getVar(var_location);
        if(assign!= nullptr)
            value=assign->evaluate();
        return value;
    }

    void VariableExp::solveVarReferences(AST::DeclarationStack &stack, std::vector<Error> &errors) {
        if (!stack.getVariableLocation(symbol, var_location))
            errors.emplace_back("semantic error, variable is not declared: " + symbol.symbol_name, location);
        if(assign!=nullptr)
            assign->solveVarReferences(stack,errors);
    }
}