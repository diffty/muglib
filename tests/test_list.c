#include <stdio.h>
#include <stdlib.h>

#include "../src/utils/list.h"
#include "../src/utils/memory.h"


int main() {
    List newIntList = List(int);
    
    //lst_init_list(&newIntList, sizeof(int));
    int test1 = 5;
    int test2 = 69;
    int test3 = 254;
    int test4 = 5;
    int test5 = 420;

    lst_append(&newIntList, &test1);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_append(&newIntList, &test2);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_append(&newIntList, &test3);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_remove(&newIntList, 1);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_remove(&newIntList, 0);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_append(&newIntList, &test2);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_append(&newIntList, &test3);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_append(&newIntList, &test2);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_append(&newIntList, &test1);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_append(&newIntList, &test4);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_remove(&newIntList, newIntList.count-1);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_remove(&newIntList, newIntList.count-1);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_remove(&newIntList, newIntList.count-1);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_insert(&newIntList, &test5, 1);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_insert(&newIntList, &test1, 0);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_insert(&newIntList, &test2, newIntList.count);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    lst_reallocate(&newIntList);
    print_memory_block_hex(newIntList.data, newIntList.dataSize);

    int* t1 = (int*) lst_get(&newIntList, 0);
    int* t2 = (int*) lst_get(&newIntList, 1);
    printf("%d\n", *t1);
    printf("%d\n", *t2);

    List newCharPtrList = List(char*);

    char testStr1[] = "cc sava";
    char testStr2[] = "Bonjour non";

    char** testPtrStr1 = &testStr1;
    char** testPtrStr2 = &testStr2;

    lst_append(&newCharPtrList, &testPtrStr1);
    print_memory_block_hex(newCharPtrList.data, newCharPtrList.dataSize);

    lst_append(&newCharPtrList, &testPtrStr2);
    print_memory_block_hex(newCharPtrList.data, newCharPtrList.dataSize);

    printf("%s\n", *((char**) lst_get(&newCharPtrList, 0)));
    printf("%s\n", *((char**) lst_get(&newCharPtrList, 1)));

    return 0;
}
