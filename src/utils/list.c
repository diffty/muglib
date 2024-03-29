#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"


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

void lst_free(List* pList) {
    free(pList->data);
}

void* lst_get(List* pList, int n) {
    return (void*) (((char*) pList->data) + pList->elementSize * n);
}

void lst_insert(List* pList, void* pDataToAdd, int n) {
    int oldSize = pList->count * pList->elementSize;
    int newSize = (pList->count + 1) * pList->elementSize;

    if (newSize > pList->dataSize) {
        resize_array(&pList->data, oldSize, newSize);
        pList->dataSize = newSize;
    }

    if (n < pList->count) {
        memmove(((char*) pList->data) + pList->elementSize * (n + 1),
                ((char*) pList->data) + pList->elementSize * n,
                pList->elementSize * (pList->count - n));
    }

    memmove(((char*) pList->data) + n * pList->elementSize,
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
        memmove(((char*) pList->data) + pList->elementSize * n,
                ((char*) pList->data) + pList->elementSize * (n+1),
                pList->elementSize * (pList->count - (n + 1)));
    }
    pList->count--;
    memset(((char*) pList->data) + pList->elementSize * pList->count, 0, pList->elementSize);

    return pRemovedElement;
}

void lst_reallocate(List* pList) {
    int oldSize = pList->dataSize;
    int newSize = pList->count * pList->elementSize;
    resize_array(&pList->data, oldSize, newSize);
    pList->dataSize = newSize;
}
