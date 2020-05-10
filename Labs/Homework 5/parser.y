%{ 
  #include <stdio.h> 
  #include <stdlib.h> 
  extern FILE *yyin;
 %} 
  
%token A 
%token B
%token C
%token C_END 
  
%% 
stmt: A S C_END {printf("Successfuly parsed token.\n"); exit(0);} 
;
S : B C
  | B 
;
%% 
  
int yyerror(char *msg) 
{ 
  printf("Failed to parse token.\n"); 
  exit(1);
} 
  
  
main()
{ 
   printf("Enter a token: \n"); 
   yyparse();
} 