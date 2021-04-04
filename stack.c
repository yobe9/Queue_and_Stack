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

#define EMPTY -1

/******************
* Function Name: initStack
* Input:
* Output: Stack*
* Function Operation: initialize stack and return the pointer of the new stack
******************/

Stack* initStack()
{

	//allocating dynamic array for stack and checking if allocating success
	Stack* stackptr = (Stack *) malloc(sizeof(Stack));
	if (stackptr == NULL)
	{
		printf("stack.c initstack stackptr malloc failed");
		return NULL;
	}

	//allocating dynamic array for elements and checking if allocation succeed
	stackptr->content = (Element *) malloc(sizeof(Element));
	if (stackptr->content == NULL)
	{
		printf("stack.c initstack stackptr->content malloc failed");
		return NULL;
	}

	//initializing size and top index of the new stack
	stackptr->size = 1;
	stackptr->topIndex = -1;
	return stackptr;
}

/******************
* Function Name: destroyStack
* Input: Stack*
* Output: void
* Function Operation: freeing dynamic allocation of stack and of element array
******************/
void destroyStack(Stack* stackptr)
{
	free(stackptr->content);
	free(stackptr);
}

/******************
* Function Name: isStackEmpty
* Input: Stack*
* Output: 1/0
* Function Operation: checking if the stack is empty
******************/
int isStackEmpty(Stack* stackptr)
{
	if (stackptr->topIndex == EMPTY)
	{
		return 1;
	}
	return 0;
}

/******************
* Function Name: lenOfStack
* Input: Stack*
* Output: int
* Function Operation: check and return the lenth of stack
******************/
int lenOfStack(Stack* stackptr)
{
	return ((stackptr->topIndex) + 1);
}

/******************
* Function Name: capacityOfStack
* Input: Stack*
* Output: int
* Function Operation: return the size of the stack
******************/
int capacityOfStack(Stack* stackptr)
{
	return stackptr->size;
}

/******************
* Function Name: push
* Input: Stack*, Element
* Output: void
* Function Operation: enter new char into the stack and increasing the content arry if needed
******************/
void push(Stack* stackptr, Element element)
{

	//entering new element above the last to element and incresing the index
	stackptr->content[(stackptr->topIndex) + 1] = element;
	stackptr->topIndex = ((stackptr->topIndex) + 1);

	//in case we need to increase the element array
	if (stackptr->topIndex == ((stackptr->size) - 1))
	{
		Element* tmp = stackptr->content;
		stackptr->content = (Element *) realloc(stackptr->content, ((sizeof(element) * stackptr->size) * 2));
		if (stackptr->content == NULL)
		{
			stackptr->content = tmp;
			printf("stack.c push stackptr realloc failed");
		}

		//also increasing the size counter
		else
		{
			stackptr->size = ((stackptr->size) * 2);
		}
		
	}
}

/******************
* Function Name: pop
* Input: Stack*
* Output: Element
* Function Operation: remove top item in the stack and return it, also decreasing the content arry if needed
******************/
Element pop(Stack* stackptr)
{

	//saving the top element in the stack and decresing the top index
	Element topItem = stackptr->content[stackptr->topIndex];
	stackptr->topIndex = ((stackptr->topIndex) - 1);

	//in case we need to decrease the size of the element array
	if ((((stackptr->size) / 2) - 2) == stackptr->topIndex)
	{
		Element* tmp = stackptr->content;
		stackptr->content = (Element*)realloc(stackptr->content, ((stackptr->size) / 2));
		if (stackptr->content == NULL)
		{
			stackptr->content = tmp;
			printf("stack.c pop stackptr realloc failed");
		}

		//if works also decreasing the size counter
		else
		{
			stackptr->size = ((stackptr->size) / 2);
		}
	}
	return topItem;
}

/******************
* Function Name: top
* Input: Stack*
* Output: Element
* Function Operation: return the top item in the stack
******************/
Element top(Stack* stackptr)
{
	return stackptr->content[stackptr->topIndex];
}

/******************
* Function Name: printStack
* Input: Stack*
* Output: void
* Function Operation: printing stack content
******************/
void printStack(Stack* stackptr)
{
	for (int i = stackptr->topIndex + 1; i > 0; i--)
	{
		printf("%d: ", i);
		printElement(stackptr->content[i-1]);
		printf("\n");
	}
}