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

    void WhileStmt::solveDeclarations(DeclarationStack &stack, std::vector<Error> &errors){
        condition->solveVarReferences(stack, errors);
        body->solveDeclarations(stack,errors);
    }

    void WhileStmt::emitBytecode(VM::VirtualMachine &vm) const {
        unsigned begin=vm.getBytecodeSize();
        condition->emitBytecode(vm);
        vm.pushOpcode(VM::Opcode::JUMP_IF_FALSE);
        unsigned body_begin=vm.getBytecodeSize();
        vm.pushUInt(0);

        vm.pushOpcode(VM::Opcode::POP);

        body->emitBytecode(vm);
        vm.pushOpcode(VM::Opcode::JUMP);
        vm.pushUInt(begin);

        vm.patchUInt(vm.getBytecodeSize(),body_begin);
        vm.pushOpcode(VM::Opcode::POP);

    }

}