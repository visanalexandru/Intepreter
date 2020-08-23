//
// Created by gvisan on 12.08.2020.
//

#include "Context.h"

namespace AST {
    Context globalContext;
    Context::Context() {
        pushScope();
    }

    std::unordered_map<unsigned long, Value> *Context::findScopeOf(const Symbol&varsymbol) {
        for (auto it = scopes.rbegin(); it != scopes.rend(); it++) {
            std::unordered_map<unsigned long, Value>&scope = *it;
            if (scope.find(varsymbol.symbol_id) != scope.end())
                return &scope;
        }
        return nullptr;
    }

    void Context::declareVar(const Symbol&varsymbol, const Value &value) {
        assert(scopes.back().insert(std::make_pair(varsymbol.symbol_id, value)).second);
    }

    bool Context::isVarDeclared(const Symbol&varsymbol) {
        return findScopeOf(varsymbol)!= nullptr;
    }

    bool Context::isFuncDeclared(const Symbol&funcsymbol) {
        return functions.find(funcsymbol.symbol_id)!=functions.end();
    }

    void Context::declareFunc(const Symbol& funcsymbol, std::unique_ptr<Function> function) {
        assert(functions.insert(std::make_pair(funcsymbol.symbol_id, std::move(function))).second);
    }

    void Context::setVar(const Symbol& varsymbol, const AST::Value &value) {
        std::unordered_map<unsigned long , Value> *scope = findScopeOf(varsymbol);
        assert(scope!= nullptr);
        (*scope)[varsymbol.symbol_id] = value;
    }

    Value Context::getVar(const Symbol& varsymbol) {
        std::unordered_map<unsigned long , Value> *scope = findScopeOf(varsymbol);
        assert(scope!= nullptr);
        return (*scope)[varsymbol.symbol_id];
    }

    const std::unique_ptr<Function>&Context::getFunc(const Symbol& funcsymbol) {
        assert(isFuncDeclared(funcsymbol));
        return functions[funcsymbol.symbol_id];
    }

    void Context::pushScope() {
        scopes.emplace_back();
    }

    void Context::popScope() {
        scopes.pop_back();
    }
}