#include<stdio.h>
#include<malloc.h>
#include<math.h>

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

shape* shapeDefiner(){
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

void shapeDeconstructor(shape* a){
    free(a->points);
    free(a);
}

double areaPolygon(shape* a){
    double area = 0.0;
    int i, j;
    for(i=0; i<a->numVerts; i++){
        j = (i+1) % a->numVerts;
        area += a->points[i].x * a->points[j].y;
        area -= a->points[i].y * a->points[j].x;
    }
    return fabs(area/2);
}

int main(void){
    shape *a = shapeDefiner();
    printf("%f\n", areaPolygon(a));
    shapeDeconstructor(a);
}
