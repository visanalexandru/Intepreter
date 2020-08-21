//
// Created by gvisan on 14.08.2020.
//

#include "VarDeclarationStmt.h"

namespace AST {

    VarDeclarationStmt::VarDeclarationStmt(yy::location loc, Symbol sym) :
            StmtNode(loc),
            symbol(std::move(sym)), value(nullptr) {


    }

    VarDeclarationStmt::VarDeclarationStmt(yy::location loc, Symbol sym, std::shared_ptr<ExpNode> exp) :
            StmtNode(loc),
            symbol(std::move(sym)),
            value(std::move(exp)) {

    }

    void VarDeclarationStmt::execute() {
        if (value != nullptr) {
            globalContext.declareVar(symbol.symbol_name, value->evaluate());
        } else {
            globalContext.declareVar(symbol.symbol_name, Value());
        }
    }
}