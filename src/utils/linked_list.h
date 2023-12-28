#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../core/types.h"


typedef struct LLNode {
	void* pData;
	struct LLNode *pNext;
} LLNode;

typedef struct LinkedList {
	LLNode* pHead;
	LLNode* pTail;
	unsigned int size;
} LinkedList;


void initList(LinkedList* pList);
void clearList(LinkedList* pList);
void appendList(LinkedList* pllSrcList, LinkedList* pllDstList);
void addNodeToList(LinkedList* pList, LLNode* nodeToAdd, bool bAddToHead);   // bAddToHead default to false
void addAfterNodeInList(LinkedList* pList, LLNode* pNodeToAdd, LLNode* pPrevNodeInList);
void addDataToList(LinkedList* pList, void* pDataToAdd);
LLNode* removeNodeFromList(LinkedList* pList, LLNode* pNode);
LLNode* searchForNodeInList(LinkedList* pList, void* pDataToSearch);
int countNodesInList(LinkedList* pList);
LLNode* getNodeInList(LinkedList* pList, uint nodeNum);
LLNode* popNodeFromList(LinkedList* pList);

#endif
