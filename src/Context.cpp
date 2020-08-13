//
// Created by gvisan on 12.08.2020.
//

#include "Context.h"

namespace AST {
    Context::Context() {
        pushScope();
    }

    Context::~Context() {
        while (!scopes.empty())
            popScope();
    }

    std::unordered_map<std::string, Value> *Context::getCurrentScope() {
        return scopes.back();
    }


    std::unordered_map<std::string, Value> *Context::findScopeOf(const std::string &varname) {
        for (auto it = scopes.rbegin(); it != scopes.rend(); it++) {
            std::unordered_map<std::string, Value> *scope = *it;
            if (scope->find(varname) != scope->end())
                return scope;
        }
        return nullptr;
    }

    void Context::declareVar(const std::string &name, const Value &value) {
        auto current_scope = getCurrentScope();
        if (current_scope->find(name) != current_scope->end())
            throw std::runtime_error("Variable has already been declared in this scope: " + name);
        current_scope->insert(std::make_pair(name, value));
    }

    void Context::setVar(const std::string &name, const AST::Value &value) {
        std::unordered_map<std::string, Value> *scope = findScopeOf(name);
        if (scope == nullptr)
            throw std::runtime_error("Variable has not been declared: " + name);
        (*scope)[name] = value;
    }

    Value Context::getVar(const std::string &name) {
        std::unordered_map<std::string, Value> *scope = findScopeOf(name);
        if (scope == nullptr)
            throw std::runtime_error("Variable has not been declared: " + name);
        return (*scope)[name];
    }

    void Context::pushScope() {
        scopes.push_back(new std::unordered_map<std::string, Value>());
    }

    void Context::popScope() {
        delete getCurrentScope();
        scopes.pop_back();
    }
}