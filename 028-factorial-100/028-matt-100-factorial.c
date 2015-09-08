#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>


uint8_t* copy(uint8_t* a, size_t size){
    int i;
    uint8_t* b = malloc(sizeof(uint8_t)*size);
    for(i=size-1; i>=0; i--){
        b[i] = a[i];
    }
    return b;
}

size_t numDigits(uint32_t n){
    return (size_t)(log10(n)+1);
}

uint8_t* setArrVal(uint64_t n, size_t size){
    int i, j=numDigits(n), k=j;
    uint8_t* a = malloc(sizeof(uint8_t)*size);
    for(i=0; i<k; i++){
        a[i] = (uint8_t)(n % (int)pow(10, j--) /(int)pow(10, j));
    }
    return a;
}

void printNum(uint8_t* a, size_t size){
    int i;
    for(i=size-1; i>=0; i--){
        printf("%d", a[i]);
    }
    printf("\n");
}

void add(uint8_t* a, uint8_t* b, size_t size){
    /*stores the result in "a" i.e. add(dest, src)*/
    int temp,i;
    for(i=0; i<size; i++){
        temp = a[i] + b[i];
        if(temp>=10){
            a[i] = temp % 10;
            a[i+1] += temp / 10;
        }else{
            a[i] = temp;
        }
    }
}

void multiply(uint8_t* a, uint64_t n, size_t size){
    /*stores the result in a i.e. multiply(dest, src)*/
    int i;
    uint8_t* x = copy(a, size);
    for(i=1; i<n; i++){
        add(a, x, size);
    }
    free(x);
}

size_t numDigitsFact(uint16_t n){
    int i;
    double sum=0;
    for(i=1; i<=n; i++){
        sum += log10(i);
    }
    return (int)ceil(sum);
}

uint8_t* factorial(uint8_t n, size_t size){
    uint64_t i;
    size_t numDigits = numDigitsFact(n);
    uint8_t *result = setArrVal(1, size);
    for(i=2; i<=n; i++){
        multiply(result, i, size);
    }
    return result;
}

int main(void){
    const int fact = 100;
    const size_t numDigits = numDigitsFact(fact);
    uint8_t *result = factorial(fact, numDigits);
    printNum(result, numDigits);
    free(result);
    return EXIT_SUCCESS;
}
