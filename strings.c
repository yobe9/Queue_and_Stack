/***********************
* Yoav Berger
* 
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

#define REGULAR_PARANTHESIS_DIFF 1
#define OTHER_PARANTHESIS_DIFF 2

/******************
* Function Name: isLegalString
* Input: char
* Output: int
* Function Operation: checks if string is leagal by the rules of the paranthesis
******************/
int isLegalString(char str[])
{

	//initiate stack for saving paranthesis
	Stack* stackptr = initStack();

	//iterating threw the string
	int stringLengh = strlen(str);
	for (int i = 0; i < stringLengh; i++)
	{
		//if arrived to paranthesis insert it to the stack
		if ((str[i] == '(') || (str[i] == '[') || (str[i] == '{') || (str[i] == '<'))
		{
			Element element;
			element.c = str[i];
			push(stackptr, element);
		}

		//checking if paranthesis closers are fits unless not empty
		if (str[i] == ')')
		{
			if (isStackEmpty(stackptr) == 1)
			{
				destroyStack(stackptr);
				return 0;
			}
			else
			{
				Element topStack;
				topStack = pop(stackptr);

				//checks if the difference of the paranthesis are right
				if (str[i] - topStack.c != REGULAR_PARANTHESIS_DIFF)
				{
					destroyStack(stackptr);
					return 0;
				}
			}

		}
		if ((str[i] == ']') || (str[i] == '}') || (str[i] == '>'))
		{
			if (isStackEmpty(stackptr) == 1)
			{
				destroyStack(stackptr);
				return 0;
			}
			else
			{

				//checks if the difference of the paranthesis are right
				Element topStack2;
				topStack2 = pop(stackptr);
				if (str[i] - topStack2.c != OTHER_PARANTHESIS_DIFF)
				{
					destroyStack(stackptr);
					return 0;
				}
			}
		}
	}

	//checks if all the open paranthesis had been check
	if (isStackEmpty(stackptr) == 0)
	{
		destroyStack(stackptr);
		return 0;
	}
	destroyStack(stackptr);
	return 1;
}