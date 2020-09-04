//
// Created by gvisan on 27.08.2020.
//

#ifndef INTERPRETER_VIRTUALMACHINE_H
#define INTERPRETER_VIRTUALMACHINE_H

#include<vector>
#include<iostream>
#include "Preprocess/DeclarationStack.h"
#include "Value/Value.h"
#include "Value/Arithmetic.h"
#include "Opcode.h"
#include "BytecodeChunk.h"
#include "CoreFunction/CoreFunction.h"

namespace VM {

    class VirtualMachine {
    private:
        const unsigned stack_size;

        BytecodeChunk bytecode;

        /*Literals.*/
        std::vector<Value> literals;

        /*The value stack*/
        Value *stack;

        /*The stack pointer*/
        unsigned stack_ptr;

        VM::DeclarationStack declaration_stack;

        Value &popValue();

        void pushValue(const Value &value);

        Value&topOfStack();

    public:
        VirtualMachine();

        ~VirtualMachine();

        void pushLiteral(const Value &literal);

        unsigned getLiteralCount() const;

        void executeOpcode(Opcode opcode);

        void disassemble();

        BytecodeChunk &getChunk();

        VM::DeclarationStack&getDeclarationStack();

        void run();

    };

}


#endif //INTERPRETER_VIRTUALMACHINE_H
