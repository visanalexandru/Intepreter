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
        bool inLoop;
        bool inFunction;
    public:
        FlowState();

        void enterLoop();

        void exitLoop();

        void enterFunction();

        void exitFunction();

        bool isInLoop() const;

        bool isInFunction() const;
    };


}


#endif //INTERPRETER_FLOWSTATE_H
