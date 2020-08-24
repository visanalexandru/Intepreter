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

        std::deque<std::deque<Value>> scopes;
    public:

        Context();

        /*Push a variable into the current scope*/
        void pushVar(const Value &value);

        /*Declare a function */
        void declareFunc(const Symbol &funcsymbol, std::unique_ptr<Function> function);

        /*Check if a function is declared*/
        bool isFuncDeclared(const Symbol &funcsymbol);

        /*Get a reference to a function with that name.*/
        const std::unique_ptr<Function> &getFunc(const Symbol &funcsymbol);

        /*Get a reference to the variable at the location.*/
        Value&getVar(const VariableLocation&location);

        /*Creates a new scope and pushes it to the scope list*/
        void pushScope();

        /*Deletes the current scope and removes it from the scope list
         *Calling this function when there is no scope in the list is undefined*/
        void popScope();
    };

    /*The global context of the interpreted program
     *Function calls,assignments etc will refer to this variable*/
    extern Context globalContext;

}


#endif //INTERPRETER_CONTEXT_H
