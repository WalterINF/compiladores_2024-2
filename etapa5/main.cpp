/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include "Ast.h"
#include "Tac.h"

int yylex();
extern char *yytext;
extern FILE *yyin;
extern int yyparse();
int getLineNumber();
Node *getAst();
int isRunning();


int main(int argc, char** argv){
	if (argc < 2){
		std::cout <<  "Usage: ./etapa5 [FILEPATH]" << std::endl;
		exit(1);
    }

    yyin = fopen(argv[1], "r");
    if(yyin == nullptr){
    	std::cout << "Não foi possível abrir o arquivo: " << argv[1] << std::endl;
      	exit(2);
    }

    if(yyparse())
      exit(3);

	std::cout << "Parsed Successfully!" << std::endl;

	Node* tree = getAst();
	Tac *result = nullptr;
	result = Tac::generateCode(tree);
	result->printList();

	return 0;
}