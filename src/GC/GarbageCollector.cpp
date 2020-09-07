//
// Created by gvisan on 02.09.2020.
//

#include "GarbageCollector.h"
#include<iostream>
namespace GC {
    GarbageCollector globalGc;
    GarbageCollector::GarbageCollector() : head(nullptr) {

    }

    void GarbageCollector::addObj(VM::Object *obj) {
        obj->previous = head;
        if (head != nullptr)
            head->next = obj;
        head = obj;
    }

    VM::StringObj*GarbageCollector::makeStringObj(std::string data) {
        auto *str = new VM::StringObj(std::move(data));
        addObj(str);
        return str;
    }

    VM::NativeFunctionObj* GarbageCollector::makeNativeFunctionObj(std::string name,unsigned arity,VM::Value (*func_ptr)(VM::Value *)) {
        auto * fn=new VM::NativeFunctionObj(std::move(name),arity,func_ptr);
        addObj(fn);
        return fn;
    }
}