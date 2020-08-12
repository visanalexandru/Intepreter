//
// Created by gvisan on 10.08.2020.
//
#include "Driver.h"
#include "Value.h"
int main(int argc,char**argv){
    Driver driver;
    int success=driver.parse("test.lang");
    if(success==0){
        std::cout<<"Parsing successful"<<std::endl;
        float a=clock();
        std::cout<<(driver.result->evaluate()).toString()<<std::endl;
        std::cout<<"Took "<<(clock()-a)/CLOCKS_PER_SEC<<std::endl;
    }
    return 0;
}