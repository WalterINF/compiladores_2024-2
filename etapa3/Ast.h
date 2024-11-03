//
// Created by walter on 11/2/24.
//

#ifndef AST_H
#define AST_H

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

  void printAll() {
    printf("PRINTING...\n");
    printTree(this);
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
      }
    return "ERR";
  }

private:
  void printTree(Node* node, int depth = 0) {
    if (node == nullptr) {
      return;
    }

    // Print indentation
    for (int i = 0; i < depth; i++) {
      printf("  ");  // Two spaces for each level of depth
    }

    // Print current node
    printf("%s", node->toString().c_str());

    // Print symbol value if it exists
    if (node->symbol != nullptr) {
      printf(" (%s)", node->toString().c_str());
    }
    printf("\n");

    // Print all children recursively
    for (int i = 0; i < 4; i++) {
      if (node->children[i] != nullptr) {
        printTree(node->children[i], depth + 1);
      }
    }
  }

};


#endif //AST_H