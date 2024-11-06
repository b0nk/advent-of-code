#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 100


int is_low_point(int map[][MAP_SIZE], int row, int col){
	int low_count = 0;

	//up
	if(map[row][col] < (row != 0 ? map[row - 1][col] : 10)){
		low_count++;
	}
	//down
	if(map[row][col] < ((row != (MAP_SIZE - 1)) ? map[row + 1][col] : 10)){
		low_count++;
	}
	//left
	if(map[row][col] < (col != 0 ? map[row][col - 1] : 10)){
		low_count++;
	}
	//right
	if(map[row][col] < ((col != (MAP_SIZE - 1)) ? map[row][col + 1] : 10)){
		low_count++;
	}

	return low_count == 4 ? 1 : 0;
}

int find_low_point_risk(int map[][MAP_SIZE]){
	int result = 0;
	for(int i = 0; i < MAP_SIZE; i++){
		for(int j = 0; j < MAP_SIZE; j++){
			if(is_low_point(map, i, j)){
				result += 1 + map[i][j];
			}
		}
	}
	return result;
}

int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	int map[MAP_SIZE][MAP_SIZE];
	int row = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		int l = strlen(line);
		for(int i = 0; i < l; i++){
			int v = line[i] - '0';
			map[row][i] = v;
		}
		row++;
	}

	part1 = find_low_point_risk(map);

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
