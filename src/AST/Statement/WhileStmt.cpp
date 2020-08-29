//
// Created by gvisan on 25.08.2020.
//

#include "WhileStmt.h"

namespace AST {

    WhileStmt::WhileStmt(yy::location loc, std::unique_ptr<ExpNode> cond, std::unique_ptr<CompoundStmt> stmts)
            : StmtNode(loc),
              condition(std::move(cond)),
              body(std::move(stmts)) {

    }

    void WhileStmt::execute() {
        resetReturnValue();
        while (condition->evaluate().asBool()) {
            body->execute();
            if(body->hasReturned()){
                setReturnValue(body->getReturnValue());
                break;
            }
       }
    }

    void WhileStmt::checkControlFlow(FlowState &state, std::vector<Error> &errors) const {
        state.enterLoop();
        body->checkControlFlow(state,errors);
        state.exitLoop();
    }

    void WhileStmt::checkDeclarations(DeclarationStack &stack, std::vector<Error> &errors) const {
        condition->solveVarReferences(stack, errors);
        body->checkDeclarations(stack,errors);
    }

}