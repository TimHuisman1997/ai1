#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listTypeAndFunctions.c"
#include "nodes.h"

#define N 500 /* N times N chessboard */

int actions[8][2] = {  /* knight moves */
  {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1,-2}, {1,2}, {2, -1}, {2, 1}
};

int isValidLocation(int x, int y) {
  return (0<=x && x < N && 0<= y && y < N);
}

Node calculateNodeCosts(int x, int y, int GoalX, int GoalY, Node current_node){
	Node newNode;
	
	newNode.g = current_node.g + 1;
	
    printf("G = %d\n", newNode.g);
	int X = x - GoalX;
	int Y = y - GoalY;
	newNode.h = abs(X) + abs(Y);
	printf("H = %d\n", newNode.h);
	newNode.f = newNode.g + newNode.h;
	printf("F = %d\n", newNode.f);	
	
	return newNode;
}

int Inclosedlist(int r,int c,List closedlist){
	
	while(visitListRec(closedlist)){
		if((r==(closedlist->item).x)&&(c==(closedlist->item).y)){
				return 1;
		}
	}
	return 0;
}

int Inopenlist(Node* NewNode, List openlist){
	
	while(visitListRec(openlist)){
		if((NewNode->x==(openlist->item).x)&&(NewNode->y==(openlist->item).y)){
			if((openlist->item).f < NewNode->f){
				NewNode->f = (openlist->item).f;
				printf("%d", NewNode->f);
				NewNode->g = (openlist->item).g;
				printf("%d", NewNode->g);
				NewNode->h = (openlist->item).h;
				printf("%d", NewNode->h);
				return 1;
			}
		}
	}
	return 0;
	
}


int A_Star_Knight(Node current_node, List openlist, List closedlist, int goalX, int goalY){
	
	Node newnode;
	Node lowestCostnode;
	
	lowestCostnode.f = 999999;
	addItem(current_node, closedlist);
	
	//if possible to go there from current location add to open list
	for (int act=0; act < 8; act++) {
		int r = current_node.x + actions[act][0];
		int c = current_node.y + actions[act][1];
		if (isValidLocation(r,c)){
			if (!(Inclosedlist(r,c,closedlist))) {
				newnode = calculateNodeCosts(r,c,goalX,goalY,current_node);
				}
			if(newnode.h == 0){
				return newnode.f;
			}
			if(!(Inopenlist(&newnode, openlist))){
			addItem(newnode, openlist);
			}
			printf("%d\n", newnode.f);
			if(newnode.f < lowestCostnode.f){
				printf("%d\n", newnode.f);
				lowestCostnode = newnode;
			}
		}
	}
	A_Star_Knight(lowestCostnode,openlist, closedlist,goalX,goalY);
}
	


int main(int argc, char *argv[]) {
  List closed, open;
  closed = newEmptyList();
  open = newEmptyList();
  Node beginning;
  beginning.g=0;
  int x0,y0;
  int x1,y1;
  do {
    printf("Start location (x,y) = ");
    scanf("%d %d", &x0, &y0);
  } while (!isValidLocation(x0,y0));
  do {
    printf("Goal location (x,y)  = ");
    scanf("%d %d", &x1, &y1);
  } while (!isValidLocation(x1,y1));
  
  Node start = calculateNodeCosts(x0, y0,x1,y1, beginning);
  printf("Length shortest path: %d\n", A_Star_Knight(start,open, closed,x1,y1));
  return 0;
}
