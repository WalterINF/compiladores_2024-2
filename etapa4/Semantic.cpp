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
        fprintf(stderr,"SemanticError in line %d: Redeclared variable: %s\n",root->line_number,
          root->symbol->name.c_str());
        SemanticErrors++;
      }
      root->symbol->type = SYMBOL_VARIABLE;
      if(root->children[0]->type == NODE_INT) {
          root->symbol->datatype = DATATYPE_INT;
      }
      if(root->children[0]->type == NODE_CHAR) {
        root->symbol->datatype = DATATYPE_CHAR;
      }
      break;
    case NODE_DECVEC:
      if(root->symbol->type != SYMBOL_IDENTIFIER) {
        fprintf(stderr,"SemanticError in line %d: Redeclared vector: %s\n",root->line_number,
          root->symbol->name.c_str());
        SemanticErrors++;
      }
      root->symbol->type = SYMBOL_VECTOR;
      if(root->children[0]->type == NODE_INT) {
        root->symbol->datatype = DATATYPE_INT;
      }
      if(root->children[0]->type == NODE_CHAR) {
        root->symbol->datatype = DATATYPE_CHAR;
      }
      if(root->children[2] != nullptr) {
        if(!check_vector_size(root)) {
          fprintf(stderr,"SemanticError in line %d: Incompatible vector size with initalizer list\n",root->line_number);
        }
      }
      break;
    case NODE_DECFUNC:
      if(root->symbol->type != SYMBOL_IDENTIFIER) {
        fprintf(stderr,"SemanticError in line %d: Redeclared function: %s\n",root->line_number,
          root->symbol->name.c_str());
        SemanticErrors++;
      }
      root->symbol->type = SYMBOL_FUNCTION;
      if(root->children[0]->type == NODE_INT) {
        root->symbol->datatype = DATATYPE_INT;
      }
      if(root->children[0]->type == NODE_CHAR) {
        root->symbol->datatype = DATATYPE_CHAR;
      }
      if(!check_type(root->symbol->datatype, get_return_type(root))){
        SemanticErrors++;
        fprintf(stderr,"SemanticError in line %d: Return type mismatch in function %s\n",root->line_number,root->symbol->name.c_str());
      }
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
        fprintf(stderr, "SemanticError in line %d: invalid left operand\n",root->line_number);
      }
      if(!is_number(root->children[1])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: invalid right operand\n",root->line_number);
      }
      break;
    case NODE_EQ:
    case NODE_OR:
    case NODE_TIL:
    case NODE_AND:
      if(!isRelationalOp(root->children[0])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: invalid left operand\n",root->line_number);
      }
      if(!isRelationalOp(root->children[1])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: invalid right operand\n",root->line_number);
      }
      break;
    case NODE_LESS:
    case NODE_GREATER:
      if(!is_number(root->children[0])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: invalid left operand\n",root->line_number);
      }
      if(!is_number(root->children[1])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: invalid right operand\n",root->line_number);
      }
      break;
    default:
      break;
  }
  for(const auto& child : root->children) {
    check_operands(child);
  }
}

void Semantic::check_usage(Node *root) {
  if(root == nullptr) {
    return;
  }
  switch(root->type) {
    case NODE_ATTR:
      if(root->symbol->type != SYMBOL_VARIABLE) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: Attribution must be to a variable \n",root->line_number);
      }
      if(
        (root->symbol->datatype == DATATYPE_INT && !is_number(root->children[0])) ||
        (root->symbol->datatype == DATATYPE_CHAR && !is_char(root->children[0]))
        ){
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: incompatible types: %d and %d\n",root->line_number,root->symbol->datatype, root->children[0]->type);
      }
    break;
    case NODE_VECACC:
      if(root->symbol->type != SYMBOL_VECTOR) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: Not a vector: %s\n",root->line_number,root->symbol->name.c_str());
      }
      if(!is_number(root->children[0])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: invalid vector index\n",root->line_number);
      }
      break;
    case NODE_CALL:
      if(root->symbol->type != SYMBOL_FUNCTION) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: Not a function: %s\n",root->line_number,root->symbol->name.c_str());
      }
    break;
    case NODE_VECATTR:
      if(root->symbol->type != SYMBOL_VECTOR) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: Not a vector: %s\n",root->line_number,root->symbol->name.c_str());
      }
      if(!is_number(root->children[0])) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: invalid vector index\n",root->line_number);
      }
      if(!check_type(root->children[0]->type, root->symbol->datatype)) {
        SemanticErrors++;
        fprintf(stderr, "SemanticError in line %d: incompatible types: %d and %d\n",root->line_number,root->children[0]->type, root->symbol->datatype);
      }
    break;
    default:
      break;

  }
  for(const auto& child : root->children) {
    check_usage(child);
  }
}









