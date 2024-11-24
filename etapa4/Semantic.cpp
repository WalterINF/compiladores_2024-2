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
        fprintf(stderr,"SemanticError: Redeclared identifier: %s\n",
          root->symbol->name.c_str());
        SemanticErrors++;
      }
      root->symbol->type = SYMBOL_VARIABLE;
      break;
    case NODE_DECVEC:
      break;
    case NODE_DECFUNC:
      printf(" %d ",root->symbol->type);
      if(root->symbol->type != SYMBOL_IDENTIFIER) {
        printf("SemanticError: Redeclared function \n");
        fprintf(stderr,"SemanticError: Redeclared function: %s\n",
          root->symbol->name.c_str());
        SemanticErrors++;
      }
      root->symbol->type = SYMBOL_FUNCTION;
      printf("   %d\n",root->symbol->type);
      break;
    default:
      break;
  }

  for(const auto child : root->children) {
    check_and_set_declarations(child);
  }

}
