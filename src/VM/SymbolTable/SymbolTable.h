//
// Created by gvisan on 20.08.2020.
//

#ifndef INTERPRETER_SYMBOLTABLE_H
#define INTERPRETER_SYMBOLTABLE_H

#include<unordered_map>
#include<string>
#include "Symbol.h"

namespace VM{
/*This class is responsible for creating unique indexes for identifiers in the interpreted program.*/
/*So identifier strings are converted to integer indexes for speed*/
    class SymbolTable {
    private:
        /*A mapping between strings and their unique indexes*/
        std::unordered_map<std::string, unsigned> map;

        /*The number of symbols that were added*/
        unsigned num_symbols;

    public:
        /*Adds a new symbol and returns its index. If the symbol was already in the map,
         * return its index.*/
        Symbol addSymbol(const std::string &symbol);

        /*Check if a given symbol has already been added to the map*/
        bool symbolExists(const std::string &symbol) const;

        /*Returns the index of the given symbol. If the symbol was not added, return 0.*/
        Symbol getSymbol(const std::string &symbol);

        /*Returns the number of distinct symbols in the table*/
        unsigned getNumSymbols() const;

        SymbolTable();
    };

    extern SymbolTable globalSymtable;
}


#endif //INTERPRETER_SYMBOLTABLE_H
