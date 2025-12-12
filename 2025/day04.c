#include <stdio.h>
#include <string.h>

#define MAP_SIZE 138


int check_up(char map[MAP_SIZE][MAP_SIZE], int row, int col){
	if(row == 0){
		return 0;
	}
	return map[row - 1][col] == '@';
}

int check_down(char map[MAP_SIZE][MAP_SIZE], int row, int col){
	if(row == MAP_SIZE - 1){
		return 0;
	}
	return map[row + 1][col] == '@';
}

int check_left(char map[MAP_SIZE][MAP_SIZE], int row, int col){
	if(col == 0){
		return 0;
	}
	return map[row][col - 1] == '@';
}

int check_right(char map[MAP_SIZE][MAP_SIZE], int row, int col){
	if(col == MAP_SIZE - 1){
		return 0;
	}
	return map[row][col + 1] == '@';
}

int check_up_left(char map[MAP_SIZE][MAP_SIZE], int row, int col){
	if(row == 0 || col == 0){
		return 0;
	}
	return map[row - 1][col - 1] == '@';
}

int check_up_right(char map[MAP_SIZE][MAP_SIZE], int row, int col){
	if(row == 0 || col == MAP_SIZE - 1){
		return 0;
	}
	return map[row - 1][col + 1] == '@';
}

int check_down_left(char map[MAP_SIZE][MAP_SIZE], int row, int col){
	if(row == MAP_SIZE - 1 || col == 0){
		return 0;
	}
	return map[row + 1][col - 1] == '@';
}

int check_down_right(char map[MAP_SIZE][MAP_SIZE], int row, int col){
	if(row == MAP_SIZE - 1 || col == MAP_SIZE - 1){
		return 0;
	}
	return map[row + 1][col + 1] == '@';
}

int check_access(char map[MAP_SIZE][MAP_SIZE], int row, int col){
	return check_up(map, row, col) +
	check_down(map, row, col) +
	check_left(map, row, col) +
	check_right(map, row, col) +
	check_up_left(map, row, col) +
	check_up_right(map, row, col) +
	check_down_left(map, row, col) +
	check_down_right(map, row, col) < 4;
}

int main(void) {

	char line[BUFSIZ];
	char map[MAP_SIZE][MAP_SIZE] = {0};
	int part1 = 0;
	int part2 = 0;
	int rows = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		for(int cols = 0; cols < MAP_SIZE; cols++){
			map[rows][cols] = line[cols];
		}
		rows++;
	}

	for(int i = 0; i < MAP_SIZE; i++){
		for(int j = 0; j < MAP_SIZE; j++){
			if(map[i][j] == '@'){
				part1 += check_access(map, i, j);
			}
		}
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}

