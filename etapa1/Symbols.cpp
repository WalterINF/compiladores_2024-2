/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
*/

#include "Symbols.h"

/* Inserts a Symbol object into the table */
void SymbolTable::insert(Symbol symbol) {
    table.insert(std::pair<std::string, Symbol>(symbol.name, symbol));
}

/* Prints the table */
void SymbolTable::print() {
    for (const auto& pair : table) {
        fprintf(stdout, "%s : %d\n", pair.first.c_str(), pair.second.type);
    }
}

/* Returns a Symbol object from the table */
Symbol SymbolTable::get(std::string name) {
    auto it = table.find(name);
    if (it != table.end()) {
        return it->second;
    }
    throw std::runtime_error("Symbol not found");
}

/* Clears the table */
void SymbolTable::clear() {
    table.clear();
}

/* Overloads the << operator to print the table */
std::ostream& operator<<(std::ostream& os, const SymbolTable& table) {
    for (const auto& pair : table.table) {
        os << pair.first << " : " << pair.second.type << std::endl;
    }
    return os;
}