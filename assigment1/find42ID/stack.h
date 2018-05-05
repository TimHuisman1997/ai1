#ifndef STACK_H
#define STACK_H

#include "state.h"

typedef struct{
	State *array;
	int top;
	int size;
	} Stack;
	
Stack newStack ();

void doubleStackSize(Stack *stp);

void push (State s, Stack *stp);

int isEmptyStack (Stack st);

void stackEmptyError();

State pop(Stack *stp);

void freeStack (Stack st);
	
#endif
