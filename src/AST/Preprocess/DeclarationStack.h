//
// Created by gvisan on 21.08.2020.
//

#ifndef INTERPRETER_DECLARATIONSTACK_H
#define INTERPRETER_DECLARATIONSTACK_H

#include<memory>
#include<unordered_set>
#include<vector>
#include<algorithm>
#include "AST/Symbol.h"
#include "VariableLocation.h"

namespace AST {
    /*Useful for resolving variables.*/
    class DeclarationStack {
    private:

        struct VariableDeclaration {
            Symbol variable_symbol;

            unsigned long scope_depth;

            VariableDeclaration(Symbol symbol, unsigned long depth) : variable_symbol(std::move(symbol)),
                                                                      scope_depth(depth) {
            }
        };

        struct StackFrame {
            unsigned long scope_depth;

            std::vector<VariableDeclaration> declarations;

            StackFrame() : scope_depth(0) {

            }

        };

        std::vector<StackFrame> stack_frames;


    public:
        /*Add a new stack frame to the list*/
        void pushStackFrame();

        /*Remove the current stack frame*/
        void popStackFrame();

        /*Add a new variable declaration to the current stack frame*/
        void addVariable(const Symbol &var_symbol);

        /*Check if a variable was declared in the current scope. Useful for finding duplicate variable
         * declarations*/
        bool variableInCurrentScope(const Symbol &var_symbol) const;

        /*Returns the number of variables in the current scope.*/
        unsigned long variablesInScope() const;

        /*Set the location parameter to the variable location. If the variable was not found, return false*/
        bool getVariableLocation(const Symbol &var_symbol, VariableLocation &location) const;

        /*Increments scope_depth in the current stack frame. */
        void pushScope();

        /*Decrements scope_depth in the current stack frame.*/
        void popScope();

        /*Push a variable declaration scope by default*/
        DeclarationStack();

    };
}


#endif //INTERPRETER_DECLARATIONSTACK_H
