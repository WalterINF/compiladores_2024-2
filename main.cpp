/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
 */

#include <iostream>
#include <stdio.h>
#include "tokens.h"
#include <map>
#include <string>

int yylex();
extern char *yytext;
extern FILE *yyin;
extern std::map<std::string,int> symbol_table;
extern void insertSymbol(std::map<std::string, int> *table, char* symbol, int type);
extern void printSymbols(std::map<std::string, int> table);


int getLineNumber();
int isRunning(void);

int main(int argc, char** argv){

	int kw;

	if (argc < 2){
		std::cout << "Número incorreto de argumentos" << std::endl;
		return 1;
    }

    yyin = fopen(argv[1], "r");
    if(yyin == NULL){
    	std::cout << "Não foi possível abrir o arquivo: " << argv[1] << std::endl;
      	return 1;
    }

	while(isRunning()){

		kw = yylex();
		if (!isRunning())
      		break;

		switch(kw){
            case KW_CHAR: fprintf(stderr, "KW_CHAR (%s) on line: %d\n",yytext, getLineNumber()); break;
			case KW_INT:  fprintf(stderr, "KW_INT (%s) on line: %d \n", yytext, getLineNumber()); break;
   			case KW_IF:   fprintf(stderr, "KW_IF (%s) on line: %d \n", yytext, getLineNumber()); break;
   			case KW_THEN: fprintf(stderr, "KW_THEN (%s) on line: %d \n", yytext, getLineNumber()); break;
   			case KW_ELSE: fprintf(stderr, "KW_ELSE (%s) on line: %d \n", yytext, getLineNumber()); break;
            case KW_WHILE: fprintf(stderr, "KW_WHILE (%s) on line: %d \n", yytext, getLineNumber()); break;
   			case KW_READ: fprintf(stderr, "KW_READ (%s) on line: %d \n", yytext, getLineNumber()); break;
   			case KW_RETURN: fprintf(stderr, "KW_RETURN (%s) on line: %d \n", yytext, getLineNumber()); break;
   			case KW_PRINT: fprintf(stderr, "KW_PRINT (%s) on line: %d \n", yytext, getLineNumber()); break;
   			case TK_IDENTIFIER: fprintf(stderr, "TK_IDENTIFIER (%s) on line: %d \n", yytext, getLineNumber()); break;
   			case LIT_INT: fprintf(stderr, "LIT_INT (%s) on line: %d \n", yytext, getLineNumber()); break;
   			case LIT_STRING: fprintf(stderr, "LIT_STRING (%s) on line: %d \n", yytext, getLineNumber()); break;
			case LIT_CHAR: fprintf(stderr, "LIT_CHAR (%s) on line: %d \n", yytext, getLineNumber()); break;
   			case TOKEN_ERROR: fprintf(stderr, "TOKEN_ERROR (%s) on line: %d \n", yytext, getLineNumber()); break;
			default: fprintf(stderr, "CARACTERE ESPECIAL (%s) on line: %d \n", yytext, getLineNumber()); break;
		}
	}
    printSymbols(symbol_table);
	return 0;
}

/*
int main(void){

  std::map<std::string, int> table;
  insertSymbol(&table,"hello4",1);
  insertSymbol(&table,"hello5",2);
  insertSymbol(&table,"hello6",3);
  printSymbols(table);
  printf("\n--fim da tabela--\n");
  return 0;
}
*/
