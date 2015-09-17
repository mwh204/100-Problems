#include<stdio.h>
#include<stdint.h>

uint64_t factorial(int n) {
    uint64_t i, result = 1;
    for (i = 2; i<=n; i++){
        result *= i;
    }
    return result;
}

uint64_t nCk(uint32_t n, uint32_t k){
    return n>=k ? factorial(n)/(factorial(k)*factorial(n-k)) : 0;
}

int main(void){
    printf("%d\n", nCk(4, 5));
}
