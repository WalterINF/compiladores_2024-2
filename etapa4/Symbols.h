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

//após verificação semântica, SYMBOL_IDENTIFIER é substituído por um dos seguintes
#define SYMBOL_VARIABLE 5
#define SYMBOL_FUNCTION 6
#define SYMBOL_VECTOR 7

#define DATATYPE_INT 8
#define DATATYPE_CHAR 9
#define DATATYPE_NONE 10

class Symbol {
    public:
        std::string name;
        int type;
        u_int8_t datatype;
        /* probably more data here in future steps */

        Symbol(char* name, int type) {
            this->name = std::string(name);
            this->type = type;
            this->datatype = 0;
        }

        void setDatatype(u_int8_t datatype) {
            this->datatype = datatype;
        }
};

class SymbolTable {
    public:
        SymbolTable() {}

        Symbol * insert(Symbol symbol);
        void print();
        void clear();
        int length();
        Symbol *symbolAt(int index);
        std::map<std::string, Symbol> getTable();

        Symbol get(std::string name);

        friend std::ostream& operator<<(std::ostream& os, const SymbolTable& table);
    private:
        std::map<std::string, Symbol> table;
};

#endif //SYMBOLS_H
