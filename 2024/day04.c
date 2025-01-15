#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XMAS "XMAS"
#define LEN 4
#define SIZE 141


int check_up(char** map, int row, int col){
	if(row < LEN - 1){
		return 0;
	}
	for(int i = 0; i < LEN; i++){
		if(map[row - i][col] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_down(char** map, int row, int col){
	if(LEN + row > SIZE - 1){
		return 0;
	}
	for(int i = 0; i < LEN; i++){
		if(map[row + i][col] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_left(char** map, int row, int col){
	if(col < LEN - 1){
		return 0;
	}
	for(int i = 0; i < LEN; i++){
		if(map[row][col - i] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_right(char** map, int row, int col){
	if(LEN + col > SIZE - 1){
		return 0;
	}
	for(int i = 0; i < LEN; i++){
		if(map[row][col + i] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_up_left(char** map, int row, int col){
	if(row < LEN - 1 || col < LEN - 1){
		return 0;
	}
	for(int i = 0; i < LEN; i++){
		if(map[row - i][col - i] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_up_right(char** map, int row, int col){
	if(row < LEN - 1 || LEN + col > SIZE - 1){
		return 0;
	}
	for(int i = 0; i < LEN; i++){
		if(map[row - i][col + i] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_down_left(char** map, int row, int col){
	if(LEN + row > SIZE - 1 || col < LEN - 1){
		return 0;
	}
	for(int i = 0; i < LEN; i++){
		if(map[row + i][col - i] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_down_right(char** map, int row, int col){
	if(LEN + row > SIZE - 1 || LEN + col > SIZE - 1){
		return 0;
	}
	for(int i = 0; i < LEN; i++){
		if(map[row + i][col + i] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_XMAS(char** map, int row, int col){
	return check_up(map, row, col) +
	check_down(map, row, col) +
	check_left(map, row, col) +
	check_right(map, row, col) +
	check_up_left(map, row, col) +
	check_up_right(map, row, col) +
	check_down_left(map, row, col) +
	check_down_right(map, row, col);
}

int find_occurrences(char** map, int lines){
	int result = 0;
	for(int row = 0; row < lines; row++){
		for(int col = 0; col < SIZE; col++){
			if(map[row][col] == 'X'){
				result += check_XMAS(map, row, col);
			}
		}
	}
	return result;
}

int main(void){

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	char **soup = malloc(SIZE * sizeof(char *));
	int lines = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		soup[lines] = malloc(strlen(line) * sizeof(char));
		sscanf(line, "%s", soup[lines++]);
	}

	part1 = find_occurrences(soup, lines);

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
