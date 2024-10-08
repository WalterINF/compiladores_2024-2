%{

#include <stdio.h>
#include <string.h>
#include "tokens.h"

int line_count = 0;

%}

%x MULTILINE_COMMENT


%%


\\n                        { line_count++; }  
char                       { printf("palavra char"); }
int                        { printf("palavra read"); }
if                         { printf("comando if"); }
then                       { printf("comando then"); }
else                       { printf("comando else"); }
while                      { printf("comando while"); }
read                       { printf("comando read"); }
print                      { printf("comando print"); }
return                     { printf("comando return"); }
[#][0-9]+                  { printf("literal numero"); }
\"([^\"\\]|\\.)*\"         { printf("literal string"); }
'(.|\\.)'                  { printf("literal caractere"); }
[;,():\[\]{}=+\-*/%<>&\\~] { printf("%d",yytext[0]); }
\/\/(.*?)\\n               { printf("comentario"); }
"/**"                      { BEGIN(MULTILINE_COMMENT); }
[a-zA-Z0-9]+               { printf("identificador"); }

<MULTILINE_COMMENT>"**/"   { BEGIN(INITIAL); }
<MULTILINE_COMMENT>.       { }
<MULTILINE_COMMENT>\\n     { line_count++; }


%%


int yywrap()
{
  return 1;
}

main()
{
  yylex();
}