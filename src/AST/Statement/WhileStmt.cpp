//
// Created by gvisan on 25.08.2020.
//

#include "WhileStmt.h"

namespace AST {

    WhileStmt::WhileStmt(yy::location loc, std::unique_ptr<ExpNode> cond,
                         std::vector<std::unique_ptr<StmtNode>> statements) :
            StmtNode(loc), block(std::move(statements)), condition(std::move(cond)) {


    }


    void WhileStmt::execute() {
        resetReturnValue();
        bool should_stop;
        while (condition->evaluate().asBool()) {
            should_stop=false;
            globalContext.pushScope();
            for (const auto &stmt:block) {
                stmt->execute();
                if (stmt->hasReturned()) {
                    setReturnValue(stmt->getReturnValue());
                    should_stop= true;
                    break;
                }
            }

            globalContext.popScope();
            if(should_stop)
                break;
        }
    }

    void WhileStmt::checkControlFlow(FlowState &state, std::vector<Error> &errors) const {
        state.enterLoop();
        for(const auto&stmt:block)
            stmt->checkControlFlow(state,errors);
        state.exitLoop();
    }

    void WhileStmt::checkDeclarations(DeclarationStack &stack, std::vector<Error> &errors) const {
        condition->solveVarReferences(stack,errors);
        stack.pushScope();
        for(const auto&stmt:block)
            stmt->checkDeclarations(stack,errors);
        stack.popScope();
    }

    void WhileStmt::emitBytecode(VM::VirtualMachine &vm) const {

    }

}