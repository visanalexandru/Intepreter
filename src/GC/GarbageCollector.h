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

        VM::Object*makeStringObj(std::string data);
    };

    extern GarbageCollector globalGc;
}


#endif //INTERPRETER_GARBAGECOLLECTOR_H
