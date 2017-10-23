#include <stdio.h>
#include <stdlib.h>

typedef struct __list {
	struct node *head;
	struct node *tail;
} linkdList;

typedef struct __node {
	int data;
	struct node *next;
} node;


void createNode(linkedList *ptrList, int data)
{
	node *newNode = (node*)malloc(sizeof(node));
	newNode->data = data;
	newNode->next = NULL;
	if(ptrList->head == NULL && ptrList->tail == NULL)
	{
		ptrList->head = newNode;
		ptrList->tail = newNode;
	}
	else
	{
		ptrList->tail->next = newNode;
		ptrList->tail = newNode;
	}
}

void deleteFirstNode(linkedList *ptrList)
{
	
}
