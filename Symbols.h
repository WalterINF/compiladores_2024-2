/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
*/

#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <iostream>
#include <map>
#include <string>

class Symbol {
    public:
        std::string name;
        int type;
        /* probably more data here in future steps */

        Symbol(char* name, int type) {
            this->name = std::string(name);
            this->type = type;
        }
};

void insertSymbol(std::map<std::string, Symbol> *table, Symbol symbol);
void printSymbols(std::map<std::string, Symbol> table);

#endif //SYMBOLS_H
