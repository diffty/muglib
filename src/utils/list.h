#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "array.h"

#define List(type) lst_create(sizeof(type))


typedef struct List {
    void* data;
    int count;
    int dataSize;
    int elementSize;
} List;


void lst_init(List* pList, int elementSize) {
    pList->data = malloc(0);
    pList->count = 0;
    pList->dataSize = 0;
    pList->elementSize = elementSize;
}

List lst_create(int elementSize) {
    List newList;
    lst_init(&newList, elementSize);
    return newList;
}

void* lst_get(List* pList, int n) {
    return (void*) pList->data + pList->elementSize * n;
}

void lst_insert(List* pList, void* pDataToAdd, int n) {
    int oldSize = pList->count * pList->elementSize;
    int newSize = (pList->count + 1) * pList->elementSize;

    if (newSize > pList->dataSize) {
        resize_array(&pList->data, oldSize, newSize);
        pList->dataSize = newSize;
    }

    if (n < pList->count) {
        memmove(pList->data + pList->elementSize * (n + 1),
                pList->data + pList->elementSize * n,
                pList->elementSize * (pList->count - n));
    }

    memmove(pList->data + n * pList->elementSize,
           pDataToAdd,
           pList->elementSize);
           
    pList->count++;
}

void lst_append(List* pList, void* pDataToAdd) {
    lst_insert(pList, pDataToAdd, pList->count);
}

void* lst_remove(List* pList, int n) {
    void* pRemovedElement = *((void**) lst_get(pList, n));

    if (n < pList->count - 1) {
        memmove(pList->data + pList->elementSize * n,
                pList->data + pList->elementSize * (n+1),
                pList->elementSize * (pList->count - (n + 1)));
    }
    pList->count--;
    memset(pList->data + pList->elementSize * pList->count, 0, pList->elementSize);

    return pRemovedElement;
}

void lst_reallocate(List* pList) {
    int oldSize = pList->dataSize;
    int newSize = pList->count * pList->elementSize;
    resize_array(&pList->data, oldSize, newSize);
    pList->dataSize = newSize;
}

#endif
