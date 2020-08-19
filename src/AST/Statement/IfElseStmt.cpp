//
// Created by gvisan on 19.08.2020.
//

#include "IfElseStmt.h"

namespace AST {

    IfElseStmt::IfElseStmt(yy::location loc, std::unique_ptr<ExpNode> cond,
                           std::vector<std::unique_ptr<StmtNode>> ifstmts,
                           std::vector<std::unique_ptr<StmtNode>> elsestmts) :
            StmtNode(loc),
            condition(std::move(cond)),
            ifblock(std::move(ifstmts)),
            elseblock(std::move(elsestmts)) {


    }

    IfElseStmt::IfElseStmt(yy::location loc, std::unique_ptr<ExpNode> cond,
                           std::vector<std::unique_ptr<StmtNode>> ifstmts) :
            StmtNode(loc),
            condition(std::move(cond)),
            ifblock(std::move(ifstmts)),
            elseblock() {

    }

    void IfElseStmt::execute() {
        resetReturnValue();

        std::vector<std::unique_ptr<StmtNode>>* to_execute;
        if(condition->evaluate().toBoolObj().asBool()){
            to_execute=&ifblock;
        }
        else {
            to_execute=&elseblock;
        }

        globalContext.pushScope();
        for(const auto& stmt:*to_execute){
            stmt->execute();
            if(stmt->hasReturned()){
                setReturnValue(stmt->getReturnValue());
                break;
            }
        }
        globalContext.popScope();
    }

    void IfElseStmt::checkControlFlow(AST::FlowState &state, std::vector<Error> &errors) const {
        for(const auto&stmt:ifblock)
            stmt->checkControlFlow(state,errors);
        for(const auto&stmt:elseblock)
            stmt->checkControlFlow(state,errors);
    }


}