//
// Created by gvisan on 21.08.2020.
//

#include "DeclarationStack.h"
#include<iostream>

namespace AST {

    DeclarationStack::DeclarationStack() {
        pushScope();
    }

    void DeclarationStack::addFunction(const Symbol &func_symbol) {
        function_declarations.insert(func_symbol.symbol_id);
    }

    bool DeclarationStack::functionExists(const Symbol &func_symbol) const {
        return function_declarations.find(func_symbol.symbol_id) != function_declarations.end();
    }


    bool DeclarationStack::variableInCurrentScope(const Symbol &var_symbol) const {
        const auto &current_scope = variable_declarations_scopes.back();

        for (const VariableDeclaration &declaration :current_scope)
            if (declaration.variable_symbol.symbol_id == var_symbol.symbol_id)
                return true;
        return false;
    }

    bool DeclarationStack::getVariableLocation(const Symbol &var_symbol, VariableLocation &location) const {
        unsigned long scope_offset=0;
        for (auto iter = variable_declarations_scopes.rbegin(); iter != variable_declarations_scopes.rend(); iter++) {
            const std::vector<VariableDeclaration> &scope = *iter;

            for (auto decl = scope.begin(); decl != scope.end(); decl++) {
                if (decl->variable_symbol.symbol_id == var_symbol.symbol_id) {
                    unsigned long index = decl - scope.begin();
                    location = {index,scope_offset,decl->is_local};
                    return true;
                }
            }
            scope_offset++;
        }
        return false;
    }

    void DeclarationStack::addVariable(const Symbol &var_symbol) {
        std::vector<VariableDeclaration>&current_scope = variable_declarations_scopes.back();
        VariableDeclaration declaration{var_symbol, variable_declarations_scopes.size() > 1};
        current_scope.push_back(declaration);
    }

    void DeclarationStack::pushScope() {
        variable_declarations_scopes.emplace_back();
    }

    void DeclarationStack::popScope() {
        variable_declarations_scopes.pop_back();
    }

}