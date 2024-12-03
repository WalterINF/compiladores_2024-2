//
// Created by walter on 12/1/24.
//

#ifndef TAC_H
#define TAC_H


#include "Ast.h"

extern SymbolTable symbol_table;

#define TAC_SYMBOL 1
#define TAC_MOVE 2
#define TAC_ADD 3
#define TAC_SUB 4
#define TAC_DIV 6
#define TAC_LESS 7
#define TAC_GREATER 8
#define TAC_EQ 9
#define TAC_MUL 10
#define TAC_LABEL 11
#define TAC_BEGINFUN 12
#define TAC_ENDFUN 13
#define TAC_IFZ 14
#define TAC_JUMP 15
#define TAC_CALL 16
#define TAC_ARG 17
#define TAC_RET 18
#define TAC_PRINT 19
#define TAC_READ 20
#define TAC_END 21
#define TAC_OR 22
#define TAC_AND 23
#define TAC_RETURN 24


class Tac {
public:
    int type;
    Symbol *res;
    Symbol *op1;
    Symbol *op2;

    Tac *prev;
    Tac *next;

    Tac(int type,Symbol *res, Symbol *op1, Symbol *op2);

    void printTac();

    std::string toString();

    void append(Tac *new_tac);

    static Tac *createIfThen(Tac* code[]);

    static Tac *createIfThenElse(Tac* code[]);

    static Tac *createBinOp(int type, Tac* code[]);

    static Tac *joinTV(Tac *tac1, Tac *tac2);

    static Tac *generateCode(Node *root);

    static Tac *createFunction(const Tac* symbol, Tac* params, Tac* code);

    static Tac *createWhile(Tac *code[]);

private:

};


#endif //TAC_H
