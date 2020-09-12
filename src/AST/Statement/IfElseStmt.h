//
// Created by gvisan on 19.08.2020.
//

#ifndef INTERPRETER_IFELSESTMT_H
#define INTERPRETER_IFELSESTMT_H

#include <memory>
#include"StmtNode.h"
#include "AST/Expression/ExpNode.h"
#include"CompoundStmt.h"

namespace AST {
    /*This class represents an if-else-statement in the interpreted language.*/
    class IfElseStmt : public StmtNode {
    private:
        /*Condition to be evaluated*/
        std::unique_ptr<ExpNode> condition;

        std::unique_ptr<CompoundStmt> ifbranch;
        std::unique_ptr<CompoundStmt> elsebranch;

    public:
        IfElseStmt(yy::location loc, std::unique_ptr<ExpNode> cond, std::unique_ptr<StmtNode> ifb,std::unique_ptr<StmtNode>elseb= nullptr);

        void checkControlFlow(VM::FlowState&state,std::vector<Error>&errors) const override;

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;

        /*Solve declarations for the condition and the 2 branches*/
        void solveDeclarations(VM::DeclarationStack&stack,std::vector<Error>&errors)override ;
    };
}


#endif //INTERPRETER_IFELSESTMT_H
