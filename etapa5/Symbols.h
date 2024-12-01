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
#define DATATYPE_BOOL 11
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

        static std::string typeToString(u_int8_t type) {
            switch (type) {
                case SYMBOL_LIT_INT:
                    return "lit_int";
                case SYMBOL_LIT_STRING:
                    return "lit_string";
                case SYMBOL_LIT_CHAR:
                    return "lit_char";
                case SYMBOL_IDENTIFIER:
                    return "identifier";
                case SYMBOL_VARIABLE:
                    return "variable";
                case SYMBOL_FUNCTION:
                    return "function";
                case SYMBOL_VECTOR:
                    return "vector";
                case DATATYPE_INT:
                    return "int";
                case DATATYPE_CHAR:
                    return "char";
                case DATATYPE_NONE:
                    return "none";
                case DATATYPE_BOOL:
                    return "bool";
                default:
                    return "unknown";
            }
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
        Symbol* makeTemp();
        Symbol* makeLabel();


        Symbol get(std::string name);

        friend std::ostream& operator<<(std::ostream& os, const SymbolTable& table);
    private:
        std::map<std::string, Symbol> table;
};

#endif //SYMBOLS_H
