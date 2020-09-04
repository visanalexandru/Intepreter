//
// Created by gvisan on 12.08.2020.
//

#include "BinaryOpExp.h"

namespace AST {
    BinaryOpExp::BinaryOpExp(yy::location loc, AST::BinaryOperator t, std::unique_ptr<ExpNode> l,
                             std::unique_ptr<ExpNode> r) :
            ExpNode(loc),
            type(t),
            left(std::move(l)),
            right(std::move(r)) {
    }

    void BinaryOpExp::solveVarReferences(VM::DeclarationStack &stack, std::vector<Error> &errors) {
        left->solveVarReferences(stack, errors);
        right->solveVarReferences(stack, errors);
    }

    void BinaryOpExp::emitBytecode(VM::VirtualMachine &vm, VM::BytecodeChunk &chunk) const {
        switch (type) {
            case BinaryOperator::Add:
                left->emitBytecode(vm, chunk);
                right->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::BINARY_ADD);
                break;
            case BinaryOperator::Subtract:
                left->emitBytecode(vm, chunk);
                right->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::BINARY_SUBTRACT);
                break;
            case BinaryOperator::Multiply:
                left->emitBytecode(vm, chunk);
                right->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::BINARY_MULTIPLY);
                break;
            case BinaryOperator::Divide:
                left->emitBytecode(vm, chunk);
                right->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::BINARY_DIVIDE);
                break;
            case BinaryOperator::Equal:
                left->emitBytecode(vm, chunk);
                right->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::BINARY_EQUAL);
                break;
            case BinaryOperator::NEqual:
                left->emitBytecode(vm, chunk);
                right->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::BINARY_NEQUAL);
                break;
            case BinaryOperator::Greater:
                left->emitBytecode(vm, chunk);
                right->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::BINARY_GREATER);
                break;
            case BinaryOperator::GreaterEq:
                left->emitBytecode(vm, chunk);
                right->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::BINARY_GREATEREQ);
                break;
            case BinaryOperator::Less:
                left->emitBytecode(vm, chunk);
                right->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::BINARY_LESS);
                break;
            case BinaryOperator::LessEq:
                left->emitBytecode(vm, chunk);
                right->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::BINARY_LESSEQ);
                break;


            case BinaryOperator::And: {
                left->emitBytecode(vm, chunk);

                chunk.pushOpcode(VM::Opcode::JUMP_IF_FALSE);
                unsigned location = chunk.getBytecodeSize();//location to patch
                chunk.pushUInt(0);//to be patched
                chunk.pushOpcode(VM::Opcode::POP);

                right->emitBytecode(vm, chunk);

                chunk.patchUInt(chunk.getBytecodeSize(), location);
                break;
            }

            case BinaryOperator::Or: {
                left->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::JUMP_IF_TRUE);
                unsigned location = chunk.getBytecodeSize();//location to patch
                chunk.pushUInt(0);//to be patched
                chunk.pushOpcode(VM::Opcode::POP);

                right->emitBytecode(vm, chunk);

                chunk.patchUInt(chunk.getBytecodeSize(), location);
                break;
            }


            case BinaryOperator::Modulus:
                left->emitBytecode(vm, chunk);
                right->emitBytecode(vm, chunk);
                chunk.pushOpcode(VM::Opcode::BINARY_MODULUS);
                break;
        }

    }
}