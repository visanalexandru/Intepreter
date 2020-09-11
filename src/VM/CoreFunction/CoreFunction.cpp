//
// Created by gvisan on 04.09.2020.
//
#include "CoreFunction.h"
namespace VM{

    Value print(Value*ptr){
        std::cout<<"PRINT:"<<toString(*ptr)<<std::endl;
        return makeNullValue();
    }

    Value time(Value*ptr){
        double seconds= (double)(clock())/CLOCKS_PER_SEC;
        return makeFloatValue(seconds);
    }

}
