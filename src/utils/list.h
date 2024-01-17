#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "array.h"


typedef struct List {
    void* data;
    int* offsetIndex;
    int count;
    int dataSize;
    int elementSize;
} List;


void lst_init_list(List* pList, int elementSize) {
    pList->data = malloc(0);
    pList->count = 0;
    pList->dataSize = 0;
    pList->elementSize = elementSize;
}

void lst_add_to_list(List* pList, void* pDataToAdd) {
    resize_array(
        &pList->data,
        pList->count * pList->elementSize,
        (pList->count + 1) * pList->elementSize);
    
    memcpy(pList->data + pList->count * pList->elementSize,
           pDataToAdd,
           pList->elementSize);
           
    pList->count++;
}

void* lst_get_element_list(List* pList, int n) {
    return (void*) pList->data + pList->elementSize * n;
}

#endif
