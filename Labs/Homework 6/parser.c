#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

#define NL 10
#define ERR 0

/*************
Grammar:
E ->  int | ( E ) | E + E | E - E | E * E

Grammar with no left recursion:
S -> (S)E | intE
E -> * SE | + SE | - SE | epsilon
*************/

char buffer[50];
char *tree_str;

int i = 0;
int j = 0;
int k = 0;

int p = 0;

int S();
int E();
char* T();

/// +++ PARSER +++ ///

int match(char c) {

    if (buffer[i] == c) {
        i++;
        return 1;
    }
    
    return ERR;
}

int E3() {

    if (buffer[i+1] == '*') {
        if (match(' ') && match('*') && match(' ') && S() && E()){
			return 1;
		}
    }

    return ERR;
}

int E2() {

    if (buffer[i+1] == '-') {
        if (match(' ') && match('-') && match(' ') && S() && E()){
			return 1;
		}
    }

    return ERR;
}

int E1() {

    if (buffer[i+1] == '+') {
        if (match(' ') && match('+') && match(' ') && S() && E()){
			return 1;
		}
    }

    return ERR;
}


int E() {
    
    if (buffer[i] != ' '){
        if (buffer[i] == 0 || buffer[i] == ')' || buffer[i] == '\n'){
            return 1;
        }
        return ERR;
    } else {
        if (E1()){
            return 1;
        } else if (E2()){
            return 1;
        } else if (E3()){
            return 1;
        }
    }

   return ERR;
}

int S2() {

    if (isdigit(buffer[i])) {
        if(match(buffer[i]) && E()) {
            return 1;
        }
    }

    return ERR;
}

int S1() {

    if (buffer[i] == '(') {
        p++;
        if(match('(') && S() && match(')') && E()) {
            return 1;
        }
    }

    return ERR; 
}

int S() {

    if(S1()){
        return 1;
    } else if (S2()){
        return 1;
    }

    printf("Failed to parse token.\n");
    exit(-1);
}

/// --- PARSER --- ///

/// +++ TREE GEN +++ ///

char* T(char str[]){

    for (int r = 0; r < strlen(str); r++) {

        if (str[r] == '('){

            char *tmp = malloc(50);
            int t = r+1;

            int start = r;
            int end = 0;

            for (int s = 0; s < strlen(str); s++) {
                if (str[t] == ')'){
                    end = t;
                    break;
                }
                tmp[s] = str[t];
                t++;
            }

            strcat(tree_str, T(tmp));
            str[start] = 'a';

            for (int s = start+1; s <= end; s++) {
                str[s] = 10;
            }

        } 

    }

    for (int r = 0; r < strlen(str); r++) {
        if(str[r] == 'a'){
            for (int s = r+1; s < 10; s++) {
                str[s] = 10;
            }
            break;
        }
    }

    for (int r = 0; r < strlen(str); r++) {

        if(str[r] == '*') {

            char *tmp4 = malloc(50);
            strcat(tmp4, "mul ");

            if(isdigit(str[r+2])){
                strncat(tmp4, &str[r-2], 1);
            } else {
                strcat(tmp4, "&acum");
            }
            
            strcat(tmp4, ",");

            if(isdigit(str[r+2])){
                strncat(tmp4, &str[r+2], 1);
            } else {
                strncat(tmp4, &str[r-2], 1);
            }

            strcat(tmp4, ",acum\n");
            strcat(tree_str, tmp4);
        }

        if(str[r] == '+') {

            char *tmp2 = malloc(50);
            strcat(tmp2, "add ");

            if(isdigit(str[r+2])){
                strncat(tmp2, &str[r-2], 1);
            } else {
                strcat(tmp2, "&acum");
            }
            
            strcat(tmp2, ",");

            if(isdigit(str[r+2])){
                strncat(tmp2, &str[r+2], 1);
            } else {
                strncat(tmp2, &str[r-2], 1);
            }

            strcat(tmp2, ",acum\n");
            strcat(tree_str, tmp2);

        }

        if(str[r] == '-') {

            char *tmp3 = malloc(50);
            strcat(tmp3, "sub ");

            if(isdigit(str[r-2])){
                strncat(tmp3, &str[r-2], 1);
                str[r-2] = 'a';
            } else {
                strcat(tmp3, "&acum");
            }
            
            strcat(tmp3, ",");

            if(isdigit(str[r+2])){
                strncat(tmp3, &str[r+2], 1);
                str[r+2] = 'a';
            } else {
                strcat(tmp3, "&acum");
            }

            strcat(tmp3, ",acum\n");
            strcat(tree_str, tmp3);
        }

    }

    return "";

}

/// --- TREE GEN --- ///

int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Usage: ./parser tokens.txt\n");
        exit(-1);
    }

    FILE *fp;
    fp = fopen(argv[1], "r");

    while (fgets(buffer, 500, (FILE*)fp)){
        printf("\n");
        i = 0;
        S();

        tree_str = malloc(50);
        T(buffer);

        printf("%s\n", tree_str);
    }


    fclose(fp);
    
}