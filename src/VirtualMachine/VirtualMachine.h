//
// Created by gvisan on 27.08.2020.
//

#ifndef INTERPRETER_VIRTUALMACHINE_H
#define INTERPRETER_VIRTUALMACHINE_H

#include<vector>
#include<stack>
#include "AST/Value/Value.h"
#include "Opcode.h"
#include<iostream>

namespace VM {

    class VirtualMachine {
    private:
        /*The bytecode of the program*/
        std::vector<uint8_t> bytecode;

        /*Constants.*/
        std::vector<AST::Value> literals;

        /*The value stack.*/
        std::stack<AST::Value> value_stack;

        /*The location of the execution*/
        unsigned bytecode_location;

        AST::Value popValue();

    public:
        VirtualMachine();

        unsigned getBytecodeSize() const;

        void pushOpcode(Opcode opcode);

        void pushLiteral(const AST::Value&literal);

        unsigned getLiteralCount() const;

        void pushUInt(uint32_t to_push);

        void patchUInt(uint32_t to_patch,unsigned index);

        uint32_t readUInt();

        void executeOpcode(Opcode opcode);

        void disassemble();

        void run();

    };

}


#endif //INTERPRETER_VIRTUALMACHINE_H
