#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

Stack newStack (int s) {
	Stack st;
	st.array = malloc(s*sizeof(State));
	assert(st.array != NULL);
	st.top = 0;
	st.size = s;
	return st;
}

void doubleStackSize(Stack *stp) {
	int newSize = 2 * stp->size;
	stp->array = realloc(stp->array, newSize * sizeof(State));
	assert(stp->array != NULL);
	stp->size = newSize;
}

void push (State s, Stack *stp) {
	if(stp->top == stp->size){
		doubleStackSize(stp);
	}
	stp->array[stp->top] = s;
	(stp->top)++;
}

int isEmptyStack (Stack st) {
	return (st.top == 0);
}

void stackEmptyError() {
	printf("stack empty\n");
	abort();
}

State pop(Stack *stp) {
	if (isEmptyStack(*stp)){
		stackEmptyError();
	}
	(stp->top)--;
	return (stp->array)[stp->top];
}

void freeStack (Stack st){
	free(st.array);
}
	

