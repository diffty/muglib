#ifndef UTILS_STRINGS
#define UTILS_STRINGS

#include <string.h>

#define String(s) str_create(s, 4)


typedef struct String {
    char* data;
    int size;
    int alignedSize;
    int alignment;
} String;


String str_create(char* s, int alignment);
void str_free(String* s);
void str_resize(String* s, int newSize);
void str_set(String* s, char* newStr);
void str_concat(String* s, char* strToConcat);
void str_copy(char** strDst, const char* strSrc);

#endif