//
// Created by gvisan on 04.09.2020.
//

#include "FunctionCallExp.h"

namespace AST {

    FunctionCallExp::FunctionCallExp(yy::location location, std::unique_ptr<ExpNode> exp,
                                     std::vector<std::unique_ptr<ExpNode>> params) :
            ExpNode(location), expression(std::move(exp)), arguments(std::move(params)) {

    }


    void FunctionCallExp::solveVarReferences(VM::DeclarationStack &stack, std::vector<Error> &errors) {
        expression->solveVarReferences(stack,errors);

        for(const auto&argument:arguments){
            argument->solveVarReferences(stack,errors);
        }
    }


    void FunctionCallExp::emitBytecode(VM::VirtualMachine &vm, VM::BytecodeChunk &chunk) const {

        for(const auto&argument:arguments){
            argument->emitBytecode(vm,chunk);
        }

        expression->emitBytecode(vm,chunk);

        chunk.pushOpcode(VM::Opcode::FUNCTION_CALL);
        chunk.pushUInt(arguments.size());
    }
}