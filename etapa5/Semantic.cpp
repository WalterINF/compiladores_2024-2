//
// Created by walter on 11/23/24.
//

#include "Semantic.h"

int SemanticErrors = 0;

void Semantic::check_and_set_declarations(Node *root) {
    if (!root) {
        return;
    }

    switch (root->type) {
        case NODE_PARAM:
            root->symbol->type = SYMBOL_VARIABLE;
            break;
        case NODE_DECVAR:
            if (root->symbol->type != SYMBOL_IDENTIFIER) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: Redeclared variable: %s\n", root->line_number,
                        root->symbol->name.c_str());
            }
            root->symbol->type = SYMBOL_VARIABLE;
            if (root->children[0]->type == NODE_INT) {
                root->symbol->datatype = DATATYPE_INT;
            }
            if (root->children[0]->type == NODE_CHAR) {
                root->symbol->datatype = DATATYPE_CHAR;
            }
            break;
        case NODE_DECVEC:
            if (root->symbol->type != SYMBOL_IDENTIFIER) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: Redeclared vector: %s\n", root->line_number,
                        root->symbol->name.c_str());
            }
            root->symbol->type = SYMBOL_VECTOR;
            root->symbol->datatype = DATATYPE_NONE;
            if (root->children[0]->type == NODE_INT) {
                root->symbol->datatype = DATATYPE_INT;
            }
            if (root->children[0]->type == NODE_CHAR) {
                root->symbol->datatype = DATATYPE_CHAR;
            }
            break;
        case NODE_DECFUNC:
            if (root->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "SemanticError in line %d: Redeclared function: %s\n", root->line_number,
                        root->symbol->name.c_str());
                SemanticErrors++;
            }
            root->symbol->type = SYMBOL_FUNCTION;
            if (root->children[0]->type == NODE_INT) {
                root->symbol->datatype = DATATYPE_INT;
            }
            if (root->children[0]->type == NODE_CHAR) {
                root->symbol->datatype = DATATYPE_CHAR;
            }
            break;
        default:
            break;
    }

    for (const auto child: root->children) {
        check_and_set_declarations(child);
    }
}

void Semantic::check_types(Node *root) {
    if (!root) {
        return;
    }
    switch (root->type) {
        case NODE_DECVAR:
            if (root->children[1]) {
                if (!checkTypeCompatibility(root->symbol->datatype, getType(root->children[1]))) {
                    SemanticErrors++;
                    fprintf(stderr, "SemanticError in line %d: incompatible types: %s and %s\n",
                            root->line_number,
                            Symbol::typeToString(root->symbol->datatype).c_str(),
                            Symbol::typeToString(getType(root->children[1])).c_str()
                    );
                }
            }
            break;
        case NODE_DECVEC:
            if (root->children[2] != nullptr) {
                if (get_vector_type(root->children[2]) != root->symbol->datatype) {
                    SemanticErrors++;
                    fprintf(stderr, "SemanticError in line %d: Multiple types in initializer list\n",
                            root->line_number);
                }
            }
            break;
        case NODE_DECFUNC:
            if (!checkTypeCompatibility(root->symbol->datatype, get_return_type(root))) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: Return type mismatch in function %s\n", root->line_number,
                        root->symbol->name.c_str());
            }
            break;
        case NODE_ATTR:
            if (root->symbol->type != SYMBOL_VARIABLE) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: Attribution must be to a variable \n", root->line_number);
            }
            if (!checkTypeCompatibility(root->symbol->datatype, getType(root->children[0]))
            ) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: incompatible types: %s and %s\n",
                        root->line_number,
                        Symbol::typeToString(root->symbol->datatype).c_str(),
                        Symbol::typeToString(getType(root->children[0])).c_str());
            }
            break;
        case NODE_VECATTR:
            if (!checkTypeCompatibility(root->symbol->datatype, getType(root->children[1]))) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: incompatible types: %s and %s\n",
                        root->line_number,
                        Symbol::typeToString(root->symbol->datatype).c_str(),
                        Symbol::typeToString(getType(root->children[1])).c_str()
                );
            }
            break;
        default:
            break;
    }
    for (const auto child: root->children) {
        check_types(child);
    }
}

void Semantic::check_undeclared(SymbolTable table) {
    for (const auto &pair: table.getTable()) {
        if (pair.second.type == SYMBOL_IDENTIFIER) {
            SemanticErrors++;
            fprintf(stderr, "SemanticError: Undeclared identifier \"%s\"\n", pair.second.name.c_str());
        }
    }
}

void Semantic::check_operands(Node *root) {
    if (root == nullptr) {
        return;
    }
    switch (root->type) {
        case NODE_DIV:
        case NODE_MUL:
        case NODE_SUB:
        case NODE_SUM:
            if (!is_number(root->children[0]) && !is_char(root->children[0])) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: invalid left operand\n", root->line_number);
            }
            if (!is_number(root->children[1]) && !is_char(root->children[1])) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: invalid right operand\n", root->line_number);
            }
            break;
        case NODE_EQ:
        case NODE_OR:
        case NODE_TIL:
        case NODE_AND:
            if (!is_number(root->children[0]) && !is_char(root->children[0])) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: invalid left operand\n", root->line_number);
            }
            if (!is_number(root->children[1]) && !is_char(root->children[1])) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: invalid right operand\n", root->line_number);
            }
            break;
        case NODE_LESS:
        case NODE_GREATER:
            if (!is_number(root->children[0]) && !is_char(root->children[0])) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: invalid left operand\n", root->line_number);
            }
            if (!is_number(root->children[1]) && !is_char(root->children[1])) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: invalid right operand\n", root->line_number);
            }
            break;
        default:
            break;
    }
    for (const auto &child: root->children) {
        check_operands(child);
    }
}

void Semantic::check_usage(Node *root) {
    if (root == nullptr) {
        return;
    }
    switch (root->type) {
        case NODE_SYMBOL:
            if (root->symbol->type == SYMBOL_FUNCTION || root->symbol->type == SYMBOL_VECTOR) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: Not a variable: %s\n", root->line_number,
                        root->symbol->name.c_str());
            }
            break;
        case NODE_ATTR:
            if (root->symbol->type != SYMBOL_VARIABLE) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: Not a variable: %s\n", root->line_number,
                        root->symbol->name.c_str());
            }
            break;
        case NODE_VECACC:
            if (root->symbol->type != SYMBOL_VECTOR) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: Not a vector: %s\n", root->line_number,
                        root->symbol->name.c_str());
            }
            if (!is_number(root->children[0])) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: invalid vector index\n", root->line_number);
            }
            break;
        case NODE_CALL:
            if (root->symbol->type != SYMBOL_FUNCTION) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: Not a function: %s\n", root->line_number,
                        root->symbol->name.c_str());
            }
            break;
        case NODE_VECATTR:
            if (root->symbol->type != SYMBOL_VECTOR) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: Not a vector: %s\n", root->line_number,
                        root->symbol->name.c_str());
            }
            if (!is_number(root->children[0])) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: invalid vector index\n", root->line_number);
            }
            if (!checkTypeCompatibility(root->symbol->datatype, getType(root->children[1]))) {
                SemanticErrors++;
                fprintf(stderr, "SemanticError in line %d: incompatible types: %s and %s\n",
                        root->line_number,
                        Symbol::typeToString(root->symbol->datatype).c_str(),
                        Symbol::typeToString(getType(root->children[1])).c_str()
                );
            }
            break;
        default:
            break;
    }
    for (const auto &child: root->children) {
        check_usage(child);
    }
}

void Semantic::check_calls(Node *root, Node *current_node) {
    if (root == nullptr || current_node == nullptr) {
        return;
    }
    if (current_node->type == NODE_CALL) {
        if (!compareAllParams(getFunctionParams(root, current_node->symbol), current_node->children[0])) {
            SemanticErrors++;
            fprintf(stderr, "SemanticError in line %d: invalid call\n", current_node->line_number);
        }
    }
    for (const auto &child: current_node->children) {
        check_calls(root, child);
    }
}


int Semantic::is_bool(const Node *root) {
    return
            root != nullptr && (
                root->type == NODE_EQ ||
                root->type == NODE_OR ||
                root->type == NODE_LESS ||
                root->type == NODE_GREATER ||
                root->type == NODE_AND ||
                root->type == NODE_TIL);
}

int Semantic::is_number(const Node *root) {
    return
            root != nullptr && (
                root->type == NODE_SUM ||
                root->type == NODE_DIV ||
                root->type == NODE_MUL ||
                root->type == NODE_SUB ||
                (root->symbol != nullptr && root->symbol->datatype == DATATYPE_INT) ||
                (root->type == NODE_SYMBOL && root->symbol != nullptr && root->symbol->type == SYMBOL_LIT_INT) ||
                (root->symbol != nullptr && root->symbol->type == SYMBOL_VARIABLE && root->symbol->datatype ==
                 DATATYPE_INT) ||
                (root->type == NODE_VECACC && root->symbol != nullptr && root->symbol->datatype == DATATYPE_INT) ||
                (root->type == NODE_CALL && root->symbol != nullptr && root->symbol->datatype == DATATYPE_INT));
}

int Semantic::is_char(const Node *root) {
    return
            root != nullptr && (
                root->type == NODE_CHAR ||
                (root->symbol != nullptr && root->symbol->datatype == DATATYPE_CHAR) ||
                (root->type == NODE_SYMBOL && root->symbol != nullptr && root->symbol->type == SYMBOL_LIT_CHAR) ||
                (root->type == NODE_CALL && root->symbol != nullptr && root->symbol->datatype == DATATYPE_CHAR) ||
                (root->type == NODE_VECACC && root->symbol != nullptr && root->symbol->datatype == DATATYPE_CHAR) ||
                (root->symbol != nullptr && root->symbol->type == SYMBOL_VARIABLE && root->symbol->datatype ==
                 DATATYPE_CHAR)
            );
}

int Semantic::getType(const Node *root) {
    if (is_number(root)) {
        return DATATYPE_INT;
    }
    if (is_char(root)) {
        return DATATYPE_CHAR;
    }
    if (is_bool(root)) {
        return DATATYPE_BOOL;
    }
    return DATATYPE_NONE;
}

int Semantic::checkTypeCompatibility(int type1, int type2) {
    return

            (type1 == type2) ||
            (type1 == DATATYPE_CHAR && type2 == DATATYPE_INT) ||
            (type1 == DATATYPE_INT && type2 == DATATYPE_CHAR);
}

int Semantic::get_return_type(Node *root) {
    int type = DATATYPE_NONE;
    if (root == nullptr) {
        return DATATYPE_NONE;
    }
    if (root->type == NODE_RETURN) {
        if (is_number(root->children[0])) {
            return DATATYPE_INT;
        }
        return DATATYPE_CHAR;
    }
    for (const auto &child: root->children) {
        type = get_return_type(child);
        if (type != DATATYPE_NONE) {
            return type;
        }
    }
    return type;
}


int Semantic::count_vector_size(Node *node) {
    if (node == nullptr) return 0;
    if (node->type != NODE_LIT_VEC) {
        return 0;
    }
    int count = 1;
    Node *curr = node;
    while (curr->children[1] != nullptr && curr->type == NODE_LIT_VEC) {
        count++;
        curr = curr->children[1];
    }
    return count;
}


int Semantic::check_vector_size(const Node *node) {
    return true;
}

int Semantic::get_vector_type(Node *node) {
    if (node == nullptr) return 0;
    if (node->type != NODE_LIT_VEC) {
        return 0;
    }
    u_int8_t first_datatype = DATATYPE_NONE;
    if (is_number(node->children[0])) {
        first_datatype = DATATYPE_INT;
    } else if (is_char(node->children[0])) {
        first_datatype = DATATYPE_CHAR;
    }
    u_int8_t current_type = DATATYPE_NONE;
    Node *curr = node;
    while (curr->children[1] != nullptr && curr->type == NODE_LIT_VEC) {
        if (is_number(node->children[0])) {
            current_type = DATATYPE_INT;
        } else if (is_char(node->children[0])) {
            current_type = DATATYPE_CHAR;
        }
        if (current_type != first_datatype) {
            return DATATYPE_NONE;
        }
        curr = curr->children[1];
    }
    return first_datatype;
}

Node *Semantic::getFunctionParams(Node *root, Symbol *symbol) {
    if (root == nullptr || symbol == nullptr) return nullptr;
    Node *lparams;
    if (root->symbol == symbol && root->type == NODE_DECFUNC) {
        return root->children[1];
    }
    for (const auto &child: root->children) {
        lparams = getFunctionParams(child, symbol);
        if (lparams != nullptr) {
            return lparams;
        }
    }
    return nullptr;
}

int Semantic::compareParams(Node *fparam, Node *cparam) {
    if (fparam == nullptr && cparam == nullptr) {
        return true;
    }
    if (fparam->children[0]->type == NODE_INT) {
        if (getType(cparam) == DATATYPE_INT) {
            return true;
        }
    }
    if (fparam->children[0]->type == NODE_CHAR) {
        if (getType(cparam->children[0]) == DATATYPE_CHAR) {
            return true;
        }
    }
    return false;
}


int Semantic::compareAllParams(Node *fparams, Node *callparams) {
    Node *func = fparams;
    Node *call = callparams;
    while (func != nullptr && call != nullptr) {
        if (!compareParams(func->children[0], call->children[0])) {
            return false;
        }
        func = func->children[1];
        call = call->children[1];
    }
    if (func != nullptr || call != nullptr) return false;
    return true;
}

int Semantic::getSemanticErrors() {
    return SemanticErrors;
}
