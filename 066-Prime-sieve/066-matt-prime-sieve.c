#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define LIMIT 100

uint8_t* makePrimeArray(){
    unsigned long long int i,j;

	uint8_t* primes = malloc(sizeof(int)*LIMIT);
    primes[2]=1;
	for (i=3; i<LIMIT; i+=2) {
		primes[i] = 1;
	}

	for (i=2; i<LIMIT; i++) {
		if (primes[i]) {
			for (j=i; i*j<LIMIT; j++) {
				primes[i*j] = 0;
			}
		}
	}
	return primes;
}


int main() {
    int i, j=1;
    uint8_t* primes = makePrimeArray();
	for (i=2; i<LIMIT; i++) {
        if(primes[i])
            printf("%dth prime:\t%d\n",j++,i);

	}

	free(primes);
    return EXIT_SUCCESS;
}
