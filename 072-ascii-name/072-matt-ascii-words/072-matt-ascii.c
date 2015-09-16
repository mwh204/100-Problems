#include<stdio.h>
#include<string.h>

#include "name.h"

#define ORIG '#'    //do not change
#define REPL "_/"
#define SPACE "  "  //must match number of chars in REPL

void selChar(const char** a, int i){
    int j;
    for(j=0;j<WIDTH;j++){
        a[i][j]==ORIG ? printf(REPL) : fputs(SPACE, stdout);
    }
    fputs(SPACE, stdout);
}

void printLetter(char a, int i){
    int j;
    switch(a){
        case 'a':
        case 'A': selChar(A, i); break;
        case 'b':
        case 'B': selChar(B, i); break;
        case 'c':
        case 'C': selChar(C, i); break;
        case 'd':
        case 'D': selChar(D, i); break;
        case 'e':
        case 'E': selChar(E, i); break;
        case 'f':
        case 'F': selChar(F, i); break;
        case 'g':
        case 'G': selChar(G, i); break;
        case 'h':
        case 'H': selChar(H, i); break;
        case 'i':
        case 'I': selChar(I, i); break;
        case 'j':
        case 'J': selChar(J, i); break;
        case 'k':
        case 'K': selChar(K, i); break;
        case 'l':
        case 'L': selChar(L, i); break;
        case 'm':
        case 'M': selChar(M, i); break;
        case 'n':
        case 'N': selChar(N, i); break;
        case 'o':
        case 'O': selChar(O, i); break;
        case 'p':
        case 'P': selChar(P, i); break;
        case 'q':
        case 'Q': selChar(Q, i); break;
        case 'r':
        case 'R': selChar(R, i); break;
        case 's':
        case 'S': selChar(S, i); break;
        case 't':
        case 'T': selChar(T, i); break;
        case 'u':
        case 'U': selChar(U, i); break;
        case 'v':
        case 'V': selChar(V, i); break;
        case 'w':
        case 'W': selChar(W, i); break;
        case 'x':
        case 'X': selChar(X, i); break;
        case 'y':
        case 'Y': selChar(Y, i); break;
        case 'z':
        case 'Z': selChar(Z, i); break;
        case '0': selChar(_0, i); break;
        case '1': selChar(_1, i); break;
        case '2': selChar(_2, i); break;
        case '3': selChar(_3, i); break;
        case '4': selChar(_4, i); break;
        case '5': selChar(_5, i); break;
        case '6': selChar(_6, i); break;
        case '7': selChar(_7, i); break;
        case '8': selChar(_8, i); break;
        case '9': selChar(_9, i); break;
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
