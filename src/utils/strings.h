#ifndef UTILS_STRING
#define UTILS_STRING

#include <string.h>

#include "array.h"

typedef struct String {
    char* data;
    int size;
    int alignment;
} String;


String str_create_string(int size, int aligment) {
    String newStr;
    newStr.size = size + 1;
    newStr.data = (char*) malloc(newStr.size);
    memset(newStr.data, '\0', newStr.size);
    return newStr;
}

void str_free_string(String* s) {
    free(s->data);
}

void str_resize_string(String* s, int newSize) {
    resize_array(&s->data, s->size, newAlignedSize);
    s->size = newSize;
}

void str_copy(char** strDst, const char* strSrc) {
    int strDstSize = strlen(*strDst);
    int strSrcSize = strlen(strSrc);

    if (strSrcSize > strDstSize) {
        resize_array(strDst, strDstSize + 1, strSrcSize + 1);
    }
    else if (strSrcSize < strDstSize) {
        memset(*strDst, '\0', strDstSize + 1);
    }

    memcpy(*strDst, strSrc, strSrcSize + 1);
}

#endif