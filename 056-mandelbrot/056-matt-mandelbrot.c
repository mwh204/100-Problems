#include<stdio.h>
#include<math.h>
#include<complex.h>

#define FILL '#'
#define EMPTY '.'
#define ITERATIONS 100

void mandelbrot(void){
    unsigned int i;
    long double x, y;
    double complex z;
    for(y=-1.2; y<1.2; y += 0.05){
        for(x=-2.05; x<0.55; x += 0.03){
            z = 0;
            for(i=0; i<=ITERATIONS; i++){
                z = (z * z) + (x + y*I);
            }
            cabs(z)<2.0? putchar(FILL) : putchar(EMPTY);
        }
        putchar('\n');
    }
}

int main(void){
    mandelbrot();
}
