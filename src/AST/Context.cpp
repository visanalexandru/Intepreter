//
// Created by gvisan on 12.08.2020.
//

#include "Context.h"

namespace AST {
    Context globalContext;
    Context::Context() {
        pushScope();
    }

    bool Context::isFuncDeclared(const Symbol&funcsymbol) {
        return functions.find(funcsymbol.symbol_id)!=functions.end();
    }

    void Context::declareFunc(const Symbol& funcsymbol, std::unique_ptr<Function> function) {
        bool result=functions.insert(std::make_pair(funcsymbol.symbol_id, std::move(function))).second;
        assert(result);
    }

    const std::unique_ptr<Function>&Context::getFunc(const Symbol& funcsymbol) {
        assert(isFuncDeclared(funcsymbol));
        return functions[funcsymbol.symbol_id];
    }

    void Context::pushVar(const AST::Value &value) {
        scopes.back().push_back(value);
    }

    Value& Context::getVar(const AST::VariableLocation &location) {
        if(location.is_local){
            return scopes[scopes.size()-location.stack_offset-1][location.location_in_stack];
        }
        else{
            return scopes[0][location.location_in_stack];
        }
    }

    void Context::pushScope() {
        scopes.emplace_back();
    }

    void Context::popScope() {
        scopes.pop_back();
    }
}