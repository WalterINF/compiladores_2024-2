//
// Created by walter on 08/10/24.
//

#include <iostream>
#include "Symbols.h"
#include <stdio.h>
#include "tokens.h"

int yylex();
extern char *yytext;
extern FILE *yyin;

int getLineNumber();
int isRunning(void);

int main(int argc, char** argv){

	int tok;

	if (argc < 2){
		printf("call: ./etapa1 input.txt\n");
		exit(1);
    }
  	if (0 == (yyin = fopen(argv[1], "r"))){
		printf("Cannot open file %s... \n",argv[1]);
		exit(1);
    }

	while(isRunning()){

		tok = yylex();
		if (!isRunning())
      		break;

		switch(tok){
			case KW_INT:  fprintf(stderr, "KW_INT na linha %d. - tok: %d \n", getLineNumber(), tok); break;
   			case KW_IF:   fprintf(stderr, "KW_IF na linha %d. - tok: %d \n", getLineNumber(), tok); break;
   			case KW_THEN: fprintf(stderr, "KW_THEN na linha %d. - tok: %d \n", getLineNumber(), tok); break;
   			case KW_ELSE: fprintf(stderr, "KW_ELSE na linha %d. - tok: %d \n", getLineNumber(), tok); break;
   			case KW_READ: fprintf(stderr, "KW_READ na linha %d. - tok: %d \n", getLineNumber(), tok); break;
   			case KW_RETURN: fprintf(stderr, "KW_RETURN na linha %d. - tok: %d \n", getLineNumber(), tok); break;
   			case KW_PRINT: fprintf(stderr, "KW_PRINT na linha %d. - tok: %d \n", getLineNumber(), tok); break;
   			case TK_IDENTIFIER: fprintf(stderr, "TK_IDENTIFIER na linha %d. - tok: %d \n", getLineNumber(), tok); break;
   			case LIT_INT: fprintf(stderr, "LIT_INTEGER na linha %d. - tok: %d \n", getLineNumber(), tok); break;
   			case LIT_STRING: fprintf(stderr, "LIT_STRING na linha %d. - tok: %d \n", getLineNumber(), tok); break;
			case LIT_CHAR: fprintf(stderr, "LIT_CHAR na linha %d. - tok: %d \n", getLineNumber(), tok); break;
   			case TOKEN_ERROR: fprintf(stderr, "TOKEN_ERROR na linha %d. - tok: %d \n", getLineNumber(), tok); break;
			default: fprintf(stderr, "Caracter especial na linha %d. - tok: %d \n", getLineNumber(), tok); break;
		}
	}
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
