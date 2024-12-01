//
// Created by walter on :/:/:.
//

#include "Tac.h"

Tac::Tac(int type,Symbol *res, Symbol *op1, Symbol *op2) {
    this->type = type;
    this->op1 = op1;
    this->op2 = op2;
    this->next = nullptr;
    this->prev = nullptr;
}


std::string Tac::toString() {
    fprintf(stderr, "TAC(");
    switch (type) {
        case TAC_SYMBOL:
        case TAC_MOVE:
        case TAC_ADD:
        case TAC_MUL:
        case TAC_LABEL:
        case TAC_BEGINFUN:
        case TAC_ENDFUN:
        case TAC_IFZ:
        case TAC_JUMP:
        case TAC_CALL:
        case TAC_ARG:
        case TAC_RET:
        case TAC_PRINT:
        case TAC_READ:
        default:
            break;
    }
}

void Tac::printTac(Tac *tac) {
    fprintf(stderr, "TAC(%s)", tac->toString().c_str());
}

void Tac::append(Tac *new_tac) {
    if (!new_tac) return;
    Tac *curr = next;
    while (curr) {
        curr = curr->next;
    }
    if (curr) {
        curr->next = new_tac;
    }
}

Tac *Tac::joinTV(Tac *tac1, Tac *tac2) {
    if (!tac1)
        return tac2;
    if (!tac2)
        return tac1;
    Tac *c2 = tac2;
    while (c2->prev) {
        c2 = c2->prev;
    }
    c2->prev = tac1;
    return tac2;
}

Tac *Tac::generateCode(Node *root) {
    Tac *result = nullptr;
    Tac *code[4] = {nullptr, nullptr, nullptr, nullptr};

    if (!root) return nullptr;

    for (int i = 0; i < 4; i++) {
        code[i] = generateCode(root->children[i]);
    }

    switch (root->type) {
        case NODE_SYMBOL:
            result = new Tac(TAC_SYMBOL, root->symbol, nullptr,nullptr);
            break;
        case NODE_SUM:
            result = joinTV(
                joinTV(code[0],code[1]),
                new Tac(
                    TAC_ADD,
                    symbol_table.makeTemp(),
                    code[0]?code[0]->res:nullptr,
                    code[1]?code[1]->res:nullptr)
            );
            break;
        case NODE_ATTR:
            result = joinTV(code[0],new Tac(TAC_MOVE,root->symbol,nullptr,nullptr));
            break;
        default:
            result = joinTV(code[0],joinTV(code[1],joinTV(code[2],code[3])));
    }

    return result;
}
