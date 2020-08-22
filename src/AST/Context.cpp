//
// Created by gvisan on 12.08.2020.
//

#include "Context.h"

namespace AST {
    Context globalContext;
    Context::Context() {
        pushScope();
    }

    std::unordered_map<unsigned long, Value> *Context::findScopeOf(unsigned long varsymbol) {
        for (auto it = scopes.rbegin(); it != scopes.rend(); it++) {
            std::unordered_map<unsigned long, Value>&scope = *it;
            if (scope.find(varsymbol) != scope.end())
                return &scope;
        }
        return nullptr;
    }

    void Context::declareVar(unsigned long varsymbol, const Value &value) {
        assert(scopes.back().insert(std::make_pair(varsymbol, value)).second);
    }

    bool Context::isVarDeclared(unsigned long varsymbol) {
        return findScopeOf(varsymbol)!= nullptr;
    }

    bool Context::isFuncDeclared(unsigned long funcsymbol) {
        return functions.find(funcsymbol)!=functions.end();
    }

    void Context::declareFunc(unsigned long funcsymbol, std::unique_ptr<Function> function) {
        assert(functions.insert(std::make_pair(funcsymbol, std::move(function))).second);
    }

    void Context::setVar(unsigned long varsymbol, const AST::Value &value) {
        std::unordered_map<unsigned long , Value> *scope = findScopeOf(varsymbol);
        assert(scope!= nullptr);
        (*scope)[varsymbol] = value;
    }

    Value Context::getVar(unsigned long varsymbol) {
        std::unordered_map<unsigned long , Value> *scope = findScopeOf(varsymbol);
        assert(scope!= nullptr);
        return (*scope)[varsymbol];
    }

    const std::unique_ptr<Function>&Context::getFunc(unsigned long funcsymbol) {
        assert(isFuncDeclared(funcsymbol));
        return functions[funcsymbol];
    }

    void Context::pushScope() {
        scopes.emplace_back();
    }

    void Context::popScope() {
        scopes.pop_back();
    }
}