//
// Created by gvisan on 21.08.2020.
//

#ifndef INTERPRETER_DECLARATIONSTACK_H
#define INTERPRETER_DECLARATIONSTACK_H

#include<memory>
#include<unordered_set>
#include<vector>
#include<algorithm>
#include "AST/Function/Function.h"
#include "AST/Symbol.h"
#include "VariableLocation.h"

namespace AST {
    /*Useful for finding duplicate variable/function declarations and resolving variables.*/
    class DeclarationStack {
    private:

        struct VariableDeclaration{
            Symbol variable_symbol;

            bool is_local;

            VariableDeclaration(Symbol symbol,bool local):variable_symbol(std::move(symbol)),is_local(local){

            }
        };

        /*Use an unordered set for constant lookup on find()*/
        std::unordered_set<unsigned long> function_declarations;

        std::vector<std::vector<VariableDeclaration>> variable_declarations_scopes;


    public:
        /*Check if a function was added to the function declaration list. Useful for finding duplicate
         * function declarations.*/
        bool functionExists(const Symbol&func_symbol) const;

        /*Add a new function declaration(its symbol) to the func declaration list*/
        void addFunction(const Symbol&func_symbol);

        /*Add a new variable declaration to the var declaratoin list*/
        void addVariable(const Symbol&var_symbol);

        /*Check if a variable was declared in the current scope. Useful for finding duplicate variable
         * declarations*/
        bool variableInCurrentScope(const Symbol& var_symbol) const;

        /*Set the location parameter to the variable location. If the variable was not found, return false*/
        bool getVariableLocation(const Symbol&var_symbol,VariableLocation&location) const;

        /*Create new scope for the variable declarations*/
        void pushScope();

        /*Pop the current variable declaration scope*/
        void popScope();

        /*Push a variable declaration scope by default*/
        DeclarationStack();

    };
}


#endif //INTERPRETER_DECLARATIONSTACK_H
