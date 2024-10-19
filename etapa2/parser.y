%{
/*
Etapa2 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
 */
#include <stdio.h>
#include <string.h>

    int yylex();
	int yyerror(char *message);
	extern int getLineNumber();
%}

%token KW_CHAR
%token KW_INT

%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_READ
%token KW_PRINT
%token KW_RETURN

%token TK_IDENTIFIER

%token LIT_INT
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%start program

%%

//tipos
type : KW_CHAR
     | KW_INT
     ;

//valor literal
literal : LIT_INT
        | LIT_CHAR
        ;

//programa: lista de declarações
program : ldeclarations
    |
    ;

//lista de declarações
ldeclarations : declaration ldeclarations
    |
    ;

//declaração
declaration : type TK_IDENTIFIER "==" LIT_INT ";"
            | type TK_IDENTIFIER "==" LIT_CHAR ";"
            | type TK_IDENTIFIER "[" LIT_INT "]" ";"
            | type TK_IDENTIFIER "[" LIT_INT "]" "==" vector ";"
            ;



//vetores
vector : literal vector
      |
      ;

//parametros podem ser uma lista ou vazio
params : lparams
       |
       ;

//lista de parametros
lparams : type TK_IDENTIFIER "," lparams
        |
        ;

//funções
function : type TK_IDENTIFIER "(" params ")" block

//bloco
block : "{" ldeclarations "}"
      ;

cmd : TK_IDENTIFIER "=" expr
    | TK_IDENTIFIER "[" expr "]" "=" expr
    | KW_READ TK_IDENTIFIER
    | KW_PRINT
    | KW_RETURN expr
    |
    ;


expr : literal
     |
     ;

%%

int yyerror(char *err){

	fprintf(stderr, "ERROR in line = %d\n", getLineNumber());
	return 3;
}
