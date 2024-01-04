#ifndef UTILS_ARRAY_H
#define UTILS_ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void resizeArray(void* array, int oldSize, int newSize) {
    char** originalArray = (char**) array;
    char* newArray = (char*) malloc(newSize);
    
    memset(newArray, '\0', newSize);
    memcpy(newArray, *originalArray, oldSize);
    free(*originalArray);

    *originalArray = newArray;
}

#endif
