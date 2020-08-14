//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_STMTNODE_H
#define INTERPRETER_STMTNODE_H

#include "AST/Value/Value.h"

namespace AST {
    /*This class represents a statement in the interpreted program.
     *Classes like the declaration-statement,loops etc must derive from this class and implement the execute() method.
    */
    class StmtNode {
    private:
        /*The return value of the statement. This value is only used if in the called function a return statement occurs.
         *The value is then "propagated" upwards in the call stack.*/
        Value return_value;

        /*Flag to check if this statement or a sub-statement is a return statement*/
        bool has_returned;

        /*Sets the return_value and sets has_returned to true*/
        void setReturnValue(const Value &value);

    public:
        virtual void execute() = 0;

        /*Return the has_returned flag*/
        bool hasReturned() const;

        /*Return the return_value*/
        Value getReturnValue() const;

        StmtNode();

        virtual ~StmtNode() = default;

    };
}


#endif //INTERPRETER_STMTNODE_H