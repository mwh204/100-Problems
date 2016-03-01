#include<stdio.h>
#include<stdint.h>
#include<limits.h>

void printBin(void* n, const size_t size);

void printBin(void* n, const size_t size){
    size_t i, j;
    uint8_t byte, *b = (uint8_t* ) n;

    for(i=size; i; i--){
        for(j=CHAR_BIT; j; j--){
            byte = b[i-1] & (1U << (j-1));
            printf("%d", byte >>= (j-1));
        }
    }
    putchar('\n');
}

int main(void){
    uint32_t a = 5;
    double b = 13.37;
    uint64_t c = 987654321;
    uint16_t d = 0xF65;

    printBin(&a, sizeof(a));
    printBin(&b, sizeof(b));
    printBin(&c, sizeof(c));
    printBin(&d, sizeof(d));
}
