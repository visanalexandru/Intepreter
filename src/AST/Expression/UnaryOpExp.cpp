//
// Created by gvisan on 12.08.2020.
//

#include "UnaryOpExp.h"

namespace AST {
    UnaryOpExp::UnaryOpExp(yy::location loc, AST::UnaryOperator t, std::unique_ptr<ExpNode> op) :
            ExpNode(loc),
            type(t),
            exp(std::move(op)) {
    }

    void UnaryOpExp::solveVarReferences(VM::DeclarationStack &stack, std::vector<Error> &errors) {
        exp->solveVarReferences(stack, errors);
    }

    void UnaryOpExp::emitBytecode(VM::VirtualMachine &vm, VM::BytecodeChunk &chunk) const {
        exp->emitBytecode(vm, chunk);
        switch (type) {
            case UnaryOperator::Minus:
                chunk.pushOpcode(VM::Opcode::UNARY_MINUS);
                break;
            case UnaryOperator::Not:
                chunk.pushOpcode(VM::Opcode::UNARY_NOT);
                break;
        }
    }
}