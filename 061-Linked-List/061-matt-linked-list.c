#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

struct singleLinkedList_t{
    struct singleLinkedList_t* next;
    uint32_t data;
};

void singleInsert(struct singleLinkedList_t *initial, struct singleLinkedList_t *newLink){
    newLink->next = initial->next;
    initial->next = newLink;
}

struct singleLinkedList_t* singleRemove(struct singleLinkedList_t *curr, uint32_t data){
     struct singleLinkedList_t* next;
     if(!curr){
        fprintf(stderr, "Element not found\n");
        return NULL;
     }else if(curr->data == data){
        next = curr->next;
        free(curr);
        return next;
     }else{
        curr->next = singleRemove(curr->next, data);
        return curr;
     }
}


struct doubleLinkedList_t{
    struct doubleLinkedList* next;
    struct doubleLinkedList* prev;
    uint32_t data;
};

int main(void){
    /*Singly Linked List */
    struct singleLinkedList_t *x, *y, *z, *iter;

    x = malloc(sizeof(struct singleLinkedList_t));
    y = malloc(sizeof(struct singleLinkedList_t));
    z = malloc(sizeof(struct singleLinkedList_t));
    iter = malloc(sizeof(struct singleLinkedList_t));

    singleInsert(x, y);
    singleInsert(y, z);

    x->data = 123;
    y->data = 1337;
    z->data = 999;

    for(iter = x;iter != NULL; iter = iter->next){
        printf("%d\n", iter->data);
    }

    x = singleRemove(x, 1337);

    for(iter = x;iter != NULL; iter = iter->next){
        printf("%d\n", iter->data);
    }

    free(x);
    free(y);
    free(z);
    free(iter);

    return EXIT_SUCCESS;
}
