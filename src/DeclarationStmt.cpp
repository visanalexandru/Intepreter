//
// Created by gvisan on 14.08.2020.
//

#include "DeclarationStmt.h"

namespace AST {

    DeclarationStmt::DeclarationStmt(std::string varname) :
            name(std::move(varname)), value(nullptr) {


    }

    DeclarationStmt::DeclarationStmt(std::string varname, std::shared_ptr<ExpNode> exp) :
            name(std::move(varname)),
            value(std::move(exp)) {

    }

    void DeclarationStmt::execute() {
        if (value != nullptr) {
            globalContext.declareVar(name, value->evaluate());
        } else {
            globalContext.declareVar(name, Value());
        }
    }
}