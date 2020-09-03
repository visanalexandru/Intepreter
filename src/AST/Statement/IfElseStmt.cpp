//
// Created by gvisan on 19.08.2020.
//

#include "IfElseStmt.h"

namespace AST {

    IfElseStmt::IfElseStmt(yy::location loc, std::unique_ptr<ExpNode> cond, std::unique_ptr<CompoundStmt> ifb,
                           std::unique_ptr<CompoundStmt> elseb) :
            StmtNode(loc),
            condition(std::move(cond)),
            ifbranch(std::move(ifb)),
            elsebranch(std::move(elseb)) {


    }

    void IfElseStmt::checkControlFlow(AST::FlowState &state, std::vector<Error> &errors) const {
        ifbranch->checkControlFlow(state, errors);
        if (elsebranch != nullptr)
            elsebranch->checkControlFlow(state, errors);
    }

    void IfElseStmt::solveDeclarations(AST::DeclarationStack &stack, std::vector<Error> &errors) {
        condition->solveVarReferences(stack, errors);
        ifbranch->solveDeclarations(stack, errors);
        if (elsebranch != nullptr)
            elsebranch->solveDeclarations(stack, errors);
    }

    void IfElseStmt::emitBytecode(VM::VirtualMachine &vm, VM::BytecodeChunk &chunk) const {
        condition->emitBytecode(vm, chunk);
        chunk.pushOpcode(VM::Opcode::JUMP_IF_FALSE);//jump to the else statement if the condition is false
        unsigned jump_to_else_branch = chunk.getBytecodeSize();
        chunk.pushUInt(0);

        chunk.pushOpcode(VM::Opcode::POP);
        ifbranch->emitBytecode(vm, chunk);
        chunk.pushOpcode(VM::Opcode::JUMP);//jump to the end
        unsigned jump_to_end = chunk.getBytecodeSize();
        chunk.pushUInt(0);


        chunk.patchUInt(chunk.getBytecodeSize(), jump_to_else_branch);
        chunk.pushOpcode(VM::Opcode::POP);
        if (elsebranch != nullptr)
            elsebranch->emitBytecode(vm, chunk);
        chunk.patchUInt(chunk.getBytecodeSize(), jump_to_end);
    }


}