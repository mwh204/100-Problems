#include<stdio.h>
#include<stdint.h>

#define LIMIT 300

uint64_t collatz(uint64_t n){
    return (n % 2) ? 3*n+1 :  n/2;
}

uint64_t seqLength(uint64_t n){
    uint64_t i;
    for(i=0; n != 4 && n != 2 && n != 1 ; i++){
        n = collatz(n);
    }
    return i;
}

int main(void){
    uint64_t i;
    for(i=3; i<LIMIT; i++){
        printf("The sequence length of \t%d is \t%d\n", i, seqLength(i));
    }
}
