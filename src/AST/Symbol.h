//
// Created by gvisan on 21.08.2020.
//

#ifndef INTERPRETER_SYMBOL_H
#define INTERPRETER_SYMBOL_H

#include<string>
#include<iostream>
namespace AST {
    /*This struct represents a identifier in the interpreted program. It contains the identifier name, and an
     * identifier index. If 2 identifiers have the same name, they have the same index. This is just for optimization,
     * so we can compare 2 symbols using their id rather than their name.*/
    struct Symbol {
        std::string symbol_name;

        unsigned long symbol_id;

        Symbol():symbol_name(),symbol_id(0){

        }

        Symbol(std::string name, unsigned long id):symbol_name(std::move(name)),symbol_id(id){

        }
    };
}


#endif //INTERPRETER_SYMBOL_H
