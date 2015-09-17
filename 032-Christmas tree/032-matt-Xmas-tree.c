#include<stdio.h>
#include<stdlib.h>

#define TREE '*'
#define TRUNK '#'

void printTree(int height){
    int i,j;
    if(height<0) height *= -1;

    for(i=0; i<height; i++){
        for(j=i+1; j<height; j++){
           putchar(' ');
        }for(j=0; j<=2*i; j++){
           putchar(TREE);
        }if(i<height-1) putchar('\n');
    }
    putchar('\n');
    for(i=0; i<height-1; i++){
        putchar(' ');
    }
    putchar(TRUNK);
    putchar('\n');
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Error: no size specified or too many arguments!");
        return EXIT_FAILURE;
    }
    int height = (int)atoi(argv[1]);
    printTree(height);
    return EXIT_SUCCESS;
}
