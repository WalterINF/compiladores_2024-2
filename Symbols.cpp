//
// Created by walter on 08/10/24.
//

#include "Symbols.h"

void insertSymbol(std::map<std::string, int> *table,std::string symbol, int type){
  table->insert(std::make_pair(symbol, type));
}

void printSymbols(std::map<std::string, int> table){
    for (const auto& pair : table) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}