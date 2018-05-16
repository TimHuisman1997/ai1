#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "state.h"
#include "list.h"
#include "priorityQueue.h"


#define MAXQ 100
#define POPULATION 100
#define SAMPLE_SIZE 50
#define CHANCE_MUTATION 2
#define MAX_ITER 100000

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
  /* this routine initializes the random generator. You are not
   * supposed to understand this code. You can simply use it.
   */
  time_t t;
  srand((unsigned) time(&t));
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

List makePopulation(List li){
	State s;
	
	for(int i = 0; i < POPULATION; i++){
		s = makeState();
		//printState(s);
		li = addItem(s, li);
	}
	
	return li;
}



State mutation(State s){
	int n = rand()%CHANCE_MUTATION, m;
	switch(n){
		case 1: s.queens[rand()%nqueens] = rand()%nqueens;

		break;
		case 2: do{
					m = rand()%nqueens;
				}while(m==n);
				
				swap(&(s.queens[m]), &(s.queens[n]));

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

int inConflictWithAnotherQueen(int row, int col, int *queens) {
  int queen;
  for (queen=0; queen < nqueens; queen++) {
    if (inConflict(row, col, queen, queens[queen])) {
      if ((row != queen) || (col != queens[queen])) return TRUE;
    }
  }
  return FALSE;
}

void printBoard(int *queens) {
  int row, column; 
  printf("\n");
  for(row = 0; row < nqueens; row++) {
    for(column = 0; column < nqueens; column++) {
      if (queens[row] != column) {
        printf (".");
      } else {
        if (inConflictWithAnotherQueen(row, column, queens)) {
          printf("Q");
        } else {
          printf("q");
        }
      }
    }
    printf("\n");
  }
}

void geneticSearch(List li){
	PrioQueue sample = newEmptyQueue();
	State parent1, parent2, tempS;
	int goalReached = 0, count = 0;
	for(int j = 0; j < MAX_ITER; j++){
		visitListRec(li);
		count += 1;
		for(int i = 0; i < SAMPLE_SIZE; i++){
			li = removeItemAtPos(li, rand()%(POPULATION-i), &tempS);
			enqueue(tempS, &sample);
		}
		
		while(!isEmptyQueue(sample)){
			parent1 = removeMax(&sample);
			parent2 = removeMax(&sample);
			offSpring(&parent1, &parent2);
			if(parent1.cost == 0){
				printf("goal Reached!");
				printBoard(parent1.queens);
				goalReached = 1;
				break;
			}	
			if(parent2.cost == 0){
				printf("goal Reached!");
				printBoard(parent2.queens);
				goalReached = 1;
			}
			
			li = addItem(parent1, li);
			li = addItem(parent2, li);
		}
		if(goalReached == 1) {
			printf("generation: %d\n", count);
			return;
		}
	}
	printf("goal not reached\n");

}

	


int main(int argc, char *argv[]){
	List pool = newEmptyList();
	initializeRandomGenerator();	

	do{
		printf("Number of queens (1<=nqueens<%d): ", MAXQ);
		scanf("%d", &nqueens);
	} while ((nqueens < 1) || (nqueens > MAXQ));
	
	pool = makePopulation(pool);
	geneticSearch(pool);	

	
	return 0;
}
