#include<stdio.h>
#include<string.h>

#include "name.h"

#define REPL "_/"
#define SPACE "  "

void printLetter(char a, int i){
    int j;
    switch(a){
        case 'a':
        case 'A':
            for(j=0;j<WIDTH;j++)A[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'b':
        case 'B':
            for(j=0;j<WIDTH;j++)B[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'c':
        case 'C':
            for(j=0;j<WIDTH;j++)C[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'd':
        case 'D':
            for(j=0;j<WIDTH;j++)D[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'e':
        case 'E':
            for(j=0;j<WIDTH;j++)E[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'f':
        case 'F':
            for(j=0;j<WIDTH;j++)F[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'g':
        case 'G':
            for(j=0;j<WIDTH;j++)G[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'h':
        case 'H':
            for(j=0;j<WIDTH;j++)H[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'i':
        case 'I':
            for(j=0;j<WIDTH;j++)I[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'j':
        case 'J':
            for(j=0;j<WIDTH;j++)J[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'k':
        case 'K':
            for(j=0;j<WIDTH;j++)K[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'l':
        case 'L':
            for(j=0;j<WIDTH;j++)L[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'm':
        case 'M':
            for(j=0;j<WIDTH;j++)M[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'n':
        case 'N':
            for(j=0;j<WIDTH;j++)N[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'o':
        case 'O':
            for(j=0;j<WIDTH;j++)O[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'p':
        case 'P':
            for(j=0;j<WIDTH;j++)P[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'q':
        case 'Q':
            for(j=0;j<WIDTH;j++)Q[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'r':
        case 'R':
            for(j=0;j<WIDTH;j++)R[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 's':
        case 'S':
            for(j=0;j<WIDTH;j++)S[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 't':
        case 'T':
            for(j=0;j<WIDTH;j++)T[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'u':
        case 'U':
            for(j=0;j<WIDTH;j++)U[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'v':
        case 'V':
            for(j=0;j<WIDTH;j++)V[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'w':
        case 'W':
            for(j=0;j<WIDTH;j++)W[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'x':
        case 'X':
            for(j=0;j<WIDTH;j++)X[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'y':
        case 'Y':
            for(j=0;j<WIDTH;j++)Y[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case 'z':
        case 'Z':
            for(j=0;j<WIDTH;j++)Z[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case '0':
            for(j=0;j<WIDTH;j++)_0[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case '1':
            for(j=0;j<WIDTH;j++)_1[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case '2':
            for(j=0;j<WIDTH;j++)_2[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case '3':
            for(j=0;j<WIDTH;j++)_3[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case '4':
            for(j=0;j<WIDTH;j++)_4[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case '5':
            for(j=0;j<WIDTH;j++)_5[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case '6':
            for(j=0;j<WIDTH;j++)_6[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case '7':
            for(j=0;j<WIDTH;j++)_7[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case '8':
            for(j=0;j<WIDTH;j++)_8[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case '9':
            for(j=0;j<WIDTH;j++)_9[i][j]=='#'?printf(REPL):fputs(SPACE, stdout); fputs(SPACE, stdout);
            break;
        case ' ':
            printf("%s ", SPC[i]);
            break;
        default:
            printf("%s " , ERR[i]);
            break;
    }
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
