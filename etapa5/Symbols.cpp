/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
*/

#include "Symbols.h"
#include <algorithm>

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

/* Inserts a Symbol object into the table */
Symbol *SymbolTable::insert(char* name, int type) {
    const auto new_sym = new Symbol(name,type);
    new_sym->name = ReplaceAll(new_sym->name,"_","");
    table.insert(std::pair<std::string, Symbol>(new_sym->name, *new_sym));
    return this->get(name);
}

/* Prints the table */
void SymbolTable::print() const {
    for (const auto& pair : table) {
        fprintf(stdout, "%s : %d\n", pair.first.c_str(), pair.second.type);
    }
}

/* Returns a Symbol object from the table */
Symbol *SymbolTable::get(const std::string& name) {
    auto it = table.find(name);
    if (it != table.end()) {
        return &it->second;
    }
    throw std::runtime_error("Symbol not found");
}

/* Clears the table */
void SymbolTable::clear() {
    table.clear();
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
    static char buffer[128];
    sprintf(buffer,"_temp%d",serial++);
    const auto new_sym = new Symbol(buffer,SYMBOL_VARIABLE);
    table.insert(std::pair<std::string, Symbol>(buffer, *new_sym));
    return this->get(buffer);
}

Symbol *SymbolTable::makeLabel() {
    static int serial = 0;
    static char buffer[128];
    sprintf(buffer,"_label%d",serial++);
    auto* new_sym = new Symbol(buffer,SYMBOL_LABEL);
    table.insert(std::pair<std::string, Symbol>(buffer, *new_sym));
    return this->get(buffer);
}

