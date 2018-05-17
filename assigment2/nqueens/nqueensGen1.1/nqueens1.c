#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "state.h"
#include "define.h"
#include "nqueensFunc.h"

void swapInt(int *x, int *y){
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

void initializeRandomGenerator() {
  /* this routine initializes the random generator. You are not
   * supposed to understand this code. You can simply use it.
   */
  time_t t;
  srand((unsigned) time(&t));
}

int* mutation(int* ar){
	ar[rand()%nqueens] = rand()%nqueens;
	return ar;
}

State* offspring(State *pool){
	for(int i = 2; i < POPULATION; i++){
		for(int j = 0; j < nqueens/2; j++){
			swapInt(&(pool[i-2].queens[j]), &(pool[i-1].queens[j]));
		}
		for(int j = nqueens/2; j < nqueens; j++){
			swapInt(&(pool[i-1].queens[j]), &(pool[i].queens[j]));
		}
		pool[i].queens = mutation(pool[i].queens);
		
	}
	
	
	return pool;
}

void geneticSearch(State *pool){
	for(int i = 0; i < MAX_ITER; i++){
		pool = orderArray(offspring(pool));
		if(pool[0].cost == 0){
			printf("Goal Reached\n");
			return;
		}
	}
	printf("Goal Not Reached\n");
	
}



int main(int argc, char *argv[]){
	State *pool = malloc(sizeof(State)*POPULATION);
	initializeRandomGenerator();
	
	printf("Number of queens (1<=nqueens<%d): ", MAXQ);
	scanf("%d", &nqueens);
	
	pool = makePopulation(pool);
	geneticSearch(pool);
	
	
	return 0;
}
