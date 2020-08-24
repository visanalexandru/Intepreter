//
// Created by gvisan on 23.08.2020.
//

#ifndef INTERPRETER_VARIABLELOCATION_H
#define INTERPRETER_VARIABLELOCATION_H

namespace AST {
    struct VariableLocation {
        /*The index in the stack in which the variable exists*/
        unsigned long location_in_stack;//the index in the stack

        /*This offset is to be used only if the variable is local. Using this we can find the variable
         * by subtracting this value from the current stack index.*/
        unsigned long stack_offset;

        /*Is in a scope (a function or a block scope).*/
        bool is_local;

        VariableLocation(unsigned long location, unsigned long offset, bool local) : location_in_stack(location),stack_offset(offset), is_local(local) {

        }

        VariableLocation() : location_in_stack(0),stack_offset(0),is_local(false) {

        }
    };

}

#endif //INTERPRETER_VARIABLELOCATION_H
