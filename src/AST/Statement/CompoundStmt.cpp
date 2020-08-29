//
// Created by gvisan on 28.08.2020.
//

#include "CompoundStmt.h"

namespace AST {

    CompoundStmt::CompoundStmt(yy::location loc, std::vector<std::unique_ptr<StmtNode>> stmts) :
            StmtNode(loc), statements(std::move(stmts)) {


    }

    void CompoundStmt::execute() {
        resetReturnValue();
        globalContext.pushScope();
        for(const auto&stmt:statements){
            stmt->execute();
            if(stmt->hasReturned()){
                setReturnValue(stmt->getReturnValue());
                break;
            }
        }
        globalContext.popScope();
    }

    void CompoundStmt::checkControlFlow(FlowState &state, std::vector<Error> &errors) const {
        for(const auto&stmt:statements){
            stmt->checkControlFlow(state,errors);
        }
    }

    void CompoundStmt::checkDeclarations(DeclarationStack &stack, std::vector<Error> &errors) const {
        stack.pushScope();
        for(const auto&stmt:statements){
            stmt->checkDeclarations(stack,errors);
        }
        stack.popScope();
    }

    std::vector<std::unique_ptr<StmtNode>> & CompoundStmt::getStatements() {
        return statements;
    }
}