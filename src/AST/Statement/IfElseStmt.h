//
// Created by gvisan on 19.08.2020.
//

#ifndef INTERPRETER_IFELSESTMT_H
#define INTERPRETER_IFELSESTMT_H

#include <memory>
#include"StmtNode.h"
#include "AST/Expression/ExpNode.h"
#include "AST/Context.h"

namespace AST {
    /*This class represents an if-else-statement in the interpreted language.*/
    /*Calling execute() will evaluate the condition expression, create a new scope and execute the block
     *that is required (if the exp evaluated to true, execute the first block, else execute the second block) */
    class IfElseStmt : public StmtNode {
    private:
        std::unique_ptr<ExpNode> condition;
        std::vector<std::unique_ptr<StmtNode>> ifblock;
        std::vector<std::unique_ptr<StmtNode>> elseblock;

    public:
        IfElseStmt(yy::location loc, std::unique_ptr<ExpNode> cond, std::vector<std::unique_ptr<StmtNode>> ifstmts);

        IfElseStmt(yy::location loc, std::unique_ptr<ExpNode> cond, std::vector<std::unique_ptr<StmtNode>> ifstmts,
                   std::vector<std::unique_ptr<StmtNode>> elsestmts);

        void execute() override;

        void checkControlFlow(FlowState&state,std::vector<Error>&errors) const override;

        void checkDeclarations(DeclarationStack&stack,std::vector<Error>&errors) const override ;
    };
}


#endif //INTERPRETER_IFELSESTMT_H
