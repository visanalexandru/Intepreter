//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_CONTEXT_H
#define INTERPRETER_CONTEXT_H

#include<unordered_map>
#include<deque>
#include<string>
#include<memory>
#include<cassert>
#include "AST/Value/Value.h"
#include "AST/Function/CoreFunction/PrintFunc.h"
#include "AST/Symbol.h"
#include "AST/Preprocess/VariableLocation.h"
namespace AST {
    /*This class manages scopes and function definitions*/
    class Context {
    private:


        std::unordered_map<unsigned long, std::unique_ptr<Function>> functions;

        std::vector<std::vector<Value>> stack_frames;
    public:

        Context();

        /*Push a variable into the current stack frame*/
        void pushVar(const Value &value);

        void popVar();

        /*Declare a function */
        void declareFunc(const Symbol &funcsymbol, std::unique_ptr<Function> function);

        /*Check if a function is declared*/
        bool isFuncDeclared(const Symbol &funcsymbol);

        /*Get a reference to a function with that name.*/
        const std::unique_ptr<Function> &getFunc(const Symbol &funcsymbol);

        /*Get a reference to the variable at the location.*/
        Value&getVar(const VariableLocation&location);

        /*Creates a new stack frame and pushes it to the stack frame list*/
        void pushStackFrame();

        /*Pops the current stack frame*/
        void popStackFrame();
    };

    /*The global context of the interpreted program
     *Function calls,assignments etc will refer to this variable*/
    extern Context globalContext;

}


#endif //INTERPRETER_CONTEXT_H
