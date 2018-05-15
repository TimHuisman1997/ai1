#include <stdio.h>
#include <stdlib.h>

void dfs(int x, int goal, int limit, int *goalReached){
	if (x == goal){
		*goalReached = 1;
		return;
	}
	
	if (limit == 0){
		return;
	}
	
    dfs(x+1, goal, limit-1, goalReached);
    dfs(x*2, goal, limit-1, goalReached);
    dfs(x*3, goal, limit-1, goalReached);
    dfs(x-1, goal, limit-1, goalReached);
    dfs(x/2, goal, limit-1, goalReached);
    dfs(x/3, goal, limit-1, goalReached);
}

void ids(int start, int goal){
	int goalReached = 0;
	for(int i = 0; i < 1000; i++){
		dfs(start, goal, i, &goalReached);
	}
	
	if (goalReached == 1){
		printf("Goal Reached\n");
	} else {
		printf("Goal Not Reacheable\n");
	}
}


int main(int argc, char *argv[]) {
	int start, goal;
	scanf("%d %d", &start, &goal);
	ids(start, goal);	
	
	return 0;
}
