#include "linked_list.h"


void initList(LinkedList* pList) {
	pList->pHead = NULL;
	pList->pTail = NULL;
	pList->size = 0;
}

void clearList(LinkedList* pList) {
	LLNode* pCurrNode = pList->pHead;

	if (pCurrNode) {
		LLNode* pNextNode = pCurrNode->pNext;

		while (pCurrNode != NULL) {
			pNextNode = pCurrNode->pNext;
			free(pCurrNode);
			pCurrNode = pNextNode;
		}
	}

	pList->pHead = NULL;
	pList->pTail = NULL;
}

void appendList(LinkedList* pllSrcList, LinkedList* pllDstList) {
	LLNode* pCurrNode = pllSrcList->pHead;
	
	while (pCurrNode != NULL) {
		LLNode* pClonedNode = malloc(sizeof(LLNode));    // TODO: put this 
		memcpy(pClonedNode, pCurrNode, sizeof(LLNode));  // in a func
 
		pClonedNode->pNext = NULL;
		addNodeToList(pllDstList, pClonedNode, false);

		pCurrNode = pCurrNode->pNext;
	}
}

void addNodeToList(LinkedList* pList, LLNode* pNodeToAdd, bool bAddToHead) {
	if (pList->pHead == NULL) {
		pList->pHead = pNodeToAdd;
		pList->pTail = pNodeToAdd;
		pNodeToAdd->pNext = NULL;
	}
	else {
		if (bAddToHead) {
			pNodeToAdd->pNext = pList->pHead;
			pList->pHead = pNodeToAdd;
		}
		else {
			if (pList->pTail != NULL)
				pList->pTail->pNext = pNodeToAdd;

			pList->pTail = pNodeToAdd;
			pNodeToAdd->pNext = NULL;
		}
	}

	pList->size++;
}

void addAfterNodeInList(LinkedList* pList, LLNode* pNodeToAdd, LLNode* pPrevNodeInList) {
	if (pPrevNodeInList == pList->pTail) {
		pList->pTail = pNodeToAdd;
	}

	pNodeToAdd->pNext = pPrevNodeInList->pNext;
	pPrevNodeInList->pNext = pNodeToAdd;
    
    pList->size++;
}

void addDataToList(LinkedList* pList, void* pDataToAdd) {
	LLNode* pNewNode = malloc(sizeof(LLNode));
	pNewNode->pData = pDataToAdd;
	pNewNode->pNext = NULL;
	addNodeToList(pList, pNewNode, false);
}

LLNode* removeNodeFromList(LinkedList* pList, LLNode* pNode) {
	if (pList->pHead == NULL) {
		return NULL;
	}

    if (pNode == pList->pHead) {
        pList->pHead = pNode->pNext;
        pList->size--;
		if (pNode == pList->pTail) {
			pList->pTail = NULL;
		}
        return pNode;
    }

	LLNode* pCurrNode = pList->pHead;

	while (pCurrNode != NULL) {
		if (pCurrNode->pNext == pNode) {
			pCurrNode->pNext = pNode->pNext;

			if (pList->pTail == pNode) pList->pTail = pCurrNode;

			pList->size--;
			return pNode;
		}
		pCurrNode = pCurrNode->pNext;
	}

	return NULL;
}

LLNode* popNodeFromList(LinkedList* pList) {
	return pList->pTail;
}

LLNode* searchForNodeInList(LinkedList* pList, void* pDataToSearch) {
	LLNode* pCurrNode = pList->pHead;

	while (pCurrNode != NULL) {
		if (pCurrNode->pData == pDataToSearch) {
			return pCurrNode;
		}
		pCurrNode = pCurrNode->pNext;
	}

	return NULL;
}

int countNodesInList(LinkedList* pList) {
	if (pList->pHead == NULL) {
		return 0;
	}

	int nbNodes = 0;
	LLNode* pCurrNode = pList->pHead;

	while(pCurrNode != NULL) {
		nbNodes++;
		pCurrNode = pCurrNode->pNext;
	}

	return nbNodes;
}

LLNode* getNodeInList(LinkedList* pList, uint nodeNum) {
    if (nodeNum >= pList->size) {
        printf("<!> Out of list node number : %d\n", nodeNum);
        return NULL;
    }
    
    uint i = 0;
    LLNode* currNode = pList->pHead;
    
    while (i < nodeNum) {
        currNode = currNode->pNext;
        i++;
    }
    
    return currNode;
}
