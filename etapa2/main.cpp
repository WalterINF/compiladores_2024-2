/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
 */

#include <iostream>
#include <stdio.h>
#include <map>
#include <string>
#include "Symbols.h"

int yylex();
extern char *yytext;
extern FILE *yyin;
extern int yyparse();
extern SymbolTable symbol_table;
int getLineNumber();
int isRunning(void);

int main(int argc, char** argv){
	if (argc < 2){
		std::cout << "Número incorreto de argumentos" << std::endl;
		return 1;
    }

    yyin = fopen(argv[1], "r");
    if(yyin == NULL){
    	std::cout << "Não foi possível abrir o arquivo: " << argv[1] << std::endl;
      	return 1;
    }

    printf("\n%d",yyparse());

   	printf("----------Tabela de simbolos ---------\n");
	return 0;
}