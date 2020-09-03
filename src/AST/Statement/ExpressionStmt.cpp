//
// Created by gvisan on 14.08.2020.
//

#include "ExpressionStmt.h"


namespace AST {

    ExpressionStmt::ExpressionStmt(yy::location loc, std::shared_ptr<ExpNode> expression) :
            StmtNode(loc),
            exp(std::move(expression)) {

    }

    void ExpressionStmt::solveDeclarations(AST::DeclarationStack &stack, std::vector<Error> &errors) {
        exp->solveVarReferences(stack,errors);
    }

    void ExpressionStmt::emitBytecode(VM::VirtualMachine &vm,VM::BytecodeChunk&chunk) const {
        exp->emitBytecode(vm,chunk);
        chunk.pushOpcode(VM::Opcode::POP);
    }
}