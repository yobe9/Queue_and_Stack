/***********************
* Yoav Berger
* 313268393
* 01
* ass5
***********************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"
#include "element.h"
#include "queue.h"

/******************
* Function Name: initQueue
* Input:
* Output: Queue*
* Function Operation: initialize Queue and return the pointer of the new Queue
******************/
Queue* initQueue()
{
	Queue* queueptr = (Queue*)malloc(sizeof(Queue));
	if (queueptr == NULL)
	{
		printf("queue.c initqueue queueptr malloc failed");
		return NULL;
	}

	//initiate the stacks inside the queue
	queueptr->s1 = initStack();
	queueptr->s2 = initStack();
	return queueptr;
}

/******************
* Function Name: destroyQueue
* Input: Queue*
* Output: void
* Function Operation: freeing dynamic allocation of Queue and of her 2 stacks
******************/
void destroyQueue(Queue* queueptr)
{
	destroyStack(queueptr->s1);
	destroyStack(queueptr->s2);
	free(queueptr);
}

/******************
* Function Name: isQueueEmpty
* Input: Queue*
* Output: 1/0
* Function Operation: checking if the Queue is empty
******************/
int isQueueEmpty(Queue* queueptr)
{
	if ((isStackEmpty(queueptr->s1) == 1) && (isStackEmpty(queueptr->s2) == 1))
	{
		return 1;
	}
	return 0;
}

/******************
* Function Name: lenOfQueue
* Input: Queue*
* Output: int
* Function Operation: check and return the lenth of Queue
******************/
int lenOfQueue(Queue* queueptr)
{
	return ((lenOfStack(queueptr->s1)) + (lenOfStack(queueptr->s2)));
}

/******************
* Function Name: capacityOfQueue
* Input: Queue*
* Output: int
* Function Operation: return the size of the Queue
******************/
int capacityOfQueue(Queue* queueptr)
{
	return ((capacityOfStack(queueptr->s1)) + (capacityOfStack(queueptr->s2)));
}

/******************
* Function Name: enqueue
* Input: Queue*, Element
* Output: void
* Function Operation: enter new char into the Queue by entering him to the first stack
******************/
void enqueue(Queue* queueptr, Element element)
{
	push(queueptr->s1, element);
}

/******************
* Function Name: dequeue
* Input: Queue*
* Output: Element
* Function Operation: remove top item in the Queue and return it by poping him from second stack
******************/
Element dequeue(Queue* queueptr)
{

	//moving elements from stacks s1 to s2 if its empty
	if (isStackEmpty(queueptr->s2) == 1)
	{
		for(int i = queueptr->s1->topIndex; i>-1; i--)
		{
			Element element = pop(queueptr->s1);
			push(queueptr->s2, element);
		}
	}

	//poping top element of s2 after moving elements
	Element topQueueItem = pop(queueptr->s2);
	return topQueueItem;
}

/******************
* Function Name: peek
* Input: Queue*
* Output: Element
* Function Operation: return the top item in the Queue by using top on the stacks
******************/
Element peek(Queue* queueptr)
{
	if (isStackEmpty(queueptr->s2) == 0)
	{
		return top(queueptr->s2);
	}
	else
	{
		return (queueptr->s1->content[0]);
	}
}
