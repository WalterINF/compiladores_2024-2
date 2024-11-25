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

    static void check_and_set_declarations(Node *root);
    static void check_types(Node *root);
    static void check_undeclared(SymbolTable table);
    static void check_operands(Node *root);
    static void check_usage(Node *root);
    static void check_calls(Node *root, Node *current_node);
    static int getSemanticErrors();

private:
    static int is_bool(const Node *root);
    static int is_number(const Node *root);
    static int is_char(const Node *root);
    static int checkTypeCompatibility(int type1, int type2);
    static int get_return_type(Node *root);
    static int count_vector_size(Node *node);
    static int check_vector_size(const Node *node);
    static int get_vector_type(Node *node);
    static int getType(const Node *root);
    static Node* getFunctionParams(Node *root, Symbol *symbol);
    static int compareAllParams(Node *node1, Node *node2);
    static int compareParams(Node *fparam, Node *cparam);
};


#endif //SEMANTIC_H
