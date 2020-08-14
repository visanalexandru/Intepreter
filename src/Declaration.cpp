//
// Created by gvisan on 14.08.2020.
//

#include "Declaration.h"

namespace AST {

    Declaration::Declaration(std::string varname) :
            name(std::move(varname)), value(nullptr) {


    }

    Declaration::Declaration(std::string varname, std::shared_ptr<ExpNode> exp) :
            name(std::move(varname)),
            value(std::move(exp)) {

    }

    void Declaration::execute() {
        if (value != nullptr) {
            globalContext.declareVar(name, value->evaluate());
        } else {
            globalContext.declareVar(name, Value());
        }
    }
}