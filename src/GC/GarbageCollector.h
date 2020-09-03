//
// Created by gvisan on 02.09.2020.
//

#ifndef INTERPRETER_GARBAGECOLLECTOR_H
#define INTERPRETER_GARBAGECOLLECTOR_H
#include "Object.h"
#include<deque>
namespace GC{
    class GarbageCollector {
    private:
        Object*head;

        void addObj(Object*obj);
    public:
        GarbageCollector();

        Object*makeStringObj(std::string data);
    };

    extern GarbageCollector globalGc;
}


#endif //INTERPRETER_GARBAGECOLLECTOR_H
