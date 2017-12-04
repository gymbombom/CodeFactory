#include <stdio.h>
#include <stdlib.h>

typedef struct  list {
	struct node *head;
	struct node *tail;
	int size;
}linkedList;

typedef struct node {
	int data;
	struct node *next;
}node;

void initLinkedList(linkedList *ptrList)
{
	ptrList->head = NULL;
	ptrList->tail = NULL;
	ptrList->size = 0;
}

void createNode(linkedList *ptrList, int data)
{
	node *newNode = (node*)malloc(sizeof(node));
	newNode->data = data;
	newNode->next = NULL;

	if(ptrList->head == NULL && ptrList->tail == NULL)
	{
		ptrList->head = newNode;
		ptrList->tail = newNode;
		ptrList->size++;
	}
	else
	{
		ptrList->tail->next = newNode;
		ptrList->tail = newNode;
		ptrList->size++;
	}
}

void deleteFirstNode(linkedList *ptrList)
{
	node *tempNode =  NULL;

	if(ptrList->head !=NULL && ptrList->tail != NULL)
	{
		tempNode = ptrList->head->next;
		free(ptrList->head);
		ptrList->head = tempNode;
		ptrList->size--;
	}
	
}


void deleteAllNode(linkedList *ptrList)
{
	while(ptrList->head != NULL)
	{
		deleteFirstNode(ptrList);
	}

	if(ptrList->head == NULL)
	{
		printf("deleteAllNode \n");
	}
}

void printNode(linkedList *ptrList)
{
	node *tempNode = ptrList->head;
	printf("Linked List Size : %d \n",ptrList->size);
	while(tempNode != NULL )
	{
		printf("%d \n",tempNode->data);
		tempNode = tempNode->next;
	}
}

int main()
{
	linkedList list;
	initLinkedList(&list);

	createNode(&list,1);
	createNode(&list,2);
	createNode(&list,3);
	printNode(&list);

}
