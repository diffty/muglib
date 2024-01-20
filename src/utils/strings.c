#include "strings.h"

#include <string.h>
#include <stdarg.h>

#include "array.h"
#include "memory.h"


String str_create(char* s, int alignment) {
    String newStr;
    newStr.size = strlen(s) + 1;
    newStr.alignment = alignment;
    newStr.alignedSize = calculate_size_with_padding(newStr.size, alignment);
    newStr.data = (char*) malloc(newStr.alignedSize);
    memset(newStr.data, '\0', newStr.alignedSize);
    memmove(newStr.data, s, newStr.size);
    return newStr;
}

void str_free(String* s) {
    free(s->data);
}

void str_resize(String* s, int newSize) {
    int newAlignedSize = calculate_size_with_padding(newSize, s->alignment);
    resize_array(&s->data, s->size, newAlignedSize);
    s->size = newSize;
    s->alignedSize = newAlignedSize;
}

void str_set(String* s, char* newStr) {
    int strSize = strlen(newStr);
    str_resize(s, strSize+1);
    memcpy(s->data, newStr, strSize+1);
}

void str_concat(String* s, char* strToConcat) {
    int strOriginalSize = s->size;
    int strToConcatSize = strlen(strToConcat);
    str_resize(s, s->size+strToConcatSize);
    memcpy(s->data + strOriginalSize-1, strToConcat, strToConcatSize);
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
