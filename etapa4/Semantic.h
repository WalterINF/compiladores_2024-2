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
    static void check_operands(Node *root);
    static int isRelationalOp(Node *root){
        return
            root->type == NODE_EQ ||
            root->type == NODE_OR ||
            root->type == NODE_LESS ||
            root->type == NODE_GREATER ||
            root->type == NODE_AND ||
            root->type == NODE_TIL;
    }

    static int is_number(Node *root){
        return
            root->type == NODE_SUM ||
            root->type == NODE_DIV ||
            root->type == NODE_MUL ||
            root->type == NODE_SUB ||
            (root->type == NODE_SYMBOL && root->symbol->type == SYMBOL_LIT_INT) ||
            (root->symbol->type == SYMBOL_VARIABLE && root->symbol->datatype == DATATYPE_INT) ||
            (root->type == NODE_CALL && root->symbol->datatype == DATATYPE_INT);
    }

    static void check_usage(Node *root);
};


#endif //SEMANTIC_H
