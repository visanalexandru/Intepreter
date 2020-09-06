//
// Created by gvisan on 20.08.2020.
//

#include "SymbolTable.h"
namespace VM{
    SymbolTable globalSymtable;

    SymbolTable::SymbolTable() : num_symbols(0) {

    }

    Symbol SymbolTable::addSymbol(const std::string &symbol) {
        auto pair = map.insert(std::make_pair(symbol, num_symbols + 1));
        if (pair.second) {
            num_symbols++;
            return {symbol,num_symbols};
        } else return {symbol,map[symbol]};
    }

    bool SymbolTable::symbolExists(const std::string &symbol) const {
        return map.find(symbol) != map.end();
    }

    Symbol SymbolTable::getSymbol(const std::string &symbol) {
        if (symbolExists(symbol))
            return {symbol,map[symbol]};
        return {symbol,0};
    }

    unsigned SymbolTable::getNumSymbols() const {
        return num_symbols;
    }
}
