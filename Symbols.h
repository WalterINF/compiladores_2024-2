/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
 */

//
// Created by walter on 08/10/24.
//

#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <iostream>
#include <map>
#include <string>

void insertSymbol(std::map<std::string, int> *table, char* symbol, int type);
void printSymbols(std::map<std::string, int> table);


#endif //SYMBOLS_H
