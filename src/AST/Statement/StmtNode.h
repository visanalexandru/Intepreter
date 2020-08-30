//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_STMTNODE_H
#define INTERPRETER_STMTNODE_H

#include "AST/Value/Value.h"
#include "AST/Preprocess/FlowState.h"
#include "AST/Preprocess/DeclarationStack.h"
#include "VirtualMachine/VirtualMachine.h"
#include "location.hh"
#include<vector>
#include"Error.h"

namespace AST {
    /*This class represents a statement in the interpreted program.
     *Classes like the declaration-statement,loops etc must derive from this class and implement the execute() method.
    */
    class StmtNode {
    protected:
        /*The return value of the statement. This value is only used if in the called function a return statement occurs.
         *The value is then "propagated" upwards in the call stack.*/
        Value return_value;

        /*Flag to check if this statement or a sub-statement is a return statement*/
        bool has_returned;

        /*Sets the return_value and sets has_returned to true*/
        void setReturnValue(const Value &value);

        /*The location of the statement in the interpreted program*/
        yy::location location;

        void resetReturnValue();

    public:
        virtual void execute() = 0;

        /*Return the has_returned flag*/
        bool hasReturned() const;

        /*Return the return_value*/
        Value getReturnValue() const;

        /*Check if syntax errors regarding control flow are present.
         * Example: return statement outside function, break statement outside loop etc.
         * Add a syntax error to the list if it has  found control flow errors */
        virtual void checkControlFlow(FlowState&state,std::vector<Error>&errors) const =0;


        /*Report duplicate declarations of functions/variables , solve variable references.*/
        virtual void solveDeclarations(DeclarationStack&stack,std::vector<Error>&error)=0;

        virtual void emitBytecode(VM::VirtualMachine&vm) const=0;

        explicit StmtNode(yy::location loc);

        virtual ~StmtNode() = default;

    };
}


#endif //INTERPRETER_STMTNODE_H
