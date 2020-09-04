//
// Created by gvisan on 27.08.2020.
//

#include "VirtualMachine.h"


namespace VM {

    VirtualMachine::VirtualMachine() : stack_size(1048576), stack_ptr(0) {
        stack = new Value[stack_size];
    }

    VirtualMachine::~VirtualMachine() {
        delete []stack;
    }

    Value &VirtualMachine::popValue() {
        Value &to_return = stack[stack_ptr - 1];
        stack_ptr--;
        return to_return;
    }

    void VirtualMachine::pushValue(const Value &value) {
        stack[stack_ptr++] = value;
    }

    Value &VirtualMachine::topOfStack() {
        return stack[stack_ptr - 1];
    }

    BytecodeChunk &VirtualMachine::getChunk() {
        return bytecode;
    }

    void VirtualMachine::executeOpcode(Opcode opcode) {
        switch (opcode) {
            case Opcode::LOAD_LITERAL:
                pushValue(literals[bytecode.readUInt()]);
                break;
            case Opcode::BINARY_ADD:
                pushValue(add(popValue(), popValue()));
                break;
            case Opcode::BINARY_SUBTRACT:
                pushValue(subtract(popValue(), popValue()));
                break;
            case Opcode::BINARY_MULTIPLY:
                pushValue(multiply(popValue(), popValue()));
                break;
            case Opcode::BINARY_DIVIDE:
                pushValue(divide(popValue(), popValue()));
                break;
            case Opcode::BINARY_EQUAL:
                pushValue(equal(popValue(), popValue()));
                break;
            case Opcode::BINARY_NEQUAL:
                pushValue(nequal(popValue(), popValue()));
                break;
            case Opcode::BINARY_LESS:
                pushValue(less(popValue(), popValue()));
                break;
            case Opcode::BINARY_LESSEQ:
                pushValue(lesseq(popValue(), popValue()));
                break;
            case Opcode::BINARY_GREATER:
                pushValue(greater(popValue(), popValue()));
                break;
            case Opcode::BINARY_GREATEREQ:
                pushValue(greatereq(popValue(), popValue()));
                break;
            case Opcode::BINARY_MODULUS:
                pushValue(modulo(popValue(), popValue()));
                break;
            case Opcode::UNARY_MINUS:
                pushValue(uminus(popValue()));
                break;
            case Opcode::UNARY_NOT:
                pushValue(makeBoolValue(!asBool(castToBool(popValue()))));
                break;
            case Opcode::JUMP_IF_TRUE: {
                unsigned to_jump = bytecode.readUInt();
                if (asBool(topOfStack()))
                    bytecode.jump(to_jump);
                break;
            }
            case Opcode::JUMP_IF_FALSE: {
                unsigned to_jump = bytecode.readUInt();
                if (!asBool(topOfStack())) {
                    bytecode.jump(to_jump);
                }
                break;
            }

            case Opcode::JUMP:
                bytecode.jump(bytecode.readUInt());
                break;
            case Opcode::POP:
                popValue();
                break;
            case Opcode::LOAD_LOCAL:
                pushValue(stack[bytecode.readUInt()]);
                break;
            case Opcode::LOAD_GLOBAL:
                pushValue(stack[bytecode.readUInt()]);
                break;
            case Opcode::ASSIGN_LOCAL: {
                Value&to_assign = popValue();
                stack[bytecode.readUInt()]=to_assign;
                pushValue(to_assign);
                break;
            }

            case Opcode::ASSIGN_GLOBAL: {
                Value to_assign = popValue();
                stack[bytecode.readUInt()]=to_assign;
                pushValue(to_assign);
                break;
            }
        }
    }


    void VirtualMachine::pushLiteral(const Value &literal) {
        literals.push_back(literal);
    }

    unsigned VirtualMachine::getLiteralCount() const {
        return literals.size();
    }

    void VirtualMachine::disassemble() {
        bytecode.jump(0);
        std::cout << "Bytecode chunk size " << bytecode.getBytecodeSize() << std::endl;
        while (!bytecode.reachedEnd()) {
            std::cout << bytecode.getCursor() << " ";
            auto op = bytecode.readOpcode();
            switch (op) {

                case Opcode::LOAD_LITERAL:
                    std::cout << "LOAD_LITERAL " << toString(literals[bytecode.readUInt()]) << std::endl;
                    break;
                case Opcode::BINARY_ADD:
                    std::cout << "BINARY_ADD " << std::endl;
                    break;
                case Opcode::BINARY_SUBTRACT:
                    std::cout << "BINARY_SUBTRACT " << std::endl;
                    break;
                case Opcode::BINARY_MULTIPLY:
                    std::cout << "BINARY_MULTIPLY" << std::endl;
                    break;
                case Opcode::BINARY_DIVIDE:
                    std::cout << "BINARY_DIVIDE" << std::endl;
                    break;
                case Opcode::BINARY_EQUAL:
                    std::cout << "BINARY_EQUAL" << std::endl;
                    break;
                case Opcode::BINARY_NEQUAL:
                    std::cout << "BINARY_NEQUAL" << std::endl;
                    break;
                case Opcode::BINARY_LESS:
                    std::cout << "BINARY_LESS" << std::endl;
                    break;
                case Opcode::BINARY_LESSEQ:
                    std::cout << "BINARY_LESSEQ" << std::endl;
                    break;
                case Opcode::BINARY_GREATER:
                    std::cout << "BINARY_GREATER" << std::endl;
                    break;
                case Opcode::BINARY_GREATEREQ:
                    std::cout << "BINARY_GREATEREQ" << std::endl;
                    break;
                case Opcode::JUMP_IF_FALSE:
                    std::cout << "JUMP_IF_FALSE " << bytecode.readUInt() << std::endl;
                    break;
                case Opcode::JUMP_IF_TRUE:
                    std::cout << "JUMP_IF_TRUE " << bytecode.readUInt() << std::endl;
                    break;
                case Opcode::JUMP:
                    std::cout << "JUMP " << bytecode.readUInt() << std::endl;
                    break;
                case Opcode::POP:
                    std::cout << "POP" << std::endl;
                    break;
                case Opcode::BINARY_MODULUS:
                    std::cout << "BINARY_MODULUS" << std::endl;
                    break;
                case Opcode::UNARY_NOT:
                    std::cout << "UNARY_NOT" << std::endl;
                    break;
                case Opcode::UNARY_MINUS:
                    std::cout << "UNARY_MINUS" << std::endl;
                    break;
                case Opcode::LOAD_LOCAL:
                    std::cout << "LOAD_LOCAL " << bytecode.readUInt() << std::endl;
                    break;
                case Opcode::LOAD_GLOBAL:
                    std::cout << "LOAD_GLOBAL " << bytecode.readUInt() << std::endl;
                    break;
                case Opcode::ASSIGN_LOCAL:
                    std::cout << "ASSIGN_LOCAL " << bytecode.readUInt() << std::endl;
                    break;
                case Opcode::ASSIGN_GLOBAL:
                    std::cout << "ASSIGN_GLOBAL " << bytecode.readUInt() << std::endl;
                default:
                    std::cout << "UNKNOWN" << std::endl;
                    break;
            }
        }
    }

    void VirtualMachine::run() {
        bytecode.jump(0);
        while (!bytecode.reachedEnd()) {
            executeOpcode(bytecode.readOpcode());
        }

        for(unsigned i=0;i<stack_ptr;i++){
            std::cout<<toString(stack[i])<<" ";
        }
    }

}