//
// Created by gvisan on 09.09.2020.
//

#include "ReturnStmt.h"

namespace AST {
    ReturnStmt::ReturnStmt(yy::location loc) : StmtNode(loc), expression(nullptr) {

    }

    ReturnStmt::ReturnStmt(yy::location loc, std::unique_ptr<ExpNode> to_return) : StmtNode(loc),
                                                                                   expression(std::move(to_return)) {


    }


    void ReturnStmt::emitBytecode(VM::VirtualMachine &vm, VM::BytecodeChunk &chunk) const {
        if (expression != nullptr) {
            expression->emitBytecode(vm, chunk);
        } else {
            chunk.pushOpcode(VM::LOAD_LITERAL);
            chunk.pushUInt(0);//load null value
        }

        chunk.pushOpcode(VM::Opcode::RETURN_VALUE);

    }

    void ReturnStmt::solveDeclarations(VM::DeclarationStack &stack, std::vector<Error> &errors) {
        if (expression != nullptr) {
            expression->solveVarReferences(stack, errors);
        }
    }


    void ReturnStmt::checkControlFlow(VM::FlowState &state, std::vector<Error> &errors) const {
        if (!state.isInFunction())
            errors.emplace_back("semantic error, return statement outside function", location);
    }

}