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
#include "SymbolTable/SymbolTable.h"
#include "Utils.h"

namespace VM {

    class VirtualMachine {
    private:

        struct CallFrame{
            Value*base;

            uint8_t *chunk;

            unsigned ip;//instruction pointer
        };

        CallFrame frames[1000];

        unsigned call_frames;

        CallFrame*current_call_frame;

        const unsigned stack_size;

        /*Literals.*/
        std::vector<Value> literals;

        /*The stack*/
        Value*stack;

        /*The stack pointer*/
        Value*stack_ptr;

        VM::DeclarationStack declaration_stack;

        const Value&popValue();

        void pushValue(const Value &value);

        Value&topOfStack();

        void call(const Value&value,unsigned num_parameters);

    public:
        VirtualMachine();

        ~VirtualMachine();

        void pushLiteral(const Value &literal);

        unsigned getLiteralCount() const;

        void disassembleChunk(BytecodeChunk&chunk,const std::string&prefix);

        void executeChunk(BytecodeChunk&chunk);

        VM::DeclarationStack&getDeclarationStack();

    };

}


#endif //INTERPRETER_VIRTUALMACHINE_H
