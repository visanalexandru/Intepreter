//
// Created by gvisan on 18.08.2020.
//

#ifndef INTERPRETER_FLOWSTATE_H
#define INTERPRETER_FLOWSTATE_H

/*This class is useful for checking control flow analysis (break statements only allowed in loops,return statements
 * only allowed in functions etc.)*/
namespace AST{

    class FlowState {
    private:
        /*Check if the control flow check is currently in a loop,useful for loop-control statements*/
        bool inLoop;
        /*Check if the control flow check is currently in a function,useful for return statements*/
        bool inFunction;
    public:
        FlowState();

        /*Sets inLoop to true*/
        void enterLoop();

        /*Sets inLoop to false*/
        void exitLoop();

        /*Sets inFunction to true*/
        void enterFunction();

        /*Sets inFunction to false*/
        void exitFunction();

        /*Returns inLoop*/
        bool isInLoop() const;

        /*Returns inFunction*/
        bool isInFunction() const;
    };


}


#endif //INTERPRETER_FLOWSTATE_H
