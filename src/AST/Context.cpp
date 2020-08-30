//
// Created by gvisan on 12.08.2020.
//

#include "Context.h"

namespace AST {
    Context globalContext;
    Context::Context() {
        pushStackFrame();
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
        stack_frames.back().push_back(value);
    }

    void Context::popVar() {
        stack_frames.back().pop_back();
    }

    Value& Context::getVar(const AST::VariableLocation &location) {
        if(location.is_local){
            return stack_frames.back()[location.location_in_stack];
        }
        else{
            return stack_frames.front()[location.location_in_stack];
        }
    }

    void Context::pushStackFrame() {
        stack_frames.emplace_back();
    }

    void Context::popStackFrame() {
        stack_frames.pop_back();
    }
}