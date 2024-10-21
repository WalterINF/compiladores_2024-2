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


//programa: lista de declarações
program : ldeclarations
    |
    ;

type : KW_CHAR
     | KW_INT
     ;

//valor literal
literal : LIT_INT
        | LIT_CHAR
        ;

//lista de declarações
ldeclarations : declaration ldeclarations
    |
    ;

//declaração
declaration : type TK_IDENTIFIER "=" LIT_INT ";"
            | type TK_IDENTIFIER "=" LIT_CHAR ";"
            | type TK_IDENTIFIER "[" LIT_INT "]" ";"
            | type TK_IDENTIFIER "[" LIT_INT "]" "=" lit_vector ";"
            | function
            ;

//vetores
lit_vector : literal lit_vector
      |
      ;

//parametros podem ser uma lista ou vazio
params : lparams
       | type TK_IDENTIFIER
       |
       ;

//lista de parametros
lparams : type TK_IDENTIFIER "," lparams
        | type TK_IDENTIFIER
        ;

//funções
function : type TK_IDENTIFIER "(" params ")" block

//bloco
block : "{" lcmds "}"
      ;

//lista de comandos
lcmds : cmd lcmds
      |
      ;

//comandos
cmd : TK_IDENTIFIER "=" expr ";"
     | TK_IDENTIFIER "[" expr "]" "=" expr ";"
     | KW_READ TK_IDENTIFIER ";"
     | KW_PRINT lexpr_str ";"
     | KW_RETURN expr ";"
     | block
     | KW_WHILE "(" expr ")" cmd
     | KW_IF "(" expr ")" KW_THEN cmd
     | KW_IF "(" expr ")" KW_THEN cmd KW_ELSE cmd
     | ";"
     ;


//expressoes
expr : literal
     | TK_IDENTIFIER
     | expr op expr
     | TK_IDENTIFIER "[" expr "]"
     | TK_IDENTIFIER "(" lcallparams ")"
     ;

//lista de expressões
lexpr : expr lexpr
      |
      ;

//lista de expressões ou strings
lexpr_str : expr lexpr_str
          | LIT_STRING lexpr_str
          |
          ;

//lista de parametros de chamada de função
callparams : lcallparams
           | expr
           |
           ;

lcallparams : expr "," lcallparams
        | expr
        ;

op : "+"
   | "-"
   | "*"
   | "/"
   | "<"
   | ">"
   | "="
   | "&"
   | "|"
   | "~"
   ;



%%

int yyerror(char *err){

	fprintf(stderr, "ERROR in line = %d\n", getLineNumber());
	return 3;
}
