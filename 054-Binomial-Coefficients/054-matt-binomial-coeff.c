#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

uint64_t factorial(uint8_t n) {
    uint64_t i, result = 2;
    for (i = 3; i<=n; i++){
        result *= i;
    }
    return result;
}

uint64_t nCk(uint32_t n, uint32_t k){
    return n>=k ? factorial(n)/(factorial(k)*factorial(n-k)) : 0;
}

uint64_t nCki(uint32_t n, uint32_t k){
    uint64_t i, result = 1;
    for(i=1; i<=k; i++){
        result *= (n-k+i);
        result /= i;
    }
    return result;
}

uint64_t nCkrecurse(uint64_t** C, uint32_t n, uint32_t k){
    if(k <= 0 || k >= n) return 1;
    if(C[n-1][k-1] == 0)
        C[n-1][k-1] = nCkrecurse(C, n-1, k-1) + nCkrecurse(C, n-1, k);
    return C[n-1][k-1];
}

uint64_t nCkr(uint32_t n, uint32_t k){
    uint64_t** C = malloc(n * sizeof(uint64_t*)), i;
    for(i=0; i<n; i++){
        C[i] = malloc(k * sizeof(uint64_t));
    }
    i = nCkrecurse(C, n, k);
    free(C);
    return i;
}

int main(void){
    printf("%lu\n", nCk(63, 13));
    printf("%lu\n", nCki(75, 13));
    printf("%lu\n", nCkr(75, 13));
}
