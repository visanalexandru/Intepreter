//
// Created by gvisan on 10.08.2020.
//
#include "Driver.h"
#include "AST/Value/Value.h"
int main(int argc,char**argv){
    Driver driver;
    int success=driver.parse("test.lang");
    if(success==0){
        std::cout<<"Parsing successful"<<std::endl;
        float a=clock();

        for(const auto&stmt : driver.result)
            stmt->execute();
        std::cout<<"Took "<<(clock()-a)/CLOCKS_PER_SEC<<std::endl;
    }
    return 0;
}