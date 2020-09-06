//
// Created by gvisan on 23.08.2020.
//

#ifndef INTERPRETER_VARIABLELOCATION_H
#define INTERPRETER_VARIABLELOCATION_H

namespace VM{
    struct VariableLocation {
        /*The index in frame stack in which the variable exists*/
        unsigned location_in_stack;

        /*If is local, search for the variable in the current stack frame, else search in the global stack frame*/
        bool is_local;

        VariableLocation(unsigned location, bool local) : location_in_stack(location), is_local(local) {

        }

        VariableLocation() : location_in_stack(0),is_local(false) {

        }
    };

}

#endif //INTERPRETER_VARIABLELOCATION_H
