//
// Created by gvisan on 25.08.2020.
//

#include "WhileStmt.h"

namespace AST {

    WhileStmt::WhileStmt(yy::location loc, std::unique_ptr<ExpNode> cond, std::unique_ptr<StmtNode> stmt)
            : StmtNode(loc),
              condition(std::move(cond)){
        body=std::make_unique<CompoundStmt>(loc,std::move(stmt));
    }

    void WhileStmt::checkControlFlow(VM::FlowState &state, std::vector<Error> &errors) const {
        state.enterLoop();
        body->checkControlFlow(state, errors);
        state.exitLoop();
    }

    void WhileStmt::solveDeclarations(VM::DeclarationStack &stack, std::vector<Error> &errors) {
        condition->solveVarReferences(stack, errors);
        body->solveDeclarations(stack, errors);
    }

    void WhileStmt::emitBytecode(VM::VirtualMachine &vm, VM::BytecodeChunk &chunk) const {
        unsigned begin = chunk.getBytecodeSize();
        condition->emitBytecode(vm, chunk);
        chunk.pushOpcode(VM::Opcode::JUMP_IF_FALSE);
        unsigned body_begin = chunk.getBytecodeSize();
        chunk.pushUInt(0);

        chunk.pushOpcode(VM::Opcode::POP);

        body->emitBytecode(vm, chunk);
        chunk.pushOpcode(VM::Opcode::JUMP);
        chunk.pushUInt(begin);

        chunk.patchUInt(chunk.getBytecodeSize(), body_begin);
        chunk.pushOpcode(VM::Opcode::POP);

    }

}