#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define LENGTH 3

typedef struct vector{
    double i,j,k;
} vector;

int32_t dotProd(int32_t *a, int32_t *b, size_t length){
    /*Dot product is defined for two vectors (a_1, a_2, ... a_n) (b_1, b_2, ... b_n)
      as: a_1*b_1 + a_2*b_2 + ... + a_n*b_n*/
    int32_t i,sum = 0;
    for(i=0; i<length; i++){
        sum += (a[i]*b[i]);
    }
    return sum;
}

vector crossProd(vector *a, vector *b){
    /*cross product is only defined for R^3 vectors*/
    vector c = {a->j*b->k - a->k*b->j, a->k*b->i - a->i*b->k, a->i*b->j - a->j*b->i};
    return c;
}

void printVector(vector *a){
    printf("<%f, %f, %f>\n", a->i, a->j, a->k);
}

vector arrayToVector(int32_t *a){
    vector c = {a[0], a[1], a[2]};
    return c;
}

int32_t* vectorToArray(vector *a){
    int32_t* x = malloc(sizeof(int32_t)*LENGTH);    //memory leaks lmao
    x[0] = (int32_t)a->i;
    x[1] = (int32_t)a->j;
    x[2] = (int32_t)a->k;
    return x;
}

int32_t dotProdVec(vector *a, vector *b){
    int32_t *x = vectorToArray(a);
    int32_t *y = vectorToArray(b);
    int32_t result =  dotProd(x, y, LENGTH);
    free(x);
    free(y);
    return result;
}

int main(void){
    /*Dot prod test*/
    int32_t a[LENGTH] = {1, 3, -5};
    int32_t b[LENGTH] = {4, -2, -1};

    printf("%d\n", dotProd(a, b, LENGTH));

    /*cross prod test*/
    vector x = {2, 1, -1};
    vector y = {-3, 4, 1};
    vector c = crossProd(&x, &y);

    printVector(&c);
}
