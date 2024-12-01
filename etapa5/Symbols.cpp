/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
*/

#include "Symbols.h"

#include <Semantic.h>

/* Inserts a Symbol object into the table */
Symbol *SymbolTable::insert(Symbol symbol) {
    table.insert(std::pair<std::string, Symbol>(symbol.name.append("_"), symbol));
    auto it = table.find(symbol.name);
    if (it != table.end()) {
        return &it->second;
    }
    throw std::runtime_error("Symbol not found");
}

/* Prints the table */
void SymbolTable::print() {
    for (const auto& pair : table) {
        fprintf(stdout, "%s : %d\n", pair.first.c_str(), pair.second.type);
    }
}

/* Returns a Symbol object from the table */
Symbol SymbolTable::get(std::string name) {
    auto it = table.find(name.append("_"));
    if (it != table.end()) {
        return it->second;
    }
    throw std::runtime_error("Symbol not found");
}

/* Clears the table */
void SymbolTable::clear() {
    table.clear();
}

int SymbolTable::length() {
    return table.size();
}

std::map<std::string, Symbol> SymbolTable::getTable() {
    return table;
}


/* Overloads the << operator to print the table */
std::ostream& operator<<(std::ostream& os, const SymbolTable& table) {
    for (const auto& pair : table.table) {
        os << pair.first << " : " << pair.second.type << std::endl;
    }
    return os;
}

Symbol *SymbolTable::makeTemp() {
    static int serial = 0;
    char *buffer = "";
    sprintf(buffer,"temp%d",serial++);
    table.insert(std::pair<std::string, Symbol>(buffer, Symbol{buffer,SYMBOL_VARIABLE}));
    auto it = table.find(buffer);
    if (it != table.end()) {
        return &it->second;
    }
    throw std::runtime_error("Symbol not found");
}

Symbol *SymbolTable::makeLabel() {
    static int serial = 0;
    static char buffer[128];
    sprintf(buffer, "label%d", serial++);
    table.insert(std::pair<std::string, Symbol>(buffer, Symbol{buffer,SYMBOL_VARIABLE}));
    auto it = table.find(buffer);
    if (it != table.end()) {
        return &it->second;
    }
    throw std::runtime_error("Symbol not found");
}

