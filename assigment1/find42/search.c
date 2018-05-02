#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state.h"
#include "fringe.h"

#define RANGE 1000000

Fringe insertValidSucc(Fringe fringe, int value, int goal, int a) {
  State s;
  if (((value <= 0) || (value > RANGE)) && !(value == goal)) {
    /* ignore states that are out of bounds */
    return fringe;
  }
  s.parent = fringe.states;
  s.action = a;
  s.value = value;
  s.depth = fringe.states->depth + 1;
  //printf("%d\n", s.depth);
  
  return insertFringe(fringe, s);
}

void reversePath(State* s, int depth, int **arr){
	printf("%d\n", depth);
	while(depth-1 > 0){
		
		arr[depth][0] = s->value;
		arr[depth][1] = s->action;
		s = s->parent;
		depth -= 1;
	}
}
	
	
void showPath(State *s){
	int cost = 0, depth = s->depth;
	int **arr;
	arr = malloc(sizeof(int*) * depth);
	for(int i = 0; i<depth; i++){
		arr[i] = malloc(sizeof(int)*2);
	}
	printf("\n");
	reversePath(s, depth, arr);
	printf("x\n");
	for(int i = 0; i<depth; i++){
		switch(arr[i][1]){
			case 1: printf("%d (+1)-> ", arr[i][0]);
			cost += 1;
			break;
			case 2: printf("%d (*2)-> ", arr[i][0]); 
			cost += 2;
			break; 
			case 3: printf("%d (*3)-> ", arr[i][0]);
			cost += 2;
			break;
			case 4: printf("%d (-1)-> ", arr[i][0]);
			cost += 1;
			break;
			case 5: printf("%d (/2)-> ", arr[i][0]);
			cost += 3;
			break;
			case 6: printf("%d (/3)-> ", arr[i][0]);
			cost += 3;
			break;
		}
	}
	printf("\nlength = %d, cost = %d\n", depth, cost);
}
			
void search(int mode, int start, int goal) {
  Fringe fringe;
  State state;
  int goalReached = 0;
  int visited = 0;
  int value;

  fringe = makeFringe(mode);
  state.value = start;
  state.action = 0;
  state.depth = 0;
  state.parent = NULL;
  fringe = insertFringe(fringe, state);
  while (!isEmptyFringe(fringe)) {
    /* get a state from the fringe */
    fringe = removeFringe(fringe, &state);
    visited++;
    /* is state the goal? */
    value = state.value;
    if (value == goal) {
      goalReached = 1;
      break;
    }
    /* insert neighbouring states */
    fringe = insertValidSucc(fringe, value+1, goal, 1); /* rule n->n + 1      */
    fringe = insertValidSucc(fringe, 2*value, goal, 2); /* rule n->2*n        */
    fringe = insertValidSucc(fringe, 3*value, goal, 3); /* rule n->3*n        */
    fringe = insertValidSucc(fringe, value-1, goal, 4); /* rule n->n - 1      */
    fringe = insertValidSucc(fringe, value/2, goal, 5); /* rule n->floor(n/2) */
    fringe = insertValidSucc(fringe, value/3, goal, 6); /* rule n->floor(n/3) */

  }
  if (goalReached == 0) {
    printf("goal not reachable ");
  } else {
    printf("goal reached ");
  }
  printf("(%d nodes visited)\n", visited);
  showStats(fringe);
  showPath(fringe.states);
  deallocFringe(fringe);  
}

int main(int argc, char *argv[]) {
  int start, goal, fringetype;
  if ((argc == 1) || (argc > 4)) {
    fprintf(stderr, "Usage: %s <STACK|FIFO|HEAP> [start] [goal]\n", argv[0]);
    return EXIT_FAILURE;
  }
  fringetype = 0;
  
  if ((strcmp(argv[1], "STACK") == 0) || (strcmp(argv[1], "LIFO") == 0)) { 
    fringetype = STACK;
  } else if (strcmp(argv[1], "FIFO") == 0) {
    fringetype = FIFO;
  } else if ((strcmp(argv[1], "HEAP") == 0) || (strcmp(argv[1], "PRIO") == 0)) {
    fringetype = HEAP;
  }
  if (fringetype == 0) {
    fprintf(stderr, "Usage: %s <STACK|FIFO|HEAP> [start] [goal]\n", argv[0]);
    return EXIT_FAILURE;
  }

  start = 0;
  goal = 42;
  if (argc == 3) {
    goal = atoi(argv[2]);
  } else if (argc == 4) {
    start = atoi(argv[2]);
    goal = atoi(argv[3]);
  }

  printf("Problem: route from %d to %d\n", start, goal);
  search(fringetype, start, goal); 
  return EXIT_SUCCESS;
}
