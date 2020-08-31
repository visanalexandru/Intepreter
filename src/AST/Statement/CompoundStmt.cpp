//
// Created by gvisan on 28.08.2020.
//

#include "CompoundStmt.h"

namespace AST {

    CompoundStmt::CompoundStmt(yy::location loc, std::vector<std::unique_ptr<StmtNode>> stmts) :
            StmtNode(loc), statements(std::move(stmts)),to_pop(0) {


    }

    void CompoundStmt::execute() {
        resetReturnValue();
        for(const auto&stmt:statements){
            stmt->execute();
            if(stmt->hasReturned()){
                setReturnValue(stmt->getReturnValue());
                break;
            }
        }
        for(unsigned i=0;i<to_pop;i++)
            globalContext.popVar();
    }

    void CompoundStmt::checkControlFlow(FlowState &state, std::vector<Error> &errors) const {
        for(const auto&stmt:statements){
            stmt->checkControlFlow(state,errors);
        }
    }

    void CompoundStmt::solveDeclarations(DeclarationStack &stack, std::vector<Error> &errors) {
        stack.pushScope();
        for(const auto&stmt:statements){
            stmt->solveDeclarations(stack,errors);
        }
        to_pop=stack.variablesInScope();
        stack.popScope();
    }

    std::vector<std::unique_ptr<StmtNode>> & CompoundStmt::getStatements() {
        return statements;
    }

    void CompoundStmt::emitBytecode(VM::VirtualMachine &vm,VM::BytecodeChunk&chunk) const {
        for(const auto&stmt:statements){
            stmt->emitBytecode(vm,chunk);
        }
        for(int i=0;i<to_pop;i++){
            chunk.pushOpcode(VM::Opcode::POP);
        }
    }
}