//
// Created by gvisan on 20.08.2020.
//

#include "SymbolTable.h"
namespace AST {
    SymbolTable globalSymtable;

    SymbolTable::SymbolTable() : num_symbols(0) {

    }

    unsigned long SymbolTable::addSymbol(const std::string &symbol) {
        auto pair = map.insert(std::make_pair(symbol, num_symbols + 1));
        if (pair.second) {
            num_symbols++;
            return num_symbols;
        } else return map[symbol];
    }

    bool SymbolTable::symbolExists(const std::string &symbol) const {
        return map.find(symbol) != map.end();
    }

    unsigned long SymbolTable::getSymbolIndex(const std::string &symbol) {
        if (symbolExists(symbol))
            return map[symbol];
        return 0;
    }
}
