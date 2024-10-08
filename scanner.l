%{
#include <stdio.h>
#include <string.h>
#include "tokens.h"
#include "Symbols.h"

int line_count = 0;
int is_running = 1;
%}


%x MULTILINE_COMMENT


%%

\\n                        { line_count++;}
char                       {return KW_CHAR;}
int                        {return KW_INT;}
if                         {return KW_IF;}
then                       {return KW_THEN;}
else                       {return KW_ELSE;}
while                      {return KW_WHILE;}
read                       {return KW_READ;}
print                      {return KW_PRINT;}
return                     {return KW_RETURN;}
[#][0-9]+                  {return LIT_INT;}
\"([^\"\\]|\\.)*\"         {return LIT_STRING;}
'(.|\\.)'                  {return LIT_CHAR;}
[;,():\[\]{}=+\-*/%<>&\\~] {return (int)yytext[0];}
\/\/(.*?)\\n
"/**"                      { BEGIN(MULTILINE_COMMENT); }
[a-zA-Z0-9]+               {TK_IDENTIFIER;}

<MULTILINE_COMMENT>\\n     { line_count++; }
<MULTILINE_COMMENT>"**/"   { BEGIN(INITIAL); }
<MULTILINE_COMMENT>.       { }

[a-zA-Z0-9]+ {TK_IDENTIFIER;}

%%

int getLineNumber(void){
	return line_count;
}

int isRunning(void){
	return is_running;
}

int yywrap(){
    is_running = 0;
    return 1;
}





