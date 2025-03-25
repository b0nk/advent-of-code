#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XMAS "XMAS"
#define LEN_XMAS 4
#define SIZE 140


int check_up(char** map, int row, int col){
	if(row < LEN_XMAS - 1){
		return 0;
	}
	for(int i = 0; i < LEN_XMAS; i++){
		if(map[row - i][col] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_down(char** map, int row, int col){
	if(LEN_XMAS + row > SIZE){
		return 0;
	}
	for(int i = 0; i < LEN_XMAS; i++){
		if(map[row + i][col] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_left(char** map, int row, int col){
	if(col < LEN_XMAS - 1){
		return 0;
	}
	for(int i = 0; i < LEN_XMAS; i++){
		if(map[row][col - i] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_right(char** map, int row, int col){
	if(LEN_XMAS + col > SIZE){
		return 0;
	}
	for(int i = 0; i < LEN_XMAS; i++){
		if(map[row][col + i] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_up_left(char** map, int row, int col){
	if(row < LEN_XMAS - 1 || col < LEN_XMAS - 1){
		return 0;
	}
	for(int i = 0; i < LEN_XMAS; i++){
		if(map[row - i][col - i] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_up_right(char** map, int row, int col){
	if(row < LEN_XMAS - 1 || LEN_XMAS + col > SIZE){
		return 0;
	}
	for(int i = 0; i < LEN_XMAS; i++){
		if(map[row - i][col + i] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_down_left(char** map, int row, int col){
	if(LEN_XMAS + row > SIZE || col < LEN_XMAS - 1){
		return 0;
	}
	for(int i = 0; i < LEN_XMAS; i++){
		if(map[row + i][col - i] != XMAS[i]){
			return 0;
		}
	}
	return 1;
}

int check_down_right(char** map, int row, int col){
	if(LEN_XMAS + row > SIZE || LEN_XMAS + col > SIZE){
		return 0;
	}
	for(int i = 0; i < LEN_XMAS; i++){
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

int check_MAS(char** map, int row, int col){
	if(row - 1 < 0 || row + 1 >= SIZE) return 0;
	if(col - 1 < 0 || col + 1 >= SIZE) return 0;
	if (
		((map[row - 1][col - 1] == 'M' && map[row + 1][col + 1] == 'S') &&
		(map[row - 1][col + 1] == 'S' && map[row + 1][col - 1] == 'M'))
		||
		((map[row - 1][col - 1] == 'S' && map[row + 1][col + 1] == 'M') &&
		(map[row - 1][col + 1] == 'M' && map[row + 1][col - 1] == 'S'))
		||
		((map[row - 1][col - 1] == 'M' && map[row + 1][col + 1] == 'S') &&
		(map[row - 1][col + 1] == 'M' && map[row + 1][col - 1] == 'S'))
		||
		((map[row - 1][col - 1] == 'S' && map[row + 1][col + 1] == 'M') &&
		(map[row - 1][col + 1] == 'S' && map[row + 1][col - 1] == 'M'))
		){
			return 1;
		}
	return 0;
}

void find_occurrences(char** map, int lines, int* part1, int* part2){
	for(int row = 0; row < lines; row++){
		for(int col = 0; col < SIZE; col++){
			if(map[row][col] == 'X'){
				*part1 += check_XMAS(map, row, col);
			}
			if(map[row][col] == 'A'){
				*part2 += check_MAS(map, row, col);
			}
		}
	}
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

	find_occurrences(soup, lines, &part1, &part2);

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
