#include<stdio.h>
#include<string.h>
#include "name.h"

void printLetter(char a, int i){
    switch(a){
        case 'a':
        case 'A':
            printf("%s ", A[i]);
            break;
        case 'b':
        case 'B':
            printf("%s ", B[i]);
            break;
        case 'c':
        case 'C':
            printf("%s ", C[i]);
            break;
        case 'd':
        case 'D':
            printf("%s ", D[i]);
            break;
        case 'e':
        case 'E':
            printf("%s ", E[i]);
            break;
        case 'f':
        case 'F':
            printf("%s ", F[i]);
            break;
        case 'g':
        case 'G':
            printf("%s ", G[i]);
            break;
        case 'h':
        case 'H':
            printf("%s ", H[i]);
            break;
        case 'i':
        case 'I':
            printf("%s ", I[i]);
            break;
        case 'j':
        case 'J':
            printf("%s ", J[i]);
            break;
        case 'k':
        case 'K':
            printf("%s ", K[i]);
            break;
        case 'l':
        case 'L':
            printf("%s ", L[i]);
            break;
        case 'm':
        case 'M':
            printf("%s ", M[i]);
            break;
        case 'n':
        case 'N':
            printf("%s ", N[i]);
            break;
        case 'o':
        case 'O':
            printf("%s ", O[i]);
            break;
        case 'p':
        case 'P':
            printf("%s ", P[i]);
            break;
        case 'q':
        case 'Q':
            printf("%s ", Q[i]);
            break;
        case 'r':
        case 'R':
            printf("%s ", R[i]);
            break;
        case 's':
        case 'S':
            printf("%s ", S[i]);
            break;
        case 't':
        case 'T':
            printf("%s ", T[i]);
            break;
        case 'u':
        case 'U':
            printf("%s ", U[i]);
            break;
        case 'v':
        case 'V':
            printf("%s ", V[i]);
            break;
        case 'w':
        case 'W':
            printf("%s ", W[i]);
            break;
        case 'x':
        case 'X':
            printf("%s ", X[i]);
            break;
        case 'y':
        case 'Y':
            printf("%s ", Y[i]);
            break;
        case 'z':
        case 'Z':
            printf("%s ", Z[i]);
            break;
        case '0':
            printf("%s ", _0[i]);
            break;
        case '1':
            printf("%s ", _1[i]);
            break;
        case '2':
            printf("%s ", _2[i]);
            break;
        case '3':
            printf("%s ", _3[i]);
            break;
        case '4':
            printf("%s ", _4[i]);
            break;
        case '5':
            printf("%s ", _5[i]);
            break;
        case '6':
            printf("%s ", _6[i]);
            break;
        case '7':
            printf("%s ", _7[i]);
            break;
        case '8':
            printf("%s ", _8[i]);
            break;
        case '9':
            printf("%s ", _9[i]);
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
