#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int main(void){
	uint8_t i;
	for(i=1; i<=100; i++){
        if(i%15==0){
            puts("FizzBuzz");
        }else if(i%5==0){
            puts("Buzz");
        }else if(i%3==0){
            puts("Fizz");
        }else{
            printf("%d\n", i);
        }
	}
	return EXIT_SUCCESS;
}

