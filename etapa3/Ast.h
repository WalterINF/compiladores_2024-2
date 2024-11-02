//
// Created by walter on 11/2/24.
//

#ifndef AST_H
#define AST_H

#include "Symbols.h"
#include <string.h>

#define NODE_SYMBOL 0
#define NODE_LDEC 1
#define NODE_DECVAR 2
#define NODE_DECVEC 3
#define NODE_DECFUNC 18


#define NODE_SUM 4
#define NODE_SUB 5
#define NODE_MUL 6
#define NODE_DIV 7
#define NODE_LESS 8
#define NODE_GREATER 9
#define NODE_EQ 10
#define NODE_AND 11
#define NODE_OR 12
#define NODE_TIL 13
#define NODE_VECACC 33
#define NODE_CALL 34

#define NODE_PARAM_LST 14
#define NODE_PARAM_END 15
#define NODE_CMD_LST 16
#define NODE_CMD_END 17

#define NODE_INT 19
#define NODE_CHAR 20
#define NODE_STR 21
#define NODE_LIT_VEC 22
#define NODE_BLOCK 23
#define NODE_PARAM 24

#define NODE_ATTR 25
#define NODE_VECATTR 26
#define NODE_READ 27
#define NODE_PRINT 28
#define NODE_RETURN 29
#define NODE_WHILE 30
#define NODE_IF 31
#define NODE_IFELSE 32


class Node
{
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

    std::string toString(){
      switch (type) {
        default:
          return "invalid symbol";
    }
};

};
#endif //AST_H