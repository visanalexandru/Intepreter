//
// Created by gvisan on 02.09.2020.
//

#ifndef INTERPRETER_GARBAGECOLLECTOR_H
#define INTERPRETER_GARBAGECOLLECTOR_H
#include "VM/Value/Object.h"
#include<deque>
namespace GC{
    class GarbageCollector {
    private:
        VM::Object*head;

        void addObj(VM::Object*obj);
    public:
        GarbageCollector();

        VM::StringObj*makeStringObj(std::string data);

        VM::NativeFunctionObj*makeNativeFunctionObj(std::string name,unsigned arity,VM::Value(*func_ptr)(VM::Value*));
    };

    extern GarbageCollector globalGc;
}


#endif //INTERPRETER_GARBAGECOLLECTOR_H
