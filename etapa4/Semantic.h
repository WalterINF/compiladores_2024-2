//
// Created by walter on 11/23/24.
//

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "Ast.h"
#include "Symbols.h"

extern int semantic_errors;

class Semantic {
public:
    static void verify();
    static void check_and_set_declarations(Node *root);
    static int check_undeclared(SymbolTable table);
};


#endif //SEMANTIC_H
