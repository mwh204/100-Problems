#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SIZE 10

size_t positionOfGreatestNumber(int* arr, size_t size){
    int i, j=0, max = 0;
    for(i=0; i<size; i++){
        if(arr[i]>max) {
            j=i;
            max = arr[i];
        }
    }
    return j;
}


int main(void){
    int *i, j;
    i=malloc(sizeof(int)*SIZE);
    for(j=0;j<10;j++){
        i[j] = rand() % 6;
        printf("%d, ", i[j]);
    }
    printf("\nthe largest number is at position %d\n", positionOfGreatestNumber(i, SIZE));
    free(i);
}


