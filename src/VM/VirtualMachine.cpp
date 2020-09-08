//
// Created by gvisan on 27.08.2020.
//

#include "VirtualMachine.h"


namespace VM {

    VirtualMachine::VirtualMachine() : stack_size(1048576), stack_ptr(nullptr) {
        stack = new Value[stack_size];
        stack_ptr = stack;

        declaration_stack.addVariable(globalSymtable.addSymbol("print"));
        pushValue(makeNativeFunctionObjValue(GC::globalGc.makeNativeFunctionObj("print", 1, print)));
    }

    VM::DeclarationStack &VirtualMachine::getDeclarationStack() {
        return declaration_stack;
    }

    VirtualMachine::~VirtualMachine() {
        delete[]stack;
    }

    const Value &VirtualMachine::popValue() {
        Value &to_return = *(stack_ptr - 1);
        stack_ptr--;
        return to_return;
    }

    void VirtualMachine::pushValue(const Value &value) {
        *stack_ptr = value;
        stack_ptr++;
    }

    Value &VirtualMachine::topOfStack() {
        return *(stack_ptr - 1);
    }


    void VirtualMachine::call(const Value &value, unsigned int num_parameters) {
        if (value.type != ValueType::NativeFunction) {
            throw std::runtime_error(typeToString(value.type) + " is not callable");
        } else {
            NativeFunctionObj *native = asNativeFunctionObj(value);
            if (num_parameters != native->arity) {
                throw std::runtime_error(
                        native->name + "() requires " + std::to_string(native->arity) +
                        " parameters but " + std::to_string(num_parameters) + " were provided");
            }
            stack_ptr -= num_parameters;
            pushValue(native->data(stack_ptr));
        }
    }

    void VirtualMachine::executeChunk(BytecodeChunk &chunk) {
        uint8_t opcode;
        chunk.jump(0);
        while (!chunk.reachedEnd()) {
            opcode=chunk.readByte();
            switch (opcode) {
                case Opcode::LOAD_LITERAL:
                    pushValue(literals[chunk.readUInt()]);
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
                    unsigned to_jump = chunk.readUInt();
                    if (asBool(topOfStack()))
                        chunk.jump(to_jump);
                    break;
                }
                case Opcode::JUMP_IF_FALSE: {
                    unsigned to_jump = chunk.readUInt();
                    if (!asBool(topOfStack())) {
                        chunk.jump(to_jump);
                    }
                    break;
                }

                case Opcode::JUMP:
                    chunk.jump(chunk.readUInt());
                    break;
                case Opcode::POP:
                    popValue();
                    break;
                case Opcode::LOAD_LOCAL:
                    pushValue(stack[chunk.readUInt()]);
                    break;
                case Opcode::LOAD_GLOBAL:
                    pushValue(stack[chunk.readUInt()]);
                    break;
                case Opcode::ASSIGN_LOCAL: {
                    const Value &to_assign = popValue();
                    stack[chunk.readUInt()] = to_assign;
                    pushValue(to_assign);
                    break;
                }

                case Opcode::ASSIGN_GLOBAL: {
                    const Value &to_assign = popValue();
                    stack[chunk.readUInt()] = to_assign;
                    pushValue(to_assign);
                    break;
                }

                case Opcode::FUNCTION_CALL: {
                    const Value &func = popValue();
                    unsigned arity = chunk.readUInt();
                    call(func, arity);
                    break;
                }

                default:
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

    void VirtualMachine::disassembleChunk(BytecodeChunk &chunk, const std::string &prefix) {
        chunk.jump(0);
        std::cout << prefix + "Bytecode chunk size " << chunk.getBytecodeSize() << std::endl;
        while (!chunk.reachedEnd()) {
            std::cout << prefix << chunk.getCursor() << " ";
            auto op = chunk.readByte();
            switch (op) {

                case Opcode::LOAD_LITERAL: {
                    Value &literal = literals[chunk.readUInt()];
                    std::cout << "LOAD_LITERAL " << toString(literal) << std::endl;
                    if (literal.type == ValueType::DefinedFunction) {
                        auto fn = asDefinedFunctionObj(literal);
                        std::cout << "\tFUNCTION " << fn->name << std::endl;
                        disassembleChunk(fn->bytecode, prefix + "\t");
                    }
                    break;
                }
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
                    std::cout << "JUMP_IF_FALSE " << chunk.readUInt() << std::endl;
                    break;
                case Opcode::JUMP_IF_TRUE:
                    std::cout << "JUMP_IF_TRUE " << chunk.readUInt() << std::endl;
                    break;
                case Opcode::JUMP:
                    std::cout << "JUMP " << chunk.readUInt() << std::endl;
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
                    std::cout << "LOAD_LOCAL " << chunk.readUInt() << std::endl;
                    break;
                case Opcode::LOAD_GLOBAL:
                    std::cout << "LOAD_GLOBAL " << chunk.readUInt() << std::endl;
                    break;
                case Opcode::ASSIGN_LOCAL:
                    std::cout << "ASSIGN_LOCAL " << chunk.readUInt() << std::endl;
                    break;
                case Opcode::ASSIGN_GLOBAL:
                    std::cout << "ASSIGN_GLOBAL " << chunk.readUInt() << std::endl;
                    break;
                case Opcode::FUNCTION_CALL:
                    std::cout << "FUNCTION_CALL " << chunk.readUInt() << std::endl;
                    break;
                default:
                    std::cout << "UNKNOWN" << std::endl;
                    break;
            }
        }
    }

}