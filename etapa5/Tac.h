//
// Created by walter on 12/1/24.
//

#ifndef TAC_H
#define TAC_H


#include "Symbols.h"
#include "Ast.h"

extern SymbolTable symbol_table;

#define TAC_SYMBOL 1
#define TAC_MOVE 2
#define TAC_ADD 3
#define TAC_MUL 4
#define TAC_LABEL 5
#define TAC_BEGINFUN 6
#define TAC_ENDFUN 7
#define TAC_IFZ 8
#define TAC_JUMP 9
#define TAC_CALL 10
#define TAC_ARG 11
#define TAC_RET 12
#define TAC_PRINT 13
#define TAC_READ 14


class Tac {
public:
    int type;
    Symbol *res;
    Symbol *op1;
    Symbol *op2;

    Tac(int type,Symbol *res, Symbol *op1, Symbol *op2);

    void printTac(Tac *tac);

    std::string toString();

    void append(Tac *new_tac);

    static Tac *joinTV(Tac *tac1, Tac *tac2);

    static Tac *generateCode(Node *root);

private:
    Tac *prev;
    Tac *next;
};


#endif //TAC_H
