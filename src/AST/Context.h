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

namespace AST {
    /*This class manages scopes and function definitions*/
    class Context {
    private:
        std::deque<std::unordered_map<unsigned long, Value>> scopes;

        std::unordered_map<unsigned long, std::unique_ptr<Function>> functions;

        /*Returns a pointer to the scope of a variable referenced by name
         * The search is made "upwards", from the current scope to the base scope
         * If no scope was found that contains the variable, return nullptr .*/
        std::unordered_map<unsigned long, Value> *findScopeOf(const Symbol&varsymbol);

    public:
        Context();

        /*Declare a variable in this scope and assign its value*/
        void declareVar(const Symbol&varsymbol, const Value &value);

        /*Declared a function */
        void declareFunc(const Symbol&funcsymbol, std::unique_ptr<Function> function);

        /*Check if a variable is declared (search for its scope)*/
        bool isVarDeclared(const Symbol&varsymbol);

        /*Check if a function is declared*/
        bool isFuncDeclared(const Symbol&funcsymbol);

        /*Get the value of the variable. Will call findScopeOf() function
         * Throw an exception if the variable has not been found*/
        Value getVar(const Symbol&varsymbol);

        /*Get a reference to a function with that name. Throw an exception if the function has not been found*/
        const std::unique_ptr<Function> &getFunc(const Symbol&funcsymbol);

        /*Assign the value of the variable. Will call findScopeOf() function*/
        void setVar(const Symbol&varsymbol, const Value &value);

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
