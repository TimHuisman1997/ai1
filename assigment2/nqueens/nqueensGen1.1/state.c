#include <stdio.h>
#include <stdlib.h>

#include "state.h"
#include "nqueensFunc.h"

void swapState(State *x, State *y){
	State t;
	t = *x;
	*x = *y;
	*y = t;
}



State* orderArray(State* ar){
	int j;
	State key;
	for( int i = 0; i < POPULATION; i++){
		key = ar[i];
		j = i-1;
		while(j >= 0 && ar[j].cost > key.cost){
			ar[j+1] = ar[j];
            j = j-1;
		}
		ar[j+1] = key;
	}
	return ar;
}

State makeState(){
	State s;
	s.queens = malloc(sizeof(int)*nqueens);
	for (int i = 0; i < nqueens; i++){
		s.queens[i] = (rand()%nqueens);
	}
	s.cost = countConflicts(s.queens);
	return s;
}

void printState(State s){
	for(int i = 0; i < nqueens; i++){
		printf("%d ", s.queens[i]);
	}
	printf("cost: %d\n", s.cost);
}

State* makePopulation(State *pool){
	for(int i = 0; i < POPULATION; i++){
		pool[i] = makeState(nqueens);
		//printState(pool[i]);
	}
	pool = orderArray(pool);
	return pool;
}
