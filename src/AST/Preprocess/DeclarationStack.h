//
// Created by gvisan on 21.08.2020.
//

#ifndef INTERPRETER_DECLARATIONSTACK_H
#define INTERPRETER_DECLARATIONSTACK_H

#include<memory>
#include<unordered_set>
#include<deque>
#include "AST/Function/Function.h"


namespace AST {
    /*Useful for finding duplicate variable/function declarations and resolving variables.*/
    class DeclarationStack {
    private:
        /*Use an unordered set for constant lookup on find()*/
        std::unordered_set<unsigned long> function_declarations;

        std::deque<std::unordered_set<unsigned long>> variable_declarations;


    public:
        /*Check if a function was added to the function declaration list. Useful for finding duplicate
         * function declarations.*/
        bool functionExists(unsigned long index) const;

        /*Add a new function declaration(its symbol) to the func declaration list*/
        void addFunction(unsigned long index);

        /*Add a new variable declaration to the var declaratoin list*/
        void addVariable(unsigned long index);

        /*Check if a variable was declared in the current scope. Useful for finding duplicate variable
         * declarations*/
        bool variableInCurrentScope(unsigned long index) const;

        /*Create new scope for the variable declarations*/
        void push_scope();

        /*Pop the current variable declaration scope*/
        void pop_scope();

        /*Push a variable declaration scope by default*/
        DeclarationStack();

    };
}


#endif //INTERPRETER_DECLARATIONSTACK_H
