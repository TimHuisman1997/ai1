#include <stdlib.h>
#include <stdio.h>

#include "priorityQ.h"

#define N 500   /* N times N chessboard */

int actions[8][2] = {  /* knight moves */
  {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1,-2}, {1,2}, {2, -1}, {2, 1}
};

int isValidLocation(int x, int y) {
  return (0<=x && x < N && 0<= y && y < N);
}
void printnode(nodes n){
	printf("(x,y)= (%d,%d)\n", n.x,n.y);
	printf(" F=G+H, %d=%d+%d\n", n.f,n.g,n.h);
	printf("\n");
}
	
nodes calculatecosts(int x, int y, nodes current_node, int goalX, int goalY){
	
	nodes NN;
	int A,B;
	
	NN.x = x;
	NN.y = y;
	
	NN.g = current_node.g + 1;
	
	A = x - goalX;
	B = y - goalY;
	NN.h = abs(A) + abs(B);
	
	NN.f = NN.g + NN.h;	
	return NN;
}


int AstarK(int startX, int startY, int goalX, int goalY){
	
	int grid[N][N] = {0};
	Heap openlist = makeHeap();
	nodes current_node;
	int act;
	
	current_node.g = -1;
	
	current_node = calculatecosts(startY, startX, current_node, goalX, goalY);
	
	enqueue(current_node, &openlist);
	
	while (!isEmptyheap(openlist)){
	
			current_node = removeMax(&openlist);
			grid[current_node.x][current_node.y] = 1;
		
			if (current_node.h == 0){
				printf("At goal\n");
				return current_node.f;
			}
					
			for (act=0; act < 8; act++) {
				int r = current_node.x + actions[act][0];
				int c = current_node.y + actions[act][1];
				if ((isValidLocation(r, c)) && (grid[r][c] == 0)) {
					nodes newnode = calculatecosts(r,c, current_node, goalX, goalY);
					enqueue(newnode, &openlist);
				}
			}
	}
	return 0;
}


int main(int argc, char *argv[]) {
  int x0,y0, x1,y1;
  do {
    printf("Start location (x,y) = ");
    scanf("%d %d", &x0, &y0);
  } while (!isValidLocation(x0,y0));
  do {
    printf("Goal location (x,y)  = ");
    scanf("%d %d", &x1, &y1);
  } while (!isValidLocation(x1,y1));

  printf("Length shortest path: %d\n", AstarK(x0,y0, x1,y1));

  
  return 0;
}
	
