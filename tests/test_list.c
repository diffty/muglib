#include <stdio.h>
#include <stdlib.h>

#include "../src/utils/list.h"


int main() {
    List newIntList;

    lst_init_list(&newIntList, sizeof(int));
    int test1 = 5;
    int test2 = 69;

    lst_add_to_list(&newIntList, &test1);
    int* t1 = (int*) lst_get_element_list(&newIntList, 0);
    printf("%d\n", *t1);

    lst_add_to_list(&newIntList, &test2);
    int* t2 = (int*) lst_get_element_list(&newIntList, 1);
    printf("%d\n", *t2);

    return 0;
}