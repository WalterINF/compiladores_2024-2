/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
 */

//
// Created by walter on 08/10/24.
//

#include "Symbols.h"

void insertSymbol(std::map<std::string, int> *table,char* symbol, int type){
    std::string input = std::string(symbol);
    table->insert(std::make_pair(input, type));
}

void printSymbols(std::map<std::string, int> table){
    for (const auto& pair : table) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}