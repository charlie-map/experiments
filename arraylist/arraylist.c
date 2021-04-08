#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DEFAULT_SIZE 8

typedef struct arraylist {
    int* array;
    int size;
    int internal_size;
} arraylist_t;

arraylist_t* arraylist_factory() {
    arraylist_t* arraylist = (arraylist_t*) malloc(sizeof(arraylist_t));
    arraylist->internal_size = DEFAULT_SIZE;
    arraylist->size = 0;
    arraylist->array = (int*) malloc(sizeof(int) * DEFAULT_SIZE);
}

int arraylist_destroy (arraylist_t* arraylist) {
    free(arraylist->array);
    free(arraylist);
    return 1;
}

arraylist_t* arraylist_expand(arraylist_t* arraylist) {
    arraylist_t* new_arraylist = (arraylist_t*) malloc(sizeof(arraylist_t));
    new_arraylist->array = (int*) malloc(sizeof(int) * 2 * arraylist->internal_size);
    new_arraylist->internal_size = arraylist->internal_size * 2;
    new_arraylist->size = arraylist->size;
    memcpy(new_arraylist->array, arraylist->array, sizeof(int) * arraylist->size);
    if (arraylist_destroy(arraylist)) {
        return new_arraylist;
    } else {
        arraylist_destroy(new_arraylist);
        return NULL;
    }
}

arraylist_t* arraylist_insert (arraylist_t* arraylist, int value) {
    if (arraylist->size == arraylist->internal_size)
        arraylist = arraylist_expand(arraylist);
    
    arraylist->array[arraylist->size++] = value;
    return arraylist;
}

int arraylist_get (arraylist_t* arraylist, int index) {
    if (index < arraylist->size)
        return arraylist->array[index];
    else
        return -1;
}

int arraylist_set (arraylist_t* arraylist, int index, int value) {
    if (index < arraylist->size) {
        arraylist->array[index] = value;
        return 1;
    } else {
        return -1;
    }
}

int arraylist_delete (arraylist_t* arraylist, int posn) {
    // TODO
    return 1;
}

int main()
{
    srand(time(NULL));
    printf("Testing arraylist\n");
    
    arraylist_t* myarray = arraylist_factory();
    int i;
    for (i = 0; i < 666; i++) {
        myarray = arraylist_insert(myarray, rand() % 1000);
    }
    
    printf("My array size: %d Internal size: %d\n", myarray->size, myarray->internal_size);

    return 0;
}

