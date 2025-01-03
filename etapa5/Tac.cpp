//
// Created by walter on :/:/:.
//

#include "Tac.h"

Tac::Tac(int type, Symbol *res, Symbol *op1, Symbol *op2) {
    this->type = type;
    this->res = res;
    this->op1 = op1;
    this->op2 = op2;
    this->next = nullptr;
    this->prev = nullptr;
}

std::string Tac::toString() {
    switch (type) {
        case TAC_SYMBOL:
            return "SYMBOL";
        case TAC_MOVE:
            return "MOVE";
        case TAC_ADD:
            return "ADD";
        case TAC_MUL:
            return "MUL";
        case TAC_DIV:
            return "DIV";
        case TAC_SUB:
            return "SUB";
        case TAC_EQ:
            return "EQ";
        case TAC_LESS:
            return "LESS";
        case TAC_GREATER:
            return "GREATER";
        case TAC_LABEL:
            return "LABEL";
        case TAC_BEGINFUN:
            return "BEGINFUN";
        case TAC_ENDFUN:
            return "ENDFUN";
        case TAC_IFZ:
            return "IFZ";
        case TAC_JUMP:
            return "JUMP";
        case TAC_CALL:
            return "CALL";
        case TAC_ARG:
            return "ARG";
        case TAC_RET:
            return "RET";
        case TAC_PRINT:
            return "PRINT";
        case TAC_READ:
            return "READ";
        case TAC_END:
            return "END";
        case TAC_ARGPOP:
            return "ARGPOP";
        default:
            return "UNKNOWN";
    }
}

void Tac::printTac() {
    if (this->type == TAC_SYMBOL) return;

    fprintf(stderr, "TAC(%s,", this->toString().c_str());
    this->res ? fprintf(stderr, "%s, ", this->res->name.c_str()) : fprintf(stderr, "null, ");
    this->op1 ? fprintf(stderr, "%s, ", this->op1->name.c_str()) : fprintf(stderr, "null, ");
    this->op2 ? fprintf(stderr, "%s", this->op2->name.c_str()) : fprintf(stderr, "null");
    fprintf(stderr, ")\n");
}

void Tac::printList() {
    Tac *acc = this;
    Tac *result = nullptr;
    while (acc) {
        result = acc;
        acc = acc->prev;
    }
    while (result) {
        result->printTac();
        result = result->next;
    }
}


void Tac::append(Tac *new_tac) {
    if (!new_tac) return;
    Tac *curr = this;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = new_tac;
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
    tac1->next = c2;
    return tac2;
}

Tac *Tac::generateCode(Node *root) {
    Tac *body = generateCodeBody(root);
    return joinTV(body,new Tac(TAC_END,nullptr,nullptr,nullptr));
}

Tac *Tac::generateCodeBody(Node *root) {
    Tac *result = nullptr;
    Tac *code[4] = {nullptr, nullptr, nullptr, nullptr};

    if (!root) return nullptr;

    for (int i = 0; i < 4; i++) {
        code[i] = generateCodeBody(root->children[i]);
    }

    switch (root->type) {
        case NODE_DECVAR:
            result = joinTV(code[0], new Tac(TAC_MOVE, root->symbol, code[1] ? code[1]->res : nullptr, nullptr));
            break;
        case NODE_SYMBOL:
            result = new Tac(TAC_SYMBOL, root->symbol, nullptr, nullptr);
            break;
        case NODE_SUM:
            result = createBinOp(TAC_ADD, code);
            break;
        case NODE_MUL:
            result = createBinOp(TAC_MUL, code);
            break;
        case NODE_DIV:
            result = createBinOp(TAC_DIV, code);
            break;
        case NODE_SUB:
            result = createBinOp(TAC_SUB, code);
            break;
        case NODE_AND:
            result = createBinOp(TAC_AND, code);
            break;
        case NODE_OR:
            result = createBinOp(TAC_OR, code);
            break;
        case NODE_EQ:
            result = createBinOp(TAC_EQ, code);
            break;
        case NODE_LESS:
            result = createBinOp(TAC_LESS, code);
            break;
        case NODE_GREATER:
            result = createBinOp(TAC_GREATER, code);
            break;
        case NODE_ATTR:
            result = joinTV(code[0], new Tac(TAC_MOVE, root->symbol, code[0] ? code[0]->res : nullptr, nullptr));
            break;
        case NODE_IF:
            result = createIfThen(code);
            break;
        case NODE_IFELSE:
            result = createIfThenElse(code);
            break;
        case NODE_DECFUNC:
            result = createFunction(new Tac(TAC_SYMBOL, root->symbol, nullptr, nullptr), code[1], code[2]);
            break;
        case NODE_READ:
            result = new Tac(TAC_READ, root->symbol, nullptr, nullptr);
            break;
        case NODE_RETURN:
            result = joinTV(code[0], new Tac(TAC_RET, code[0] ? code[0]->res : nullptr, nullptr, nullptr));
            break;
        case NODE_WHILE:
            result = createWhile(code);
            break;
        case NODE_CALL:
            result = joinTV(code[0], new Tac(TAC_CALL, root->symbol, code[0] ? code[0]->res : nullptr, nullptr));
            break;
        case NODE_LCPTAIL:
        case NODE_LCPARAMS:
            result = joinTV(new Tac(TAC_ARG, code[0] ? code[0]->res : nullptr,nullptr, nullptr),code[1]);
            break;
        case NODE_PRINT_VEC:
            result = joinTV(new Tac(TAC_PRINT, root->symbol, code[0] ? code[0]->res : nullptr, nullptr),joinTV(code[0],code[1]));
            break;
        case NODE_PARAM:
            result = new Tac(TAC_ARGPOP, root->symbol,nullptr,nullptr);
            break;
        case NODE_LPARAMS:
        case NODE_LPTAIL:
            result = joinTV(code[0],code[1]);
            break;


        default:
            result = joinTV(code[0], joinTV(code[1], joinTV(code[2], code[3])));
            break;
    }
    return result;
}

Tac *Tac::createBinOp(int type, Tac *code[]) {
    const auto newtac = new Tac(
        type,
        symbol_table.makeTemp(),
        code[0] ? code[0]->res : nullptr,
        code[1] ? code[1]->res : nullptr);
    Tac *result = joinTV(code[0], joinTV(code[1], newtac));
    return result;
}

Tac *Tac::createWhile(Tac *code[]) {
    Tac *jumptac = nullptr;
    Tac *labeltac = nullptr;
    Symbol *newlabel = nullptr;
    newlabel = symbol_table.makeLabel();
    jumptac = new Tac(TAC_JUMP, newlabel, code[0] ? code[0]->res : nullptr, nullptr);
    labeltac = new Tac(TAC_LABEL, newlabel, nullptr, nullptr);
    return joinTV(code[0], joinTV(jumptac, joinTV(code[1], labeltac)));
}


Tac *Tac::createIfThen(Tac *code[]) {
    Tac *jumptac = nullptr;
    Tac *labeltac = nullptr;
    Symbol *newlabel = nullptr;
    newlabel = symbol_table.makeLabel();
    jumptac = new Tac(TAC_IFZ, newlabel, code[0] ? code[0]->res : nullptr, nullptr);
    labeltac = new Tac(TAC_LABEL, newlabel, nullptr, nullptr);
    return joinTV(code[0], joinTV(jumptac, joinTV(code[1], labeltac)));
}

Tac *Tac::createIfThenElse(Tac *code[]) {
    Tac *iftac = nullptr;
    Tac *jumptac = nullptr;
    Tac *labeltac = nullptr;
    Tac *exittac = nullptr;
    Symbol *newlabel = nullptr;
    Symbol *exitlabel = nullptr;
    newlabel = symbol_table.makeLabel();
    exitlabel = symbol_table.makeLabel();
    iftac = new Tac(TAC_IFZ, newlabel, code[0] ? code[0]->res : nullptr, nullptr);
    labeltac = new Tac(TAC_LABEL, newlabel, nullptr, nullptr);
    exittac = new Tac(TAC_LABEL, exitlabel, nullptr, nullptr);
    jumptac = new Tac(TAC_JUMP, exitlabel, nullptr, nullptr);
    return joinTV(code[0], joinTV(iftac, joinTV(code[1], joinTV(jumptac, joinTV(labeltac, joinTV(code[2], exittac))))));
}

Tac *Tac::createFunction(const Tac *symbol, Tac *params, Tac *code) {
    return joinTV(joinTV(joinTV(new Tac(TAC_BEGINFUN, symbol->res, nullptr, nullptr), params), code),
                  new Tac(TAC_ENDFUN, symbol->res, nullptr, nullptr));
}
