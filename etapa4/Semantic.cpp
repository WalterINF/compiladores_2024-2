//
// Created by walter on 11/23/24.
//

#include "Semantic.h"

int SemanticErrors = 0;

void Semantic::check_and_set_declarations(Node *root){
  if(!root){
    return;
  }

  switch (root->type) {
    case NODE_DECVAR:
      if(root->symbol->type != SYMBOL_IDENTIFIER) {
        fprintf(stderr,"SemanticError: Redeclared variable: %s\n",
          root->symbol->name.c_str());
        SemanticErrors++;
      }
      root->symbol->type = SYMBOL_VARIABLE;
      if(root->children[0]->type == NODE_INT) {
          root->symbol->datatype == DATATYPE_INT;
      }
      if(root->children[0]->type == NODE_CHAR) {
        root->symbol->datatype == DATATYPE_CHAR;
      }

      break;
    case NODE_DECVEC:
      if(root->symbol->type != SYMBOL_IDENTIFIER) {
        fprintf(stderr,"SemanticError: Redeclared vector: %s\n",
          root->symbol->name.c_str());
        SemanticErrors++;
      }
      root->symbol->type = SYMBOL_VECTOR;
      break;
    case NODE_DECFUNC:
      if(root->symbol->type != SYMBOL_IDENTIFIER) {
        fprintf(stderr,"SemanticError: Redeclared function: %s\n",
          root->symbol->name.c_str());
        SemanticErrors++;
      }
      root->symbol->type = SYMBOL_FUNCTION;
      break;
    default:
      break;
  }

  for(const auto child : root->children) {
    check_and_set_declarations(child);
  }

}

int Semantic::check_undeclared(SymbolTable table) {
  int undeclared = 0;

  for (const auto& pair : table.getTable()) {
    if(pair.second.type == SYMBOL_IDENTIFIER) {
      undeclared++;
      SemanticErrors++;
      fprintf(stderr, "SemanticError: Undeclared identifier \"%s\"\n",pair.second.name.c_str());
    }
  }
  return undeclared;
}

void Semantic::check_operands(Node *root) {
  if(root == nullptr) {
    return;
  }
  switch(root->type) {
    case NODE_DIV:
    case NODE_MUL:
    case NODE_SUB:
    case NODE_SUM:
      if(!is_number(root->children[0])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError: invalid left operand\n");
      }
      if(!is_number(root->children[1])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError: invalid right operand\n");
      }
      break;
    case NODE_EQ:
    case NODE_OR:
    case NODE_TIL:
    case NODE_AND:
      if(!isRelationalOp(root->children[0])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError: invalid left operand\n");
      }
      if(!isRelationalOp(root->children[1])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError: invalid right operand\n");
      }
      break;
    case NODE_LESS:
    case NODE_GREATER:
      if(!is_number(root->children[0])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError: invalid left operand\n");
      }
      if(!is_number(root->children[1])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError: invalid right operand\n");
      }
      break;
    default:
      break;
  }
  for(const auto& child : root->children) {
    check_operands(child);
  }
}






