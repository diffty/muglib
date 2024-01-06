#ifndef UTILS_MEMORY
#define UTILS_MEMORY

int calculate_size_with_padding(int size, int alignment) {
    int paddingSize = size % alignment;
    if (paddingSize > 0) {
        return size + (alignment - paddingSize);
    }
    else {
        return size;
    }
}

#endif