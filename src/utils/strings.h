#ifndef UTILS_STRINGS
#define UTILS_STRINGS

#include <string.h>


typedef struct String {
    char* data;
    int size;
    int alignedSize;
    int alignment;
} String;


String str_create_string(int size, int alignment);
void str_free_string(String* s);
void str_resize_string(String* s, int newSize);
void str_set_string(String* s, char* newStr);
void str_copy(char** strDst, const char* strSrc);

#endif