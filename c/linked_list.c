#include <stdio.h>
#include <stdlib.h>

#define STRING_LEN 10+1

//data 구조체
typedef struct data 
{
	int num;
	char chr;
	char string[STRING_LEN];
	char *ptrString;
}data_t;


typedef struct  list{
	struct node *head;
	struct node *tail;
	int size;
}linkedList_t;


typedef struct node {
	data_t data;
	struct node *prev;
	struct node *next;
}node_t;


/* function proto Type */
void initLinkedList(linkedList_t *ptrList);
void createNode(linkedList_t *ptrList, data_t data);
void deleteFirstNode(linkedList_t *ptrList);
void printNode(linkedList_t *ptrList);
void insertData(node_t *newNode, data_t data);

//linked list를 초기화 한다.
void initLinkedList(linkedList_t *ptrList)
{
	ptrList->head = NULL;
	ptrList->tail = NULL;
	ptrList->size = 0;
}

void createNode(linkedList_t *ptrList, data_t data)
{
	/* node 구조체 초기화 */
	node_t *newNode = (node_t*)malloc(sizeof(node_t));

	//memcpy( &(newNode.data) );

	insertData(newNode,data);
	
	newNode->next = NULL;

	/*최초 삽입되는 리스트일 경우 */
	if(ptrList->head == NULL && ptrList->tail == NULL && ptrList->size == 0)
	{
		newNode->prev = NULL;

		ptrList->head = newNode;
		ptrList->tail = newNode;
		ptrList->size++;
	}
	else /*최초 삽입되는 리스트가 아닐경우 */
	{
		newNode->prev = ptrList->tail;

		ptrList->tail->next = newNode;
		ptrList->tail = newNode;
		ptrList->size++;
	}
}


void deleteFirstNode(linkedList_t *ptrList)
{
	node_t *tempNode =  NULL;


	if(ptrList->head !=NULL && ptrList->tail != NULL)
	{
		tempNode = ptrList->head->next;
		free(ptrList->head);

		/* tempNode가 Head 가 될 것이기 때문이 NULL 을 입력해준다 */
		if(tempNode != NULL)
		{
			tempNode->prev = NULL;
		}

		ptrList->head = tempNode;

		if(ptrList->head == NULL)
		{
			ptrList->tail = NULL;
		}

		ptrList->size--;
	}
	else
	{
		printf("linked list no data \n");
	}
	
}


void deleteAllNode(linkedList_t *ptrList)
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


int deleteNode(linkedList_t *ptrList,node_t* node)
{

	if(node == NULL)
	{
		printf("delteNode Falied!! node is NULL!");
		return -1;	
	}

	/*head Node 일경우 */
	if(node->prev == NULL)
	{
		deleteFirstNode(ptrList);
		return 0;
	}


	/* 중간 Node일 경우 */
	if(node->prev != NULL && node->next != NULL)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node);
		ptrList->size--;
		return 0;
	}

	/* 마지막 node 일 경우 */
	if(node->next == NULL)
	{
		node->prev->next = NULL;
		ptrList->tail = node->prev;
		free(node);
		ptrList->size--;
		return 0;
	}
}


void printNode(linkedList_t *ptrList)
{
	node_t *tempNode = ptrList->head;
	printf("Linked List Size : %d \n",ptrList->size);

	if(tempNode == NULL)
	{
		printf("linked list no data \n");
	}

	while(tempNode != NULL )
	{
		printf("%d \n",tempNode->data.num);
		printf("%c \n",tempNode->data.chr);
		printf("%s \n", tempNode->data.string);

		tempNode = tempNode->next;
	}
}



void insertData(node_t *newNode, data_t data)
{
	newNode->data.num = data.num;
	newNode->data.chr = data.chr;
	strcpy(newNode->data.string, data.string);
}


int main()
{
	/*데이터 구조체를 만들고 데이터 삽입*/
	data_t data;

	data.num = 1;
	data.chr = 'A';
	strncpy(data.string,"STRING1",STRING_LEN);


	data_t data2;

	data2.num = 2;
	data2.chr = 'B';
	strncpy(data2.string,"STRING2",STRING_LEN);



	data_t data3;

	data3.num = 3;
	data3.chr = 'C';
	strncpy(data3.string,"STRING3",STRING_LEN);

	data_t data4;

	data4.num = 4;
	data4.chr = 'D';
	strncpy(data4.string,"STRING4",STRING_LEN);


	linkedList_t list;
	initLinkedList(&list);
	createNode(&list,data);
	createNode(&list,data2);
	createNode(&list,data3);
	createNode(&list,data4);

	node_t* tmpNode = list.head;
	while(tmpNode != NULL )
	{

		if(tmpNode->data.chr == 'A')
		{
			deleteNode( &list,tmpNode);
		}
/*
		if(tmpNode->data.chr == 'B')
		{
			deleteNode( &list,tmpNode);
		}

		if(tmpNode->data.chr == 'C')
		{
			deleteNode( &list,tmpNode);
		}
*/
		if(tmpNode->data.chr == 'D')
		{
			deleteNode( &list,tmpNode);
		}

		tmpNode = tmpNode->next;
	}


	printNode(&list);
}
