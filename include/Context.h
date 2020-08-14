//
// Created by gvisan on 12.08.2020.
//

#ifndef INTERPRETER_CONTEXT_H
#define INTERPRETER_CONTEXT_H

#include<unordered_map>
#include<deque>
#include<string>
#include "Value.h"

namespace AST {
    /*This class manages scopes and function definitions*/
    class Context {
    private:
        std::deque<std::unordered_map<std::string, Value> *> scopes;

        /*Returns a pointer to the scope of a variable referenced by name
         * The search is made "upwards", from the current scope to the base scope
         * If no scope was found that contains the variable, return nullptr .*/
        std::unordered_map<std::string, Value> *findScopeOf(const std::string &varname);

        /*Returns a pointer to the current scope*/
        std::unordered_map<std::string, Value> *getCurrentScope();

    public:
        Context();

        /*Will destroy all the active scopes*/
        ~Context();

        /*Declare a variable in this scope and assign its value
         *If the variable has been declared in this scope already, throw an exception*/
        void declareVar(const std::string &name, const Value &value);

        /*Get the value of the variable. Will call findScopeOf() function
         * Throw an exception if the variable has not been found*/
        Value getVar(const std::string &name);

        /*Assign the value of the variable. Will call findScopeOf() function*/
        void setVar(const std::string &name, const Value &value);

        /*Creates a new scope and pushes it to the scope list*/
        void pushScope();

        /*Deletes the current scope and removes it from the scope list
         *Calling this function when there is no scope in the list is undefined*/
        void popScope();
    };

    /*The global context of the interpreted program
     *Function calls,assignments etc will refer to this variable*/
    extern Context globalContext;

}


#endif //INTERPRETER_CONTEXT_H
