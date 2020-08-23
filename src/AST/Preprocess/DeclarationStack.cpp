//
// Created by gvisan on 21.08.2020.
//

#include "DeclarationStack.h"

namespace AST {

    DeclarationStack::DeclarationStack() {
        push_scope();
    }

    void DeclarationStack::addFunction(const Symbol&func_symbol) {
        function_declarations.insert(func_symbol.symbol_id);
    }

    bool DeclarationStack::functionExists(const Symbol&func_symbol) const {
        return function_declarations.find(func_symbol.symbol_id) != function_declarations.end();
    }


    bool DeclarationStack::variableInCurrentScope(const Symbol&var_symbol ) const {
        return variable_declarations.back().find(var_symbol.symbol_id)!=variable_declarations.back().end();
    }

    void DeclarationStack::addVariable(const Symbol&var_symbol) {
        variable_declarations.back().insert(var_symbol.symbol_id);
    }

    void DeclarationStack::push_scope() {
        variable_declarations.emplace_back();
    }

    void DeclarationStack::pop_scope() {
        variable_declarations.pop_back();
    }

}