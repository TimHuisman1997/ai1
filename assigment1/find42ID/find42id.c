#include <stdio.h>
#include <stdlib.h>

#include "state.h"
#include "stack.h"
//#include "stack.c"

#define RANGE 1000000
#define MAXS 500000

void insertValidSucc( State s, int val, Stack *stp, Stack oldStp, int i){
	State state;
	if((val<0) || (val > RANGE) || (s.depth >= i) ){
		return;
	}
	
	for(int j = 0; j < oldStp.top; j++){
		if(val == oldStp.array[j].value){
			return;
		}
	}
	state.value = val;
	state.depth = s.depth + 1;
	push(state, stp);
}

void search(int start, int goal){
	//printf("x\n");
	State state;
	Stack st = newStack(), oldStates = newStack();
	int goalReached = 0, value, i = 0;
	
	
	state.value = start;
	state.depth = 0;
	
	push(state, &st);
	while(i < 10000){
		
		while(!isEmptyStack(st)){
			state = pop(&st);
			push(state, &oldStates);
			value = state.value;
			printf("%d\n", value);
			if (value == goal){
				goalReached = 1;
				break;
			}
		
			insertValidSucc(state, value+1, &st, oldStates, i);
			insertValidSucc(state, value-1, &st, oldStates, i);
			insertValidSucc(state, value/2, &st, oldStates, i);
			insertValidSucc(state, value/3, &st, oldStates, i);
			insertValidSucc(state, value*2, &st, oldStates, i);
			insertValidSucc(state, value*3, &st, oldStates, i);		
		}
		//freeStack(oldStates);
		i++;
	}
	if(goalReached == 1){
		printf("Goal Reached\n");
	} else {
		printf("Goal Not Reachable\n");
	}
}

int main(int argc, char *argv[]) {
	int start, goal;
	scanf("%d %d", &start, &goal);
	search(start, goal);
	return 0;
}

