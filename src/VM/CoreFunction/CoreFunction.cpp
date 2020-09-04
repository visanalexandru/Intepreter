//
// Created by gvisan on 04.09.2020.
//
#include "CoreFunction.h"
namespace VM{

    Value print(Value*ptr){
        std::cout<<toString(*ptr);
        return makeNullValue();
    }

}
