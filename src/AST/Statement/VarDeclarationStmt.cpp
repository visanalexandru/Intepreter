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
            globalContext.pushVar(value->evaluate());
        } else {
            globalContext.pushVar(Value());
        }
    }

    void VarDeclarationStmt::checkDeclarations(AST::DeclarationStack &stack, std::vector<Error> &errors) const {
        if(stack.variableInCurrentScope(symbol))
            errors.emplace_back("semantic error, duplicate declaration of variable "+symbol.symbol_name,location);
        else stack.addVariable(symbol);
    }
}