/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
*/

#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <iostream>
#include <map>
#include <string>

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_STRING 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_IDENTIFIER 4

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

class SymbolTable {
    public:
        SymbolTable() {}

        void insert(Symbol symbol);
        void print();
        void clear();

        Symbol get(std::string name);

        friend std::ostream& operator<<(std::ostream& os, const SymbolTable& table);
    private:
        std::map<std::string, Symbol> table;
};

#endif //SYMBOLS_H
