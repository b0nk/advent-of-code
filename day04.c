#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 10
#define GRID_SIZE 5


typedef struct{
	int value;
	int marked;
} Number;

typedef struct {
	Number n[5][5];
	int total_sum;
	int bingoed;
} Board;

void print_board(Board* b, int i){
	printf("Board: %d, total: %d\n", i, b->total_sum);
	for(int row = 0; row < 5; row++){
		for(int col = 0; col < 5; col++){
			if(b->n[row][col].marked){
				printf("%d* ", b->n[row][col].value);
			} else {
				printf("%d ", b->n[row][col].value);
			}
		}
		printf("\n");
	}
}

int is_bingo(Board* b){
	int row_marked = 0;
	int col_marked = 0;
	for(int row = 0; row < 5; row++){
		row_marked = 0;
		col_marked = 0;
		for(int col = 0; col < 5; col++){
			row_marked += b->n[row][col].marked;
			col_marked += b->n[col][row].marked;
		}
		if(row_marked == 5 || col_marked == 5){
			return 1;
		}
	}
	return 0;
}

int main(){

	char line[BUFSIZ];
	int** draw = malloc(sizeof(int*) * 200);
	int draws = 0;
	Board** boards = malloc(sizeof(Board*) * LIMIT);
	int n_boards = 0;
	int limit = LIMIT;
	int row = 0;
	int part1 = 0;
	int part2 = 0;
	int bingoed = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		if(draws == 0){
			char* tkn = strtok(line, ",");
			while(tkn != NULL){
				int v = atoi(tkn);
				draw[draws] = malloc(sizeof(int));
				memcpy(draw[draws++], &v, sizeof(int));
				tkn = strtok(NULL, ",");
			}
			continue;
		}
		if(strlen(line) == 0){
			boards[n_boards] = malloc(sizeof(Board));
			boards[n_boards]->total_sum = 0;
			boards[n_boards++]->bingoed = 0;
			if(n_boards == limit){
				limit += LIMIT;
				boards = realloc(boards, sizeof(Board*) * limit);
			}
			row = 0;
			continue;
		}
		char* tkn = strtok(line, " ");
		int col = 0;
		while(tkn != NULL){
			int v = atoi(tkn);
			boards[n_boards - 1]->n[row][col].value = v;
			boards[n_boards - 1]->n[row][col++].marked = 0;
			boards[n_boards - 1]->total_sum += v;
			tkn = strtok(NULL, " ");
		}
		row++;
	}

	for(int i = 0; i < draws; i++){
		int d = *draw[i];
		for(int j = 0; j < n_boards; j++){
			Board* b = boards[j];
			if(b->bingoed){
				continue;
			}
			for(int row = 0; row < 5; row++){
				int found = 0;
				for(int col = 0; col < 5; col++){
					if(d == b->n[row][col].value){
						b->n[row][col].marked = 1;
						b->total_sum -= d;
						found = 1;
						break;
					}
				}
				if(found){
					break;
				}
			}
			if(i >= 5){
				if(is_bingo(b)){
					if(part1 == 0){
						part1 = d * b->total_sum;
					}
					b->bingoed = 1;
					bingoed++;
					if(bingoed == n_boards){
						part2 = d * b->total_sum;
					}
					break;
				}
			}

		}
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
