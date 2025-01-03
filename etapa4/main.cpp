/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include "Symbols.h"
#include "Ast.h"
#include "Semantic.h"

int yylex();
extern char *yytext;
extern FILE *yyin;
extern int yyparse();
extern SymbolTable symbol_table;
int getLineNumber();
Node *getAst();
int isRunning();

int main(int argc, char** argv){
	if (argc < 2){
		std::cout << "Número incorreto de argumentos" << std::endl;
		exit(1);
    }

    yyin = fopen(argv[1], "r");
    if(yyin == nullptr){
    	std::cout << "Não foi possível abrir o arquivo: " << argv[1] << std::endl;
      	exit(2);
    }

    if(yyparse()){
      exit(3);
    } else {
    	std::cout << "Parsed Successfully!" << std::endl;
        //printf("----------Tabela de simbolos ---------\n");
        //std::cout << symbol_table;

    }

	Node* tree = getAst();

	Semantic::check_and_set_declarations(tree);
	Semantic::check_types(tree);
	Semantic::check_undeclared(symbol_table);
	Semantic::check_operands(tree);
	Semantic::check_usage(tree);
	Semantic::check_calls(tree,tree);

	int semanticErrors = Semantic::getSemanticErrors();
	if(semanticErrors > 0) {
		std::cout << "Error: " << semanticErrors << " error(s) found in file." << std::endl;
		exit(4);
	}

	tree->printTree();

	tree->decompileToFile(argv[2]);


	return 0;
}