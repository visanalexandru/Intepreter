//
// Created by gvisan on 27.08.2020.
//

#ifndef INTERPRETER_VIRTUALMACHINE_H
#define INTERPRETER_VIRTUALMACHINE_H

#include<vector>
#include "Value/Value.h"
#include "Value/Arithmetic.h"
#include "Opcode.h"
#include "BytecodeChunk.h"
#include<iostream>

namespace VM {

    class VirtualMachine {
    private:
        const unsigned stack_size;

        BytecodeChunk bytecode;

        /*Constants.*/
        std::vector<VM::Value> literals;

        /*The value stack*/
        VM::Value *stack;

        /*The stack pointer*/
        unsigned stack_ptr;

        VM::Value &popValue();

        void pushValue(const VM::Value &value);

        VM::Value&topOfStack();

    public:
        VirtualMachine();

        ~VirtualMachine();

        void pushLiteral(const VM::Value &literal);

        unsigned getLiteralCount() const;

        void executeOpcode(Opcode opcode);

        void disassemble();

        BytecodeChunk &getChunk();

        void run();

    };

}


#endif //INTERPRETER_VIRTUALMACHINE_H
