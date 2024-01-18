#ifndef UTILS_LIST_H
#define UTILS_LIST_H

#define List(type) lst_create(sizeof(type))


typedef struct List {
    void* data;
    int count;
    int dataSize;
    int elementSize;
} List;


void lst_init(List* pList, int elementSize);
List lst_create(int elementSize);
void lst_free(List* pList);
void* lst_get(List* pList, int n);
void lst_insert(List* pList, void* pDataToAdd, int n);
void lst_append(List* pList, void* pDataToAdd);
void* lst_remove(List* pList, int n);
void lst_reallocate(List* pList);

#endif
