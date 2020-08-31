//
// Created by gvisan on 27.08.2020.
//

#ifndef INTERPRETER_VIRTUALMACHINE_H
#define INTERPRETER_VIRTUALMACHINE_H

#include<vector>
#include "AST/Value/Value.h"
#include "Opcode.h"
#include "BytecodeChunk.h"
#include<iostream>

namespace VM {

    class VirtualMachine {
    private:

        struct CallFrame{
            std::vector<uint8_t> bytecode;

            unsigned bytecode_location;

            std::vector<AST::Value> locals;
        };

        BytecodeChunk bytecode;

        /*Constants.*/
        std::vector<AST::Value> literals;

        /*The list of stack frames*/
        std::vector<std::vector<AST::Value>> stack_frames;


        /*Pops the top of stack value of the current stack frame*/
        AST::Value popValue();

        /*Returns the top of stack value for the current stack frame*/
        AST::Value topOfStack() const;

        /*Returns a reference to the value in the current stack frame*/
        AST::Value& getLocalValue(unsigned index);

        /*Returns a reference to the value int the global stack frame*/
        AST::Value& getGlobalValue(unsigned index);

        /*Push a value on the current stack frame*/
        void pushValue(const AST::Value&value);

        /*Creates a new stack frame,used when calling functions*/
        void pushStackFrame();

        /*Removes the current stack frame, used when returning from functions*/
        void popStackFrame();

    public:
        VirtualMachine();

        void pushLiteral(const AST::Value&literal);

        unsigned getLiteralCount() const;

        void executeOpcode(Opcode opcode);

        void disassemble();

        BytecodeChunk&getChunk();

        void run();

    };

}


#endif //INTERPRETER_VIRTUALMACHINE_H
