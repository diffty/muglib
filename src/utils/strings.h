#ifndef UTILS_STRING
#define UTILS_STRING

#include <string.h>

#include "array.h"
#include "memory.h"


typedef struct String {
    char* data;
    int size;
    int alignedSize;
    int alignment;
} String;


String str_create_string(int size, int alignment) {
    String newStr;
    newStr.size = size + 1;
    newStr.alignment = alignment;
    newStr.alignedSize = calculate_size_with_padding(newStr.size, alignment);
    newStr.data = (char*) malloc(newStr.alignedSize);
    memset(newStr.data, '\0', newStr.alignedSize);
    return newStr;
}

void str_free_string(String* s) {
    free(s->data);
}

void str_resize_string(String* s, int newSize) {
    int newAlignedSize = calculate_size_with_padding(newSize, s->alignment);
    resize_array(&s->data, s->size, newAlignedSize);
    s->size = newSize;
    s->alignedSize = newAlignedSize;
}

void str_set_string(String* s, char* newStr) {
    int strSize = strlen(newStr);
    str_resize_string(s, strSize+1);
    memcpy(s->data, newStr, strSize+1);
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