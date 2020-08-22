//
// Created by gvisan on 21.08.2020.
//

#include "DeclarationStack.h"

namespace AST {

    DeclarationStack::DeclarationStack() {
        push_scope();
    }

    void DeclarationStack::addFunction(unsigned long index) {
        function_declarations.insert(index);
    }

    bool DeclarationStack::functionExists(unsigned long index) const {
        return function_declarations.find(index) != function_declarations.end();
    }


    bool DeclarationStack::variableInCurrentScope(unsigned long index) const {
        return variable_declarations.back().find(index)!=variable_declarations.back().end();
    }

    void DeclarationStack::addVariable(unsigned long index) {
        variable_declarations.back().insert(index);
    }

    void DeclarationStack::push_scope() {
        variable_declarations.emplace_back();
    }

    void DeclarationStack::pop_scope() {
        variable_declarations.pop_back();
    }

}