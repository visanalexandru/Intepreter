//
// Created by gvisan on 02.09.2020.
//

#include "GarbageCollector.h"
#include<iostream>
namespace GC {
    GarbageCollector globalGc;
    GarbageCollector::GarbageCollector() : head(nullptr) {

    }

    void GarbageCollector::addObj(Object *obj) {
        obj->previous = head;
        if (head != nullptr)
            head->next = obj;
        head = obj;
    }

    Object *GarbageCollector::makeStringObj(std::string data) {
        StringObj *str = new StringObj;
        str->header.type = ObjectType::String;
        str->data = std::move(data);
        Object *obj = (Object *) str;
        addObj(obj);
        return (obj);
    }
}