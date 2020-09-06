//
// Created by gvisan on 21.08.2020.
//

#include "DeclarationStack.h"
#include<iostream>

namespace VM{

    DeclarationStack::DeclarationStack() {
        pushStackFrame();
    }

    bool DeclarationStack::variableInCurrentScope(const Symbol &var_symbol) const {
        const auto &current_stack_frame = stack_frames.back();

        for (const VariableDeclaration &declaration :current_stack_frame.declarations)
            if (declaration.variable_symbol.symbol_id == var_symbol.symbol_id &&
                declaration.scope_depth == current_stack_frame.scope_depth)
                return true;
        return false;
    }

    bool DeclarationStack::getVariableLocation(const Symbol &var_symbol, VariableLocation &location) const {
        const auto &current_stack_frame = stack_frames.back().declarations;

        for (auto iter = current_stack_frame.rbegin(); iter != current_stack_frame.rend(); iter++) {
            if (iter->variable_symbol.symbol_id == var_symbol.symbol_id) {
                unsigned index = current_stack_frame.rend() - iter-1;
                location = {index, true};
                return true;
            }
        }
        if (stack_frames.size() > 1) {//This is not the global stack frame
            /*We didn't find the declaration in the current stack frame, search for globals;*/
            const auto &global_stack_frame = stack_frames[0].declarations;
            for (auto iter = global_stack_frame.rbegin(); iter != global_stack_frame.rend(); iter++) {
                if (iter->variable_symbol.symbol_id == var_symbol.symbol_id) {
                    unsigned index = global_stack_frame.rend() - iter-1;
                    location = {index, false};
                    return true;
                }
            }
        }
        return false;
    }

    void DeclarationStack::addVariable(const Symbol &var_symbol) {
        stack_frames.back().declarations.emplace_back(var_symbol, stack_frames.back().scope_depth);
    }

    void DeclarationStack::pushScope() {
        stack_frames.back().scope_depth++;
    }

    void DeclarationStack::popScope() {
        unsigned depth = stack_frames.back().scope_depth;
        auto&current_stack_frame=stack_frames.back().declarations;
        while (!current_stack_frame.empty()&&current_stack_frame.back().scope_depth==depth){
            current_stack_frame.pop_back();
        }
        stack_frames.back().scope_depth--;
    }

    unsigned DeclarationStack::variablesInScope() const {
        unsigned result=0;
        unsigned depth = stack_frames.back().scope_depth;
        auto&current_stack_frame=stack_frames.back().declarations;
        for(const VariableDeclaration&declaration:current_stack_frame){
            if(declaration.scope_depth==depth)
                result++;
        }
        return result;
    }

    void DeclarationStack::pushStackFrame() {
        stack_frames.emplace_back();
    }

    void DeclarationStack::popStackFrame() {
        stack_frames.pop_back();
    }
}