#ifndef UTILS_MEMORY
#define UTILS_MEMORY

#include <stdio.h>
#include <stdlib.h>


int calculate_size_with_padding(int size, int alignment) {
    int paddingSize = size % alignment;
    if (paddingSize > 0) {
        return size + (alignment - paddingSize);
    }
    else {
        return size;
    }
}

void print_memory_block_hex(void* pAddress, int memBlockSize) {
    int i;
    
    for (i = 0; i < memBlockSize; i++) { 
        printf("%02hhX ", ((unsigned char*) pAddress)[i]);
    }
    
    printf("\n");
}

#endif
