//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_ASSIGNMENTEXP_H
#define INTERPRETER_ASSIGNMENTEXP_H

#include"ExpNode.h"
#include"AST/Context.h"
#include "AST/Symbol.h"
namespace AST {
    /*This class represents an assignment in the interpreted program.
     * The evaluate() function will call assignValue() on the global context,
     * and will return the value of the expression.
     * This will help us make expressions like this a=b=c=exp;*/
    class AssignmentExp : public ExpNode {
    private:
        /*The symbol of the variable that needs to be assigned*/
        const Symbol symbol;

        /*The expression on the right of the assignment*/
        std::unique_ptr<ExpNode> exp;

    public:
        AssignmentExp(Symbol sym, std::unique_ptr<ExpNode> value);

        Value evaluate() const override;
    };
}


#endif //INTERPRETER_ASSIGNMENTEXP_H
