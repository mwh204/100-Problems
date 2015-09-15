#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.14159265

#define XMIN -5
#define XMAX 5
#define YMIN -5
#define YMAX 5

#define EMPTY '.'
#define FILL '#'

typedef struct verts{
    double x, y;
} vertice;

typedef struct shape{
    size_t numVerts;
    vertice* points;
} shape;

shape* shapeConstructor(const size_t n){
    shape* a = malloc(sizeof(shape));
    a->numVerts = n;
    a->points = malloc(sizeof(vertice)*n);
    return a;
}

shape* shapeDefiner(void){
    size_t n, i;
    double z;
    printf("Enter number of vertices(>=3): ");
    do{
        scanf("%d", &n);
    }while(n<3);
    shape* a = shapeConstructor(n);
    for(i=0; i<n; i++){
        printf("Enter x coord of vertice %d: ", i+1);
        scanf("%lf", &a->points[i].x);
        printf("Enter y coord of vertice %d: ", i+1);
        scanf("%lf", &a->points[i].y);
    }
    return a;
}

void shapeTranslator(shape* a, vertice* vect){
    //using vertice struct as a 2d vector (vect)
    int i;
    for(i=0; i<(a->numVerts); i++){
        a->points[i].x += vect->x;
        a->points[i].y += vect->y;
    }
}

void shapeRotator(shape* a, double rads){

}

void shapeDeconstructor(shape* a){
    free(a->points);
    free(a);
}

void printShape(shape* a){
    int x, y, i, ch = EMPTY;
    for(y = YMAX; y>=YMIN; y--){
        for(x = XMIN; x<=XMAX; x++){
            for(i=0; i<a->numVerts; i++){
                if(a->points[i].x == x && a->points[i].y == y){
                    putchar(ch = FILL);
                }
            }
            if(ch!=FILL){
                putchar(EMPTY);
            }else ch = EMPTY;
        }
        putchar('\n');
    }
}

int main(void){
    shape* a = shapeDefiner();
    printShape(a);
    vertice translation = {3, 2};
    shapeTranslator(a, &translation);
    printf("\n\n\n");
    printShape(a);
    shapeDeconstructor(a);
}
