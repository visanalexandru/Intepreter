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

    VM::Object *GarbageCollector::makeStringObj(std::string data) {
        VM::StringObj *str = new VM::StringObj;
        str->header.type = VM::ObjectType::String;
        str->data = std::move(data);
        VM::Object *obj = (VM::Object *) str;
        addObj(obj);
        return (obj);
    }
}