#include "array.h"

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
