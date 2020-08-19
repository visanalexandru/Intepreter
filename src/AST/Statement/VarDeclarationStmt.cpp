//
// Created by gvisan on 14.08.2020.
//

#include "VarDeclarationStmt.h"

namespace AST {

    VarDeclarationStmt::VarDeclarationStmt(yy::location loc, std::string varname) :
            StmtNode(loc),
            name(std::move(varname)), value(nullptr) {


    }

    VarDeclarationStmt::VarDeclarationStmt(yy::location loc, std::string varname, std::shared_ptr<ExpNode> exp) :
            StmtNode(loc),
            name(std::move(varname)),
            value(std::move(exp)) {

    }

    void VarDeclarationStmt::execute() {
        if (value != nullptr) {
            globalContext.declareVar(name, value->evaluate());
        } else {
            globalContext.declareVar(name, Value());
        }
    }
}