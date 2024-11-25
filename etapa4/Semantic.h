//
// Created by walter on 11/23/24.
//

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "Ast.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"
#include "Symbols.h"

/*
• variáveis redeclaradas X
• anotar tipo (natureza) nas tabela de símbolos X
• anotar tipo de dado (dataType) na tabela de símbolos X
• variáveis não-declaradas X
• verificar natureza, se:
- escalares são usados como escalares X
- vetores são usados como vetores X
- funções são usadas como funções X
- não esqueça de verificar no lado direito (expressões) e no lado esquerdo
(atribuições) X
• verificar tipos de dados nas expressões
• verificar argumentos de chamada de função versus parâmetros:
- não pode haver menos argumentos
- não pode haver mais argumentos
- os tipos devem ser compatíveis (não iguais, lembre-se)
• verificar o tamanho e a lista de inicialização do vetor; X
• verificar tipo do valor de retorno da função
• verificar índices dos vetores (não pode ser booleano), tanto na expressão quanto na
atribuição X
*/


extern int semantic_errors;


class Semantic {
public:
    static void verify();

    static void check_and_set_declarations(Node *root);

    static int check_undeclared(SymbolTable table);

    static void check_operands(Node *root);

    static int isRelationalOp(Node *root) {
        return
                root != nullptr && (
                    root->type == NODE_EQ ||
                    root->type == NODE_OR ||
                    root->type == NODE_LESS ||
                    root->type == NODE_GREATER ||
                    root->type == NODE_AND ||
                    root->type == NODE_TIL);
    }

    static int is_number(Node *root) {
        return
                root != nullptr && (
                    root->type == NODE_SUM ||
                    root->type == NODE_DIV ||
                    root->type == NODE_MUL ||
                    root->type == NODE_SUB ||
                    (root->type == NODE_SYMBOL && root->symbol != nullptr && root->symbol->type == SYMBOL_LIT_INT) ||
                    (root->symbol != nullptr && root->symbol->type == SYMBOL_VARIABLE && root->symbol->datatype ==
                     DATATYPE_INT) ||
                    (root->type == NODE_CALL && root->symbol != nullptr && root->symbol->datatype == DATATYPE_INT));
        //falta acesso a vetores
    }

    static int is_char(Node *root) {
        return
        root != nullptr && (
            root->type == NODE_CHAR ||
            (root->type == NODE_SYMBOL && root->symbol != nullptr && root->symbol->type == SYMBOL_LIT_CHAR) ||
            (root->type == NODE_CALL && root->symbol != nullptr && root->symbol->datatype == DATATYPE_CHAR) ||
            (root->symbol != nullptr && root->symbol->type == SYMBOL_VARIABLE && root->symbol->datatype == DATATYPE_CHAR)
            );
        //falta acesso a vetores
    }

    static int check_type(int type1, int type2) {
        return
                (type1 == type2) ||
                ((type1 == SYMBOL_LIT_INT && type2 == DATATYPE_INT) || (
                     type1 == DATATYPE_INT && type2 == SYMBOL_LIT_INT)) ||
                ((type1 == SYMBOL_LIT_CHAR && type2 == DATATYPE_CHAR) || (
                     type1 == DATATYPE_CHAR && type2 == SYMBOL_LIT_CHAR));
    }

    static int get_return_type(Node *root) {
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

    static int count_vector_size(Node *node) {
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


    static int check_vector_size(Node *node) {
        if (node == nullptr) return 0;
        if (node->type != NODE_DECVEC) {
            return 0;
        }
        int init_size = count_vector_size(node->children[2]);
        //printf("Vector is initialized with %d elements\n",init_size);

        //Jesus amado
        std::string str = node->children[1]->symbol->name.substr(1, node->symbol->name.size() - 1);
        int vector_size = stoi(str);
        //printf("Vector has %d elements\n",vector_size);
        return init_size == vector_size;
    }


#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_STRING 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_IDENTIFIER 4

    //após verificação semântica, SYMBOL_IDENTIFIER é substituído por um dos seguintes
#define SYMBOL_VARIABLE 5
#define SYMBOL_FUNCTION 6
#define SYMBOL_VECTOR 7

#define DATATYPE_INT 8
#define DATATYPE_CHAR 9

    static void check_usage(Node *root);
};


#endif //SEMANTIC_H
