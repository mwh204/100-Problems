#include<stdio.h>
#include<string.h>

#include "name.h"

#define REPL "_/"

void space(void){
    int i;
    for(i=0; i<strlen(REPL); i++){
        putchar(' ');
    }
}

char translatePos(char a){
    if(a >= '0' && a <= '9'){ return a - '0';
    }else if((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')){return (a - 'a') + 10;
    }else if(a==' '){ return 36;
    }else return 37;

}

void printLetter(char a, int i){
    int j;
    for(j=0; j<WIDTH; j++){
        LETTERS[(int)translatePos(a)][i][j] == ORIG ? printf(REPL) : space();
    }
    space();
}

void printWord(char* str){
    int i,j;
    for(i=0; i<HEIGHT; i++){
        for(j=0; j<strlen(str); j++){
            printLetter(str[j], i);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    int i;
    if(argc<2){
        printWord("no arguments");
    }else{
        for(i=1; i<argc; i++){
            printWord(argv[i]);
        }
    }
}
