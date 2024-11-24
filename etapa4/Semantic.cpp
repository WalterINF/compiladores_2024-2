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

