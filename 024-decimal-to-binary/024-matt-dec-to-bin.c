#include<stdio.h>
#include<stdint.h>

void printBin(void* n, const size_t size){
    int32_t i, j;
    uint8_t byte, *b = (uint8_t*) n;

    for(i=size-1; i>=0; i--){
        for(j=7; j>=0; j--){
            byte = b[i] & (1U<<j);
            printf("%d", (byte >>= j));
        }
    }
    putchar('\n');
}

int main(void){
    uint16_t a = 5;
    double b = 13.37;
    uint64_t c = 987654321;
    printBin(&a, sizeof(a));
    printBin(&b, sizeof(b));
    printBin(&c, sizeof(c));
}
