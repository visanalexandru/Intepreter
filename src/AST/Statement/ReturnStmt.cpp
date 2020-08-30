//
// Created by gvisan on 16.08.2020.
//

#include "ReturnStmt.h"

namespace AST {

    ReturnStmt::ReturnStmt(yy::location loc,std::unique_ptr<ExpNode> to_return) :
    StmtNode(loc),
    expression(std::move(to_return)) {


    }

    ReturnStmt::ReturnStmt(yy::location loc) :
    StmtNode(loc),
    expression(nullptr) {

    }

    void ReturnStmt::execute() {
        resetReturnValue();
        if (expression != nullptr)
            setReturnValue(expression->evaluate());
        else setReturnValue(Value());
    }

    void ReturnStmt::checkControlFlow(FlowState &state,std::vector<Error>&errors) const {
        if(!state.isInFunction())
            errors.emplace_back("semantic error, return statement outside function",location);
    }

    void ReturnStmt::solveDeclarations(AST::DeclarationStack &stack, std::vector<Error> &errors) {
        if(expression!= nullptr)
            expression->solveVarReferences(stack,errors);
    }

    void ReturnStmt::emitBytecode(VM::VirtualMachine &vm) const {


    }

}