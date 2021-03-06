//
// Created by gvisan on 16.08.2020.
//

#ifndef INTERPRETER_RETURNSTMT_H
#define INTERPRETER_RETURNSTMT_H

#include<memory>
#include "AST/Expression/ExpNode.h"
#include "StmtNode.h"

namespace AST {
    /*This class represents a return statement in a function in the interpreted program.
     *Execute() will call the setReturnValue() function that will set the has_returned flag.
     *Each statement that contains a return statement should propagate it upwards using the setReturnValue() function*/
    class ReturnStmt : public StmtNode {
    private:
        //Return the value of the expression;
        std::unique_ptr<ExpNode> expression;

    public:
        /*Returns the value of the expression*/
        ReturnStmt(yy::location loc,std::unique_ptr<ExpNode> to_return);

        /*Returns None*/
        explicit ReturnStmt(yy::location loc);

        void execute() override;

        /*Throws exception if the return statement is out of a function declaration*/
        void checkControlFlow(FlowState&state,std::vector<Error>&errors) const override;

        void solveDeclarations(DeclarationStack&stack,std::vector<Error>&errors) override;
    };

}


#endif //INTERPRETER_RETURNSTMT_H
