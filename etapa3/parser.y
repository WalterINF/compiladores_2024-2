%{
/*
Etapa2 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
 */


#include <stdio.h>
#include <string.h>
#include "Ast.h"

    Node* getAst();
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
%type <tree> ptail
%type <tree> block
%type <tree> lcmds
%type <tree> cmd
%type <tree> expr
%type <tree> lexpr_str
%type <tree> expr_or_str
%type <tree> lcallparams
%type <tree> ctail
%type <tree> type

%start program

%%



//programa: lista de declarações
program : ldeclarations {root=$$;}
    | {$$=NULL;}
    ;

//valor literal
literal : LIT_INT   {$$=Node::createNode(NODE_SYMBOL,$1,NULL,NULL,NULL,NULL);}
        | LIT_CHAR  {$$=Node::createNode(NODE_SYMBOL,$1,NULL,NULL,NULL,NULL);}
        ;

//lista de declarações
ldeclarations : declaration ldeclarations {$$=Node::createNode(NODE_LDEC,NULL,$1,$2,NULL,NULL);}
    | {$$=NULL;}
    ;

//declaração
declaration : type TK_IDENTIFIER '=' literal ';' {$$=Node::createNode(NODE_DECVAR,$2,$1,$4,NULL,NULL);}
            | type TK_IDENTIFIER '[' LIT_INT ']' ';' {$$=Node::createNode(NODE_DECVEC,$2,$1,Node::createNode(NODE_SYMBOL,$4,NULL,NULL,NULL,NULL),NULL,NULL);}
            | type TK_IDENTIFIER '[' LIT_INT ']' '=' lit_vector ';' {$$=Node::createNode(NODE_DECVEC,$2,$1,Node::createNode(NODE_SYMBOL,$4,NULL,NULL,NULL,NULL),$7,NULL);}
            | type TK_IDENTIFIER '(' lparams ')' block {$$=Node::createNode(NODE_DECFUNC,$2,$1,$4,$6,NULL);}
            ;
//vetores
lit_vector : {$$=NULL;}
           | literal lit_vector {$$=Node::createNode(NODE_LIT_VEC,NULL,$1,$2,NULL,NULL);}
           ;

//parametros podem ser uma lista ou vazio
param : type TK_IDENTIFIER {$$=Node::createNode(NODE_PARAM,$2,$1,NULL,NULL,NULL);}
      ;

//lista de parametros
lparams : param ptail {$$=Node::createNode(NODE_LPARAMS,NULL,$1,$2,NULL,NULL);}
	    | {$$=NULL;}
	    ;
	
ptail : ',' param ptail {$$=Node::createNode(NODE_LPTAIL, NULL, $2, $3, NULL, NULL);}
     | {$$=NULL;}
     ;


//bloco
block : '{' lcmds '}' {$$=Node::createNode(NODE_BLOCK,NULL,$2,NULL,NULL,NULL);}
      ;

//lista de comandos
lcmds : cmd lcmds {$$=Node::createNode(NODE_LCMDS,NULL,$1,$2,NULL,NULL);}
      | {$$=NULL;}
      ;

//comandos
cmd : TK_IDENTIFIER '=' expr ';' {$$=Node::createNode(NODE_ATTR,$1,$3,NULL,NULL,NULL);}
     | TK_IDENTIFIER '[' expr ']' '=' expr ';' {$$=Node::createNode(NODE_VECATTR,$1,$3,$6,NULL,NULL);}
     | KW_READ TK_IDENTIFIER ';' {$$=Node::createNode(NODE_READ,$2,NULL,NULL,NULL,NULL);}
     | KW_PRINT lexpr_str ';' {$$=Node::createNode(NODE_PRINT,NULL,$2,NULL,NULL,NULL);}
     | KW_RETURN expr ';' {$$=Node::createNode(NODE_RETURN,NULL,$2,NULL,NULL,NULL);}
     | block {$$=$1;}
     | KW_WHILE '(' expr ')' cmd {$$=Node::createNode(NODE_WHILE,NULL,$3,$5,NULL,NULL);}
     | KW_IF '(' expr ')' KW_THEN cmd {$$=Node::createNode(NODE_IF,NULL,$3,$6,NULL,NULL);}
     | KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmd {$$=Node::createNode(NODE_IFELSE,NULL,$3,$6,$8,NULL);}
     | ';' {$$=NULL;}
     ;

//expressoes
expr : '(' expr ')' {$$=$2;}
     | literal {$$=$1;}
     | TK_IDENTIFIER {$$=Node::createNode(NODE_SYMBOL,$1,NULL,NULL,NULL,NULL);}
     | expr '+' expr {$$=Node::createNode(NODE_SUM,NULL,$1,$3,NULL,NULL);}
     | expr '-' expr {$$=Node::createNode(NODE_SUB,NULL,$1,$3,NULL,NULL);}
     | expr '*' expr {$$=Node::createNode(NODE_MUL,NULL,$1,$3,NULL,NULL);}
     | expr '/' expr {$$=Node::createNode(NODE_DIV,NULL,$1,$3,NULL,NULL);}
     | expr '<' expr {$$=Node::createNode(NODE_LESS,NULL,$1,$3,NULL,NULL);}
     | expr '>' expr {$$=Node::createNode(NODE_GREATER,NULL,$1,$3,NULL,NULL);}
     | expr '=' expr {$$=Node::createNode(NODE_EQ,NULL,$1,$3,NULL,NULL);}
     | expr '&' expr {$$=Node::createNode(NODE_AND,NULL,$1,$3,NULL,NULL);}
     | expr '|' expr {$$=Node::createNode(NODE_OR,NULL,$1,$3,NULL,NULL);}
     | expr '~' expr {$$=Node::createNode(NODE_TIL,NULL,$1,$3,NULL,NULL);}
     | TK_IDENTIFIER '[' expr ']' {$$=Node::createNode(NODE_VECACC,$1,$3,NULL,NULL,NULL);}
     | TK_IDENTIFIER '(' lcallparams ')' {$$=Node::createNode(NODE_CALL,$1,$3,NULL,NULL,NULL);}
     ;

//lista de expressões ou strings
lexpr_str : expr_or_str lexpr_str {$$=Node::createNode(NODE_PRINT_VEC,NULL,$1,$2,NULL,NULL);}
          | {$$=NULL;}
          ;

expr_or_str : expr {$$=$1;}
            | LIT_STRING {$$=Node::createNode(NODE_SYMBOL,$1,NULL,NULL,NULL,NULL);}
            ;

//lista de parametros de chamada de função

lcallparams : expr ctail {$$=Node::createNode(NODE_LCPARAMS,NULL,$1,$2,NULL,NULL);}
	    | {$$=NULL;}
	    ;

ctail : ',' expr ctail {$$=Node::createNode(NODE_LCPTAIL, NULL, $2, $3, NULL, NULL);}
     | {$$=NULL;}
     ;

type : KW_CHAR {$$=Node::createNode(NODE_CHAR,NULL,NULL,NULL,NULL,NULL);}
     | KW_INT {$$=Node::createNode(NODE_INT,NULL,NULL,NULL,NULL,NULL);}
     ;

%%

int yyerror(char *err){
	fprintf(stderr, "error in line = %d\n", getLineNumber());
	return 3;
}

Node* getAst(){
    return root;
}
