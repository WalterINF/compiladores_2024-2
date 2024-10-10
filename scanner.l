%{
/*
Etapa1 - Trabalho Final - compiladores - 2024/2
Integrantes: Sandro Rudiero Saibro Viegas, Walter Frank
 */
#include <stdio.h>
#include <string.h>
#include "tokens.h"
#include "Symbols.h"

int is_running = 1;
int line_count = 1;

std::map<std::string,int> symbol_table;
%}

%x MULTILINE_COMMENT

%%

\n                         {line_count++;}
[ \t]                      { }
char                       {return KW_CHAR;}
int                        {return KW_INT;}
if                         {return KW_IF;}
then                       {return KW_THEN;}
else                       {return KW_ELSE;}
while                      {return KW_WHILE;}
read                       {return KW_READ;}
print                      {return KW_PRINT;}
return                     {return KW_RETURN;}

[#][0-9]+                  {insertSymbol(&symbol_table, &yytext[0], LIT_INT); return LIT_INT;}
\"([^\"\\]|\\.)*\"         {insertSymbol(&symbol_table, &yytext[0], LIT_STRING); return LIT_STRING;}
'(.|\\.)'                  {insertSymbol(&symbol_table, &yytext[0], LIT_CHAR); return LIT_CHAR;}

[;,():\[\]{}=+\-*/%<>&\\~] {return (int)yytext[0];}
\/\/(.*?)\n               {line_count++;}
"/**"                      {BEGIN(MULTILINE_COMMENT);}

<MULTILINE_COMMENT>\n     {line_count++;}
<MULTILINE_COMMENT>"**/"   {BEGIN(INITIAL);}
<MULTILINE_COMMENT>.       { }

[a-zA-Z0-9]+               {insertSymbol(&symbol_table, &yytext[0], TK_IDENTIFIER); return TK_IDENTIFIER;}

.                          {return TOKEN_ERROR;}


%%

int getLineNumber(void){
	return line_count;
}

int isRunning(void){
	return is_running;
}

void initMe(void){
    symbol_table.clear();
}

int yywrap(){
    is_running = 0;
    return 1;
}





