/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
*/

#include "Symbols.h"

/* Inserts a Symbol object into the table, using its 'name' value as the key. */
void insertSymbol(std::map<std::string, Symbol> *table, Symbol symbol)
{
    table->insert(std::pair<std::string, Symbol>(symbol.name, symbol));
}

/* Prints all table's 'key : value' pairs to stdout. */
void printSymbols(std::map<std::string, Symbol> table)
{
    for (const auto& pair : table) {
        fprintf(stdout, "%s : %d\n", pair.first.c_str(), pair.second.type);
    }
}