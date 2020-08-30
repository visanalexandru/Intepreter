//
// Created by gvisan on 14.08.2020.
//

#include "VarDeclarationStmt.h"

namespace AST {

    VarDeclarationStmt::VarDeclarationStmt(yy::location loc, Symbol sym) :
            StmtNode(loc),
            symbol(std::move(sym)), value(nullptr) {


    }

    VarDeclarationStmt::VarDeclarationStmt(yy::location loc, Symbol sym, std::shared_ptr<ExpNode> exp) :
            StmtNode(loc),
            symbol(std::move(sym)),
            value(std::move(exp)) {

    }

    void VarDeclarationStmt::execute() {
        if (value != nullptr) {
            globalContext.pushVar(value->evaluate());
        } else {
            globalContext.pushVar(Value());
        }
    }

    void VarDeclarationStmt::solveDeclarations(AST::DeclarationStack &stack, std::vector<Error> &errors) {
        if(value!= nullptr)
            value->solveVarReferences(stack,errors);

        if(stack.variableInCurrentScope(symbol))
            errors.emplace_back("semantic error, duplicate declaration of variable "+symbol.symbol_name,location);
        else stack.addVariable(symbol);
    }

    void VarDeclarationStmt::emitBytecode(VM::VirtualMachine &vm) const {
        if(value!= nullptr){
            value->emitBytecode(vm);
        }
        else{
            unsigned literal_count=vm.getLiteralCount();
            vm.pushLiteral(Value());
            vm.pushOpcode(VM::Opcode::LOAD_LITERAL);
            vm.pushUInt(literal_count);
        }
    }
}