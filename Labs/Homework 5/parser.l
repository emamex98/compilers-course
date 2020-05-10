%{ 
#include "y.tab.h"
%} 

%%
"a" {return A;} 
"b" {return B;}
"c" {return C;}
"c\n" {return C_END;}
%%
  
int yywrap(void){} 