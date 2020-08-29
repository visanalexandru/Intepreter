//
// Created by gvisan on 25.08.2020.
//

#ifndef INTERPRETER_WHILESTMT_H
#define INTERPRETER_WHILESTMT_H

#include "StmtNode.h"
#include "AST/Expression/ExpNode.h"
#include "AST/Context.h"
#include "CompoundStmt.h"

namespace AST {
    /*This class represents a while-loop in the interpreted program.
     *Execute the statements until the condition evaluates to false*/
    class WhileStmt:public StmtNode {
    private:
        std::unique_ptr<CompoundStmt> body;
        std::unique_ptr<ExpNode> condition;

    public:
        WhileStmt(yy::location loc,std::unique_ptr<ExpNode>cond,std::unique_ptr<CompoundStmt> stmts);

        void execute() override;

        void checkControlFlow(FlowState &state, std::vector<Error> &errors) const override;

        void solveDeclarations(DeclarationStack &stack, std::vector<Error> &errors) override;
    };
}


#endif //INTERPRETER_WHILESTMT_H
