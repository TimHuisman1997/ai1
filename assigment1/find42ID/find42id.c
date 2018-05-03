#include <stdio.h>
#include <stdlib.h>

#include "state.h"
#include "stack.h"

#define RANGE 1000000

State insertValidSucc( State *s, int val){
	State state;
	if((val<0) || (val > RANGE)){
		return 0;
	}
	s->value = val;
	s->depth += 1;
	return 1;
}
	
	
		

void search(int start, int goal){
	State state;
	Stack st = newStack();
	int goalReached = 0, value;
	
	
	state.value = start;
	state.depth = 0;
	
	push(state, st);
	while(!isEmptyStack(st)){
		state = pop(&st);
		value = state.value;
		if (value = goal){
			goalReached = 1;
			break;
		}
		
		
		
		
		
		
			


int main(int argc, char *argv[]) {
	int start, goal;
	scanf("%d %d", &start, &goal);
	
	
	
	

	return 0;
}

