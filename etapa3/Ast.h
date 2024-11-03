//
// Created by walter on 11/2/24.
//

#ifndef AST_H
#define AST_H

#include <cstring>

#include "Symbols.h"
#include <string>
#include <queue>
#include <vector>

#define NODE_SYMBOL 0
#define NODE_LDEC 1
#define NODE_DECVAR 2
#define NODE_DECVEC 3
#define NODE_DECFUNC 4


#define NODE_SUM 5
#define NODE_SUB 6
#define NODE_MUL 7
#define NODE_DIV 8
#define NODE_LESS 9
#define NODE_GREATER 10
#define NODE_EQ 11
#define NODE_AND 12
#define NODE_OR 13
#define NODE_TIL 14
#define NODE_VECACC 15
#define NODE_CALL 16

#define NODE_LCMDS 17
#define NODE_CMD_END 18

#define NODE_INT 19
#define NODE_CHAR 20
#define NODE_STR 21
#define NODE_LIT_VEC 22
#define NODE_BLOCK 23
#define NODE_PARAM 24
#define NODE_LPARAMS 25
#define NODE_LPTAIL 26

#define NODE_ATTR 27
#define NODE_VECATTR 28
#define NODE_READ 29
#define NODE_PRINT 30
#define NODE_RETURN 31
#define NODE_WHILE 32
#define NODE_IF 33
#define NODE_IFELSE 34

#define NODE_LITERAL 35
#define NODE_PRINT_VEC 36

#define NODE_LCPARAMS 37
#define NODE_LCPTAIL 38


class Node {
public:
  int type;
  Symbol* symbol;
  Node* children[4];

  Node(){
    type = 0;
    symbol = NULL;
    children[0] = NULL;
    children[1] = NULL;
    children[2] = NULL;
    children[3] = NULL;
  }

  Node(int type, Symbol* symbol, Node* child0, Node* child1, Node* child2, Node* child3){
    this->type = type;
    this->symbol = symbol;
    children[0] = child0;
    children[1] = child1;
    children[2] = child2;
    children[3] = child3;
  }

  static Node* createNode(int ntype, Symbol* nsymbol, Node* child0, Node* child1, Node* child2, Node* child3){
    Node* newnode = new Node(ntype, nsymbol, child0, child1, child2, child3);
    return newnode;
  }

  void printTree() {
    //printf("PRINTING...\n");
    printAll(this);
  }

  std::string toString(){
    switch (type) {
      case NODE_SYMBOL: return "SYMBOL";
      case NODE_LDEC: return "LDEC";
      case NODE_DECVAR: return "DECVAR";
      case NODE_DECVEC: return "DECVEC";
      case NODE_DECFUNC: return "DECFUNC";
      case NODE_SUM: return "SUM";
      case NODE_SUB: return "SUB";
      case NODE_MUL: return "MUL";
      case NODE_DIV: return "DIV";
      case NODE_LESS: return "LESS";
      case NODE_GREATER: return "GREATER";
      case NODE_EQ: return "EQ";
      case NODE_AND: return "AND";
      case NODE_OR: return "OR";
      case NODE_TIL: return "TIL";
      case NODE_VECACC: return "VECACC";
      case NODE_CALL: return "CALL";
      case NODE_LCMDS: return "LCMDS";
      case NODE_ATTR: return "ATTR";
      case NODE_READ: return "READ";
      case NODE_PRINT: return "PRINT";
      case NODE_RETURN: return "RETURN";
      case NODE_WHILE: return "WHILE";
      case NODE_IF: return "IF";
      case NODE_IFELSE: return "IFELSE";
      case NODE_LITERAL: return "LITERAL";
      case NODE_PRINT_VEC: return "PRINT_VEC";
      case NODE_LCPARAMS: return "LCPARAMS";
      case NODE_LCPTAIL: return "LCPTAIL";
      case NODE_INT: return "INT";
      case NODE_CHAR: return "CHAR";
      case NODE_BLOCK: return "BLOCK";
      case NODE_VECATTR: return "VECATTR";
      case NODE_PARAM: return "PARAM";
      case NODE_LPTAIL: return "LPTAIL";
      case NODE_LPARAMS: return "LPARAMS";
    }
    return std::to_string(type);
  }

  void decompileTree(char *filepath) {
    FILE *file = fopen(filepath, "w");
    if(file)
      decompile(this,file);
    else {
      printf("Could not open file %s\n", filepath);
    }
  }

  void decompile(Node* root, FILE *output) {
    if(root == nullptr)
      return;
    switch(root->type){
      case NODE_SYMBOL:
        fprintf(output, "TEST");
      break;
      case NODE_LDEC:
        decompile(root->children[0], output);
        decompile(root->children[1], output);
      break;
      case NODE_DECVAR: break;
        decompile(root->children[0],output); //tipo de retorno
        fprintf(output, "TEST"); //nome da variavel
        fprintf(output, " = ");
        decompile(root->children[1], output); //valor de inicialização
      case NODE_DECVEC: break;
      case NODE_DECFUNC:
        decompile(root->children[0],output); //tipo de retorno
        fprintf(output, "TEST"); //nome da função
        fprintf(output, "(");
        decompile(root->children[1], output); //parametros
        fprintf(output, ")");
        decompile(root->children[2], output); //escopo
        fprintf(output, ";");
        break;
      case NODE_SUM:
        decompile(root->children[0], output);
        fprintf(output, " + ");
        decompile(root->children[1], output);
      break;
      case NODE_SUB:
        decompile(root->children[0], output);
        fprintf(output, " - ");
        decompile(root->children[1], output);
      break;
      case NODE_MUL:
        decompile(root->children[0], output);
        fprintf(output, " * ");
        decompile(root->children[1], output);
      break;
      case NODE_DIV:
        decompile(root->children[0], output);
        fprintf(output, " / ");
        decompile(root->children[1], output);
      break;
      case NODE_LESS:
        decompile(root->children[0], output);
        fprintf(output, " < ");
        decompile(root->children[1], output);
      break;
      case NODE_GREATER:
        decompile(root->children[0], output);
        fprintf(output, " > ");
        decompile(root->children[1], output);
      break;
      case NODE_EQ:
        decompile(root->children[0], output);
        fprintf(output, " == ");
        decompile(root->children[1], output);
      break;
      case NODE_AND:
        decompile(root->children[0], output);
        fprintf(output, " & ");
        decompile(root->children[1], output);
      break;
      case NODE_OR:
        decompile(root->children[0], output);
        fprintf(output, " | ");
        decompile(root->children[1], output);
      break;
      case NODE_TIL:
        decompile(root->children[0], output);
        fprintf(output, " ~ ");
        decompile(root->children[1], output);
      break;
      case NODE_VECACC:
        fprintf(output, "TEST"); //nome do vetor
        fprintf(output, "[");
        decompile(root->children[0], output);
        fprintf(output, "]");
        break;
      case NODE_CALL:
        fprintf(output, "TEST"); //nome da função
        fprintf(output, "(");
        decompile(root->children[0], output); //lista de parametros
        fprintf(output, ")");
        fprintf(output, ";");
        break;
      case NODE_LCMDS:
        decompile(root->children[0], output);
        decompile(root->children[1], output);
      break;
      case NODE_ATTR:
        fprintf(output, "TEST"); //nome da variavel
        fprintf(output, " = ");
        decompile(root->children[0], output); //valor atribuido
        break;
      case NODE_READ:
        fprintf(output, "read");
        decompile(root->children[0], output);
        break;
      case NODE_PRINT:
        fprintf(output, "print");
        decompile(root->children[0], output);
        break;
      case NODE_RETURN:
        fprintf(output, "return");
        decompile(root->children[0], output);
        break;
      case NODE_WHILE:
        fprintf(output, "while");
        fprintf(output, "(");
        decompile(root->children[0], output);
        fprintf(output, ")");
        break;
      case NODE_IF:
        fprintf(output, "if");
        fprintf(output, "(");
        decompile(root->children[0], output);
        fprintf(output, ")");
        decompile(root->children[1], output);
        break;
      case NODE_IFELSE: break;
        fprintf(output, "if");
        fprintf(output, "(");
        decompile(root->children[0], output);
        fprintf(output, ")");
        decompile(root->children[1], output);
        fprintf(output, "else");
        decompile(root->children[2], output);
      case NODE_LITERAL:
        fprintf(output, "TEST"); //valor literal
        break;
      case NODE_PRINT_VEC:
        decompile(root->children[0], output);
        decompile(root->children[1], output);
        break;
      case NODE_LCPARAMS: break;
        decompile(root->children[0], output);
        fprintf(output, ",");
        decompile(root->children[1], output);
      case NODE_LCPTAIL: break;
        decompile(root->children[0], output);
        fprintf(output, ",");
        decompile(root->children[1], output);
      case NODE_INT:
        fprintf(output, "int");
        break;
      case NODE_CHAR:
        fprintf(output, "char");
      break;
      case NODE_BLOCK:
        fprintf(output, "{");
        decompile(root->children[0], output);
        fprintf(output, "}");
        break;
      case NODE_VECATTR: break;
        fprintf(output, "TEST"); //nome do vetor
        fprintf(output, "[");
        decompile(root->children[0], output); //indice
        fprintf(output, "]");
        fprintf(output, " = ");
        decompile(root->children[1], output); //valor atribuido
      case NODE_PARAM: break;
        decompile(root->children[0], output); //tipo do parametro
        fprintf(output, "TEST"); //nome do parametro
      case NODE_LPARAMS:
        decompile(root->children[0], output);
        fprintf(output, ",");
        decompile(root->children[1], output);
        break;
      case NODE_LPTAIL:
        decompile(root->children[0], output);
        fprintf(output, ",");
        decompile(root->children[1], output);
        break;
      default: printf("\nERROR IN DECOMPILING");
      break;
    }
  }

private:
  void printAll(Node* node, int depth = 0) {
    if (node == nullptr) {
      return;
    }

    for (int i = 0; i < depth; i++) {
      printf("--");
    }

    printf("%s", node->toString().c_str());

    if(node->symbol == NULL) {
      printf(" NULL");
    } else {
    printf(" (%s)", node->symbol->name.c_str());
    }

    printf("\n");

    for (int i = 0; i < 4; i++) {
      if (node->children[i] != nullptr) {
        printAll(node->children[i], depth + 1);
      }
    }
  }
};


#endif //AST_H