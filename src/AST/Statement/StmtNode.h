//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_STMTNODE_H
#define INTERPRETER_STMTNODE_H

#include "VM/Preprocess/FlowState.h"
#include "VM/Preprocess/DeclarationStack.h"
#include "VM/VirtualMachine.h"
#include "location.hh"
#include<vector>
#include"Error.h"

namespace AST {
    class StmtNode {
    protected:
        /*The location of the statement in the interpreted program*/
        yy::location location;

    public:
        /*Check if syntax errors regarding control flow are present.
         * Example: return statement outside function, break statement outside loop etc.
         * Add a syntax error to the list if it has  found control flow errors */
        virtual void checkControlFlow(VM::FlowState &state, std::vector<Error> &errors) const = 0;

        /*Report duplicate declarations of functions/variables , solve variable references.*/
        virtual void solveDeclarations(VM::DeclarationStack &stack, std::vector<Error> &error) = 0;

        virtual void emitBytecode(VM::VirtualMachine &vm, VM::BytecodeChunk &chunk) const = 0;

        explicit StmtNode(yy::location loc);

        virtual ~StmtNode() = default;

    };
}


#endif //INTERPRETER_STMTNODE_H
