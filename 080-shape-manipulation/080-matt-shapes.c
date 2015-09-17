#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define __USE_BSD       //math.h M_PI constant
//#define PRINT_COORDS  //print the coordinates after drawing shape

#define MAX_VERTS 25    //max number of vertices in a shape

//defines for drawing the shapes
#define STEP    0.25
#define XMIN    -4
#define XMAX    4
#define YMIN    -4
#define YMAX    4

#define EMPTY   '.'
#define FILL    '#'

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
    printf("Enter number of vertices(>=3): ");
    do{
        scanf("%lu", &n);
    }while(n<3 && n>MAX_VERTS);
    shape* a = shapeConstructor(n);
    for(i=0; i<n; i++){
        printf("Enter x coord of vertice %lu: ", i+1);
        scanf("%lf", &(a->points[i].x));
        printf("Enter y coord of vertice %lu: ", i+1);
        scanf("%lf", &(a->points[i].y));
    }
    return a;
}

void shapeTranslator(shape* a, vertice vect){
    //using vertice struct as a 2d vector (vect)
    int i;
    for(i=0; i<(a->numVerts); i++){
        a->points[i].x += vect.x;
        a->points[i].y += vect.y;
    }
}

void shapeRotator(shape* a, double rads){
    double px, py;
    unsigned i;
    for(i=0; i<a->numVerts;  i++){
        px = a->points[i].x*cos(rads) - a->points[i].y*sin(rads);
        py = a->points[i].x*sin(rads) + a->points[i].y*cos(rads);
        a->points[i].x = px;
        a->points[i].y = py;
    }
}

void shapeRotatorDeg(shape* a, double degrees){
    double rads = degrees * (M_PI/180.0);
    shapeRotator(a, rads);
}

void shapeScaler(shape* a, double factor){
    unsigned i;
    for(i=0; i<a->numVerts;  i++){
        a->points[i].x *= factor;
        a->points[i].y *= factor;
    }
}

void shapeDeconstructor(shape* a){
    free(a->points);
    free(a);
}

int insidePolygon(shape* a, vertice point){
    int i, j, b = 0;
    for(i=0, j=a->numVerts-1; i<a->numVerts; j = i++){
        if( ( (a->points[i].y >= point.y ) != (a->points[j].y >= point.y) ) &&
            (point.x <= ((a->points[j].x - a->points[i].x) * (point.y - a->points[i].y) / (a->points[j].y - a->points[i].y) + a->points[i].x))
          ) b = !b;
    }
    return b;
}

void printShape(shape* a){
    int i, ch = EMPTY;
    double x,y;
    vertice p;
    for(y = YMAX; y>=YMIN; y-=STEP){
        for(x = XMIN; x<=XMAX; x+=STEP){
            for(i=0; i<a->numVerts; i++){
                p.x = (double)x; p.y = (double)y;
                if(insidePolygon(a, p)){
                    putchar(ch = FILL);
                    break;
                }
            }
            if(ch!=FILL){
                putchar(EMPTY);
            }else ch = EMPTY;
        }
        putchar('\n');
    }
    putchar('\n');
#ifdef PRINT_COORDS
    for(x=0; x<a->numVerts; x++){
        printf("%d: (%f, %f)\n", x+1, a->points[x].x, a->points[x].y);
    }
#endif // PRINT_COORDS
}

int main(void){

    //creating the shape
    shape* a = shapeDefiner();
    printShape(a);

    //translation
    vertice translation = {1, -1};
    shapeTranslator(a, translation);
    printShape(a);

    //rotation
    shapeRotator(a, M_PI/2.0);
    printShape(a);

    //scaling
    shapeScaler(a, 1.5);
    printShape(a);

    shapeDeconstructor(a);
}
