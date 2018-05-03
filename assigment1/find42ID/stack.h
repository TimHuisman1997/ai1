#ifndef STACK_H
#define STACK_H

#include "state.h"

typedef struct{
	State *array;
	int top;
	int size;
	} Stack;
	
#endif
