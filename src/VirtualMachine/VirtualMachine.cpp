//
// Created by gvisan on 27.08.2020.
//

#include "VirtualMachine.h"


namespace VM {

    VirtualMachine::VirtualMachine() : bytecode_location(0) {
        pushStackFrame();
    }

    void VirtualMachine::pushStackFrame() {
        stack_frames.emplace_back();
    }

    void VirtualMachine::popStackFrame() {
        stack_frames.pop_back();
    }

    AST::Value VirtualMachine::popValue() {
        AST::Value to_return = stack_frames.back().back();
        stack_frames.back().pop_back();
        return to_return;
    }

    void VirtualMachine::pushValue(const AST::Value&value) {
        stack_frames.back().push_back(value);
    }

    AST::Value VirtualMachine::topOfStack() const {
        return stack_frames.back().back();
    }

    AST::Value& VirtualMachine::getLocalValue(unsigned int index){
        return stack_frames.back()[index];
    }

    AST::Value& VirtualMachine::getGlobalValue(unsigned int index){
        return stack_frames.front()[index];
    }

    void VirtualMachine::executeOpcode(Opcode opcode) {
        switch (opcode) {
            case Opcode::LOAD_LITERAL:
                pushValue(literals[readUInt()]);
                break;
            case Opcode::BINARY_ADD:
                pushValue(popValue()+popValue());
                break;
            case Opcode::BINARY_SUBTRACT:
                pushValue(popValue()-popValue());
                break;
            case Opcode::BINARY_MULTIPLY:
                pushValue(popValue() * popValue());
                break;
            case Opcode::BINARY_DIVIDE:
                pushValue(popValue() / popValue());
                break;
            case Opcode::BINARY_EQUAL:
                pushValue(popValue() == popValue());
                break;
            case Opcode::BINARY_NEQUAL:
                pushValue(popValue() != popValue());
                break;
            case Opcode::BINARY_LESS:
                pushValue(popValue() < popValue());
                break;
            case Opcode::BINARY_LESSEQ:
                pushValue(popValue() <= popValue());
                break;
            case Opcode::BINARY_GREATER:
                pushValue(popValue() > popValue());
                break;
            case Opcode::BINARY_GREATEREQ:
                pushValue(popValue() >= popValue());
                break;
            case Opcode::BINARY_MODULUS:
                pushValue(popValue() % popValue());
                break;
            case Opcode::UNARY_MINUS:
                pushValue(-popValue());
                break;
            case Opcode::UNARY_NOT:
                pushValue(AST::Value(!popValue().toBoolObj().asBool()));
                break;
            case Opcode::JUMP_IF_TRUE: {
                unsigned to_jump = readUInt();
                if (topOfStack().asBool())
                    bytecode_location = to_jump;
                break;
            }
            case Opcode::JUMP_IF_FALSE: {
                unsigned to_jump = readUInt();
                if (!topOfStack().asBool()) {
                    bytecode_location = to_jump;
                }
                break;
            }
            case Opcode::JUMP:
                bytecode_location=readUInt();
                break;
            case Opcode::POP:
                popValue();
                break;
            case Opcode::LOAD_LOCAL:
                pushValue(getLocalValue(readUInt()));
                break;
            case Opcode::LOAD_GLOBAL:
                pushValue(getGlobalValue(readUInt()));
                break;
            case Opcode::ASSIGN_LOCAL:{
                AST::Value to_assign=popValue();
                AST::Value&ref=getLocalValue(readUInt());
                pushValue(ref=to_assign);
                break;
            }

            case Opcode::ASSIGN_GLOBAL:{
                AST::Value to_assign=popValue();
                AST::Value&ref=getGlobalValue(readUInt());
                pushValue(ref=to_assign);
                break;
            }
        }
    }


    void VirtualMachine::pushLiteral(const AST::Value &literal) {
        literals.push_back(literal);
    }

    unsigned VirtualMachine::getLiteralCount() const {
        return literals.size();
    }

    void VirtualMachine::pushOpcode(Opcode opcode) {
        bytecode.push_back((uint8_t) opcode);
    }

    void VirtualMachine::pushUInt(uint32_t to_push) {
        bytecode.push_back(to_push & 0xffu);
        bytecode.push_back((to_push >> 8u) & 0xffu);
        bytecode.push_back((to_push >> 16u) & 0xffu);
        bytecode.push_back((to_push >> 24u) & 0xffu);
    }

    void VirtualMachine::patchUInt(uint32_t to_patch, unsigned int index) {
        bytecode[index] = to_patch & 0xffu;
        bytecode[index + 1] = (to_patch >> 8u) & 0xffu;
        bytecode[index + 2] = (to_patch >> 8u) & 0xffu;
        bytecode[index + 3] = (to_patch >> 8u) & 0xffu;
    }

    uint32_t VirtualMachine::readUInt() {
        uint32_t a = bytecode[bytecode_location];
        uint32_t b = bytecode[bytecode_location + 1] << 8u;
        uint32_t c = bytecode[bytecode_location + 2] << 16u;
        uint32_t d = bytecode[bytecode_location + 3] << 24u;

        bytecode_location += 4;

        return a | b | c | d;
    }

    unsigned VirtualMachine::getBytecodeSize() const {
        return bytecode.size();
    }

    void VirtualMachine::disassemble() {
        bytecode_location = 0;
        std::cout << bytecode.size() << std::endl;
        while (bytecode_location < bytecode.size()) {
            std::cout << bytecode_location << " ";
            auto op = (Opcode) bytecode[bytecode_location++];
            switch (op) {

                case Opcode::LOAD_LITERAL:
                    std::cout << "LOAD_LITERAL " << literals[readUInt()].toString() << std::endl;
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
                    std::cout << "JUMP_IF_FALSE " << readUInt() << std::endl;
                    break;
                case Opcode::JUMP_IF_TRUE:
                    std::cout << "JUMP_IF_TRUE " << readUInt() << std::endl;
                    break;
                case Opcode::JUMP:
                    std::cout<<"JUMP "<<readUInt()<<std::endl;
                    break;
                case Opcode::POP:
                    std::cout << "POP" << std::endl;
                    break;
                case Opcode::BINARY_MODULUS:
                    std::cout << "BINARY_MODULUS" << std::endl;
                    break;
                case Opcode::UNARY_NOT:
                    std::cout<<"UNARY_NOT"<<std::endl;
                    break;
                case Opcode::UNARY_MINUS:
                    std::cout<<"UNARY_MINUS"<<std::endl;
                    break;
                case Opcode::LOAD_LOCAL:
                    std::cout<<"LOAD_LOCAL "<<readUInt()<<std::endl;
                    break;
                case Opcode::LOAD_GLOBAL:
                    std::cout<<"LOAD_GLOBAL "<<readUInt()<<std::endl;
                    break;
                case Opcode::ASSIGN_LOCAL:
                    std::cout<<"ASSIGN_LOCAL "<<readUInt()<<std::endl;
                    break;
                case Opcode::ASSIGN_GLOBAL:
                    std::cout<<"ASSIGN_GLOBAL "<<readUInt()<<std::endl;
                default:
                    std::cout << "UNKNOWN" << std::endl;
                    break;
            }
        }
    }

    void VirtualMachine::run() {
        bytecode_location = 0;
        while (bytecode_location < bytecode.size()) {
            executeOpcode((Opcode) bytecode[bytecode_location++]);
            std::cout<<"stack: {";
            for(const AST::Value&value:stack_frames.back())
                std::cout<<value.toString()<<",";
            std::cout<<"}"<<std::endl;
        }
    }

}