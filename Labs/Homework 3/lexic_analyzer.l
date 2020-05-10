%{ 
#include<stdio.h> 
#include<string.h> 
FILE *fr, *fw;
%} 

%%
"//".*\n ; // ignore comments
\n fprintf(fw, "\n"); // new lines

[0-9]+ fprintf(fw, "inum "); // integers
[0-9]+"."[0-9]* fprintf(fw, "fnum "); // floats
[a-eg-hj-oq-zA-EG-HJ-OQ-Z]+ fprintf(fw, "id ");

"i " fprintf(fw, "intdcl "); // int declarations
"f " fprintf(fw, "floatdcl "); // float declarations
"p " fprintf(fw, "print "); // float declarations

" "*"="" "* fprintf(fw, "assign "); // assignations
" "*"+"" "* fprintf(fw, "plus "); // addition
" "*"-"" "* fprintf(fw, "minus "); // subtraction
" "*"*"" "* fprintf(fw, "times "); // multiplication
" "*"/"" "* fprintf(fw, "divby "); // division
%%
  
int yywrap(void){} 
  
int main(int argc, char *argv[])
{    
    if(argc < 2){
        printf("Usage: ./lexic_analyzer <file>\n");
        return 1;
    }

    fr = fopen(argv[1], "r");
    fw = fopen("lex.out", "w");

    int c;

    yyset_in(fr);
    yylex(); 

    fclose(fr);
    fclose(fw);
  
    return 0; 
} 