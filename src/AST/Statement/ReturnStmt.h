//
// Created by gvisan on 09.09.2020.
//

#ifndef INTERPRETER_RETURNSTMT_H
#define INTERPRETER_RETURNSTMT_H
#include "StmtNode.h"
#include "AST/Expression/ExpNode.h"
namespace AST{
    /*This class represents a return statement in the interpreted program*/
    class ReturnStmt: public StmtNode {
    private:
        /*To return*/
        std::unique_ptr<ExpNode> expression;
    public:
        explicit ReturnStmt(yy::location loc);

        ReturnStmt(yy::location loc,std::unique_ptr<ExpNode> to_return);

        /*Report return outside function*/
        void checkControlFlow(VM::FlowState&state,std::vector<Error>&errors) const override;

        void emitBytecode(VM::VirtualMachine&vm,VM::BytecodeChunk&chunk) const override;

        void solveDeclarations(VM::DeclarationStack&stack,std::vector<Error>&errors)override ;

    };
}


#endif //INTERPRETER_RETURNSTMT_H
