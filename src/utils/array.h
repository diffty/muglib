#ifndef UTILS_ARRAY_H
#define UTILS_ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "maths.h"


void resize_array(void* array, int oldSize, int newSize) {
    char** originalArray = (char**) array;
    char* newArray = (char*) malloc(newSize);
    
    memset(newArray, '\0', newSize);
    memcpy(newArray, *originalArray, minInt(newSize, oldSize));
    free(*originalArray);

    *originalArray = newArray;
}

#endif
