#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define NL 10
#define ERR 0

/*************
Grammar:
S -> aBc
B -> bc | b
*************/

char l;
char buffer[50];
int i = 0;
int b;
int out = 1;

struct Symbol {
    char c;
    Symbol *next;
};

struct SyntaxTree {

}

void printWGString(){

    char opf[50];
    strcpy(opf, buffer);
    strcat(opf, ".gv");

    FILE *fp;
    fp = fopen(opf, "w");

    fprintf(fp, "digraph G {\n");
    fprintf(fp, "\"S\" -> \"a\" \n\"S\" -> \"B\" \n\"S\" -> \"c \" \n");

    if(b == 1){
        fprintf(fp, "\"B\" -> \"b\" \n\"B\" -> \"c\" \n");
    } else {
        fprintf(fp, "\"B\" -> \"b\" \n");
    }
    fprintf(fp, "}\n\n");

    fclose(fp);
}

int match(char c) {

    if (buffer[i] == c) {
        i++;
        return 1;
    }
    
    return ERR;
}

int B2() {

    if (buffer[i] == 'b') {
        if (match('b')){
            b = 2;
			return 1;
		}
    }

    return ERR;
}

int B1() {

    if (buffer[i] == 'b') {
        if (match('b') && match('c') && buffer[i] != NL){
            b = 1;
			return 1;
		}
    }

    return ERR;
}


int B() {
    
    if (B1()) {
		return 1;
    } else {
        i = i-2;
        if (B2()) {
		    return 1;
        }
    }

   return ERR;
}


int S() {
    
    if (buffer[i] == 'a') {
        if (match('a') && B() && match('c') && buffer[i] == NL){
            printf("Successfuly parsed token.\n");
            printWGString();
			return 1;
		}
    }

    printf("Failed to parse token.\n");
    return ERR;
}

int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Usage: ./parser tokens.txt\n");
        exit(-1);
    }

    FILE *fp;
    fp = fopen(argv[1], "r");

    while (fgets(buffer, 500, (FILE*)fp)){
        printf("%s", buffer);
        i = 0;
        S();
    }
    
    fclose(fp);
    
}