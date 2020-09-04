//
// Created by gvisan on 14.08.2020.
//

#include "VariableExp.h"

namespace AST {

    VariableExp::VariableExp(yy::location loc, VM::Symbol sym) : ExpNode(loc), symbol(std::move(sym)), assign(nullptr) {


    }

    VariableExp::VariableExp(yy::location loc, VM::Symbol sym, std::unique_ptr<ExpNode> to_assign) : ExpNode(loc),
                                                                                                 symbol(std::move(sym)),
                                                                                                 assign(std::move(to_assign)){

    }

    void VariableExp::solveVarReferences(VM::DeclarationStack &stack, std::vector<Error> &errors) {
        if (!stack.getVariableLocation(symbol, var_location))
            errors.emplace_back("semantic error, variable is not declared: " + symbol.symbol_name, location);
        if(assign!=nullptr)
            assign->solveVarReferences(stack,errors);
    }

    void VariableExp::emitBytecode(VM::VirtualMachine &vm,VM::BytecodeChunk&chunk) const {
        if (assign != nullptr) {
            assign->emitBytecode(vm,chunk);
            if (var_location.is_local)
                chunk.pushOpcode(VM::Opcode::ASSIGN_LOCAL);
            else chunk.pushOpcode(VM::Opcode::ASSIGN_GLOBAL);

        } else {
            if (var_location.is_local)
                chunk.pushOpcode(VM::Opcode::LOAD_LOCAL);
            else chunk.pushOpcode(VM::Opcode::LOAD_GLOBAL);
        }
        chunk.pushUInt(var_location.location_in_stack);
    }
}