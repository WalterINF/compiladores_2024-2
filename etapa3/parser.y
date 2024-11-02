%{
/*
Etapa2 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
 */


#include <stdio.h>
#include <string.h>
#include "Ast.h"


    int yylex();
	int yyerror(char *message);
	extern int getLineNumber();

	Node *root = NULL;
%}

%union{
	Symbol *symbol;
	Node *tree;
}

%token KW_CHAR
%token KW_INT

%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_READ
%token KW_PRINT
%token KW_RETURN

%token <symbol> TK_IDENTIFIER

%token <symbol> LIT_INT
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING

%token TOKEN_ERROR

%left '|' '~'
%left '=' '&'
%left '<' '>'
%left '+' '-'
%left '*' '/'

%type <tree> program
%type <tree> literal
%type <tree> ldeclarations
%type <tree> declaration
%type <tree> lit_vector
%type <tree> param
%type <tree> lparams
%type <tree> tail
%type <tree> block
%type <tree> lcmds
%type <tree> cmd
%type <tree> expr
%type <tree> lexpr_str
%type <tree> lcallparams
%type <tree> type

%start program

%%


//programa: lista de declarações
program : ldeclarations {root=$$;}
    | {$$=NULL;}
    ;



//valor literal
literal : LIT_INT   {$$=NULL;}
        | LIT_CHAR  {$$=NULL;}
        ;

//lista de declarações
ldeclarations : declaration ldeclarations {$$=Node::createNode(NODE_LDEC,NULL,$1,$2,NULL,NULL);}
    | {$$=NULL;}
    ;

//declaração
declaration : type TK_IDENTIFIER '=' LIT_INT ';' {$$=Node::createNode(NODE_DECVAR,$2,$1,Node::createNode(NODE_INT,$4,NULL,NULL,NULL,NULL),NULL,NULL);}
            | type TK_IDENTIFIER '=' LIT_CHAR ';' {$$=Node::createNode(NODE_DECVAR,$2,$1,Node::createNode(NODE_CHAR,$4,NULL,NULL,NULL,NULL),NULL,NULL);}
            | type TK_IDENTIFIER '[' LIT_INT ']' ';' {$$=Node::createNode(NODE_DECVAR,$2,$1,Node::createNode(NODE_INT,$4,NULL,NULL,NULL,NULL),NULL,NULL);}
            | type TK_IDENTIFIER '[' LIT_INT ']' '=' lit_vector ';' {$$=Node::createNode(NODE_DECVAR,$2,$1,Node::createNode(NODE_INT,$4,NULL,NULL,NULL,NULL),NULL,NULL);}
            | type TK_IDENTIFIER '(' lparams ')' block {$$=Node::createNode(NODE_DECFUNC,$2,$1,$4,$6,NULL);}
            ;

//vetores
lit_vector : {$$=NULL;}
           | literal lit_vector {$$=Node::createNode(NODE_LIT_VEC,NULL,$1,$2,NULL,NULL);}
           ;

//parametros podem ser uma lista ou vazio
param : type TK_IDENTIFIER {$$=NULL;} {$$=Node::createNode(NODE_PARAM,$2,$1,NULL,NULL,NULL);}
      ;

//lista de parametros
lparams : param tail {$$=NULL;}
	    | param {$$=NULL;}
	    | {$$=NULL;}
	    ;
	
tail : ',' tail {$$=NULL;}
     | param {$$=NULL;}
     ;


//bloco
block : '{' lcmds '}' {$$=Node::createNode(NODE_BLOCK,NULL,$2,NULL,NULL,NULL);}
      ;

//lista de comandos
lcmds : cmd lcmds {$$=NULL;}
      | {$$=NULL;}
      ;

//comandos
cmd : TK_IDENTIFIER '=' expr ';' {$$=NULL;}
     | TK_IDENTIFIER '[' expr ']' '=' expr ';' {$$=NULL;}
     | KW_READ TK_IDENTIFIER ';' {$$=NULL;}
     | KW_PRINT LIT_STRING lexpr_str ';' {$$=NULL;}
     | KW_RETURN expr ';' {$$=NULL;}
     | block {$$=NULL;}
     | KW_WHILE '(' expr ')' cmd {$$=NULL;}
     | KW_IF '(' expr ')' KW_THEN cmd {$$=NULL;}
     | KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmd {$$=NULL;}
     | ';' {$$=NULL;}
     ;

//expressoes
expr : '(' expr ')' {$$=NULL;}
     | literal {$$=NULL;}
     | TK_IDENTIFIER {$$=NULL;}
     | expr "+" expr {$$=NULL;}
     | expr "-" expr {$$=NULL;}
     | expr "*" expr {$$=NULL;}
     | expr "/" expr {$$=NULL;}
     | expr "<" expr {$$=NULL;}
     | expr ">" expr {$$=NULL;}
     | expr "=" expr {$$=NULL;}
     | expr "&" expr {$$=NULL;}
     | expr "|" expr {$$=NULL;}
     | expr "~" expr {$$=NULL;}
     | TK_IDENTIFIER '[' expr ']' {$$=NULL;}
     | TK_IDENTIFIER '(' lcallparams ')' {$$=NULL;}
     ;

//lista de expressões ou strings
lexpr_str : expr lexpr_str {$$=NULL;}
          | LIT_STRING lexpr_str {$$=NULL;}
          | {$$=NULL;}
          ;

//lista de parametros de chamada de função
lcallparams : lcallparams ',' expr {$$=NULL;}
            | expr {$$=NULL;}
            ;

type : KW_CHAR {$$=NULL;}
     | KW_INT {$$=NULL;}
     ;


%%

int yyerror(char *err){
	fprintf(stderr, "error in line = %d\n", getLineNumber());
	return 3;
}
