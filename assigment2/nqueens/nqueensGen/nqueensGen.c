#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "state.h"
#include "list.h"
#include "priorityQueue.h"


#define MAXQ 100
#define POP 500
#define SAMPS 8

#define FALSE 0
#define TRUE  1

#define ABS(a) ((a) < 0 ? (-(a)) : (a))

int nqueens;

void swap(int *x, int *y){
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

void initializeRandomGenerator() {
  /* this routine initializes the random generator. */

  srand((unsigned int) time(NULL));
}

int inConflict(int row0, int column0, int row1, int column1) {
  if (row0 == row1) return TRUE; /* on same row, */
  if (column0 == column1) return TRUE; /* column, */
  if (ABS(row0-row1) == ABS(column0-column1)) return TRUE;/* diagonal */
  return FALSE; /* no conflict */
}

int countConflicts(int *queens) {
  int cnt = 0;
  int queen, other;
  for (queen=0; queen < nqueens; queen++) {
    for (other=queen+1; other < nqueens; other++) {
      if (inConflict(queen, queens[queen], other, queens[other])) {
        cnt++;
      }
    }
  }
  return cnt;
}



State makeState(){
	State s;
	s.queens = malloc(sizeof(int)*nqueens);
	for (int i = 0; i < nqueens; i++){
		s.queens[i] = (random()%nqueens);
	}
	s.cost = countConflicts(s.queens);
	return s;
}

List makePopulation(List li){
	State s;
	
	for(int i = 0; i < POP; i++){
		s = makeState();
		li = addItem(s, li);
	}
	
	return li;
}

void printState(State s){
	for(int i = 0; i < nqueens; i++){
		printf("%d ", s.queens[i]);
	}
	printf("cost: %d\n", s.cost);
}

State mutation(State s){
	int n = random()%20;
	switch(n){
		case 1: s.queens[random()%nqueens] = random()%nqueens;
		break;
	}
	
	return s;
}

void offSpring(State* s1, State* s2){
	int n = nqueens/2;
	for(int i = 0; i < n; i++){
		swap(&(s1->queens[i]), &(s2->queens[i]));
	}
	*s1 = mutation(*s1);
	*s2 = mutation(*s2);
	s1->cost = countConflicts(s1->queens);
	s2->cost = countConflicts(s2->queens);
	
}


	

void geneticSearch(List li){
	PrioQueue sample = newEmptyQueue();
	State parent1, parent2, tempS;
	for(int j = 0; j < 1000; j++){
		
	for(int i = 0; i < SAMPS; i++){
		li = removeItemAtPos(li, random()%(nqueens-i), &tempS);
		enqueue(tempS, &sample);
	}
	
	parent1 = removeMax(&sample);
	parent2 = removeMax(&sample);
	offSpring(&parent1, &parent2);
	printState(parent1);
	if(parent1.cost == 0 || parent2.cost == 0){
		printf("goal reached\n");
		break;
	}
	while(!isEmptyQueue(sample)){
		li = addItem(removeMax(&sample), li);
	}
	li = addItem(parent1, li);
	li = addItem(parent2, li);
}
}

	


int main(int argc, char *argv[]){
	List pool = newEmptyList();
	
	do{
		printf("Number of queens (1<=nqueens<%d): ", MAXQ);
		scanf("%d", &nqueens);
	} while ((nqueens < 1) || (nqueens > MAXQ));
	
	pool = makePopulation(pool);
	
	geneticSearch(pool);

	
	return 0;
}
