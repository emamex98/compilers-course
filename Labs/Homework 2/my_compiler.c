#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE * fl = fopen(argv[1], "r");

    int stdLength = 250;
    int countSlash = 0;
    int top = 0;
    int stringFlag = 1;
    int line = 1;
    int lineStr = 0;
    int linePush[stdLength];

    char buffer[stdLength];
    char stack[stdLength];
    char openingQuotes = ' ';

    for(int i=0; i<=stdLength; i++){
        stack[i] = '-';
    }

    if (fl == NULL)
        exit(EXIT_FAILURE);

    while(fgets(buffer, stdLength, fl)) {

        for(int i=0; buffer[i] != '\0'; i++){

            char x = buffer[i];

            // Ignore comments
            if (x == '/') {
                countSlash++;
                if(countSlash == 2) {
                    countSlash = 0;
                    break;
                }
            } 

            // Handle quotation marks
            else if (x == '\"' || x == '\'') {
                if (openingQuotes == ' '){
                    lineStr = line;
                    openingQuotes = x;
                    stringFlag *= -1;
                } else if (openingQuotes == x) {
                    openingQuotes = ' ';
                    stringFlag *= -1;
                }
            }
            
            // Ignore characters inside string
            else if (stringFlag == 1) {

                // PUSH braquets and curly brackets to stack
                if(x == '{' || x == '(') {
                    //printf("PUSH %c \n", x);
                    stack[top] = x;
                    linePush[top] = line;
                    top++;
                }

                // POP ) from stack
                else if(x == ')'){
                    if (stack[top-1] == '(' && stack[top-1] != '-') { 
                        //printf("POP %c \n", x);
                        top--;
                        stack[top] = '-';
                    } else {
                        printf("FAILED TO COMPILE: \n");
                        printf("- Unexpected ) in line %d \n", line);
                        return -1;
                    }
                }

                // POP } from stack
                else if(x == '}'){
                    if (stack[top-1] == '{' && stack[top-1] != '-') { 
                        //printf("POP %c \n", x);
                        top--;
                        stack[top] = '-';
                    } else {
                        printf("FAILED TO COMPILE: \n");
                        printf("- Unexpected } in line %d \n", line);
                        return -1;
                    }
                }
            }
        }

        line++;
    }

    // Handle unclosed quotation marks
    if (stringFlag == -1) {
        printf("FAILED TO COMPILE: \n");
        printf("- Missing %c in line %d \n", openingQuotes, lineStr);
        return -1;
    }

    // Handle non-empty stack
    for(int i=0; i<stdLength; i++){
        if(stack[i] != '-'){
            printf("FAILED TO COMPILE: \n");
            printf("- Unexpected %c in line %d\n", stack[i], linePush[i]);
            return -1;
        }
    }

    return 0;
} 