#include<stdio.h>
#include<stdint.h>

uint64_t nthTrinum(uint32_t n){
    return (uint64_t)(n*(n+1))/2L;
}

int main(void){
    uint32_t i;
    for(i=1; i<30; i++){
        printf("%dth trinum: %lu\n", i, nthTrinum(i));
    }
}
