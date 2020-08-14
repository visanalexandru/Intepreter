//
// Created by gvisan on 14.08.2020.
//

#include "VariableExp.h"

namespace AST {

    VariableExp::VariableExp(std::string varname) : name(std::move(varname)) {


    }

    Value VariableExp::evaluate() const {
        return globalContext.getVar(name);
    }
}