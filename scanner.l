%{
#include <stdio.h>
#include <string.h>
#include "tokens.h"

int line_count = 0;
%}

NEWLINE \\n
IDENTIFIER [a-zA-Z0-9]+
LITERAL_NUM [#][0-9]+
LITERAL_CHAR '(.|\\.)'
LITERAL_STRING \"([^\"\\]|\\.)*\"
SPEC_CHAR [;,():\[\]{}=+\-*/%<>&\\~]
INLINE_COMMENT \/\/(.*?)\\n
MULTILINE_COMMENT \/\*\*(.*?)\*\*\/

%%




\\n {line_count++; printf("nova linha");} 
char {printf("palavra char");}
int {printf("palavra read");}
if {printf("comando if");}
then {printf("comando then");}
else {printf("comando else");}
while {printf("comando while");}
read {printf("comando read");}
print {printf("comando print");}
return {printf("comando return");}

[#][0-9]+ {printf("literal numero");}

\"([^\"\\]|\\.)*\" {printf("literal string");}

'(.|\\.)' {printf("literal caractere");}

[;,():\[\]{}=+\-*/%<>&\\~] {printf("%d",yytext[0]);}

\/\/(.*?)\\n {printf("comentario");}

\/\*\*(.*?)\*\*\/ {printf("comentario multilinha");}

[a-zA-Z0-9]+ {printf("identificador");}




%%


int yywrap(){
  return 1;
}

main(){
  yylex();
}




