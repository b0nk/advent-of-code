#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 1000


typedef struct {
	int x1;
	int x2;
	int y1;
	int y2;
} Range;

typedef struct Node Node;
struct Node {
	Range* r;
	Node* next;
};

Node* create_range(int x1, int y1, int x2, int y2) {
	Node* range = malloc(sizeof(Node));
	range->r = malloc(sizeof(Range));
	range->r->x1 = x1;
	range->r->y1 = y1;
	range->r->x2 = x2;
	range->r->y2 = y2;
	range->next = NULL;
	return range;
}

void init_map(int map[][MAP_SIZE]){
	memset(map, 0, MAP_SIZE * MAP_SIZE * sizeof(int));
}

int is_horizontal(Range* range){
	return range->y1 == range->y2;
}

int is_vertical(Range* range){
	return range->x1 == range->x2;
}

int is_horizontal_or_vertical(Range* range){
	return is_horizontal(range) || is_vertical(range);
}

void draw_pipe(int map[][MAP_SIZE], Range* range){
	if(is_horizontal(range)){
		if(range->x1 > range->x2){
			for(int i = range->x2; i <= range->x1; i++){
				map[i][range->y1] += 1;
			}
		} else {
			for(int i = range->x2; i >= range->x1; i--){
				map[i][range->y1] += 1;
			}
		}
	}
	else if(is_vertical(range)){
		if(range->y1 > range->y2){
			for(int i = range->y2; i <= range->y1; i++){
				map[range->x1][i] += 1;
			}
		} else {
			for(int i = range->y2; i >= range->y1; i--){
				map[range->x1][i] += 1;
			}
		}
	} else {
		int points = abs(range->x1 - range->x2) + 1;
		if(range->x1 > range->x2){
			if(range->y1 > range->y2){
				for(int i = 0; i < points; i++){
					map[abs(range->x1 - i)][abs(range->y1 - i)] += 1;
				}
			} else {
				for(int i = 0; i < points; i++){
					map[abs(range->x1 - i)][abs(range->y1 + i)] += 1;
				}
			}
		} else {
			if(range->y1 > range->y2){
				for(int i = 0; i < points; i++){
					map[abs(range->x1 + i)][abs(range->y1 - i)] += 1;
				}
			} else {
				for(int i = 0; i < points; i++){
					map[abs(range->x1 + i)][abs(range->y1 + i)] += 1;
				}
			}
		}
	}
}

void process_horizontal_vertical(int map[][MAP_SIZE], Node* root){
	Node* curr = root;
	while(curr){
		if(is_horizontal_or_vertical(curr->r)){
			draw_pipe(map, curr->r);
		}
		curr = curr->next;
	}
}

int count_overlaps(int map[][MAP_SIZE]){
	int result = 0;
	for(int i = 0; i < MAP_SIZE; i++){
		for(int j = 0; j < MAP_SIZE; j++){
			if(map[j][i] >= 2){
				result++;
			}
		}
	}
	return result;
}

void process_diagonal(int map[][MAP_SIZE], Node* root){
	Node* curr = root;
	while(curr){
		if(!is_horizontal_or_vertical(curr->r)){
			draw_pipe(map, curr->r);
		}
		curr = curr->next;
	}
}

int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	Node* head = NULL;
	Node* curr = NULL;
	int map[MAP_SIZE][MAP_SIZE];

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		int x1, y1, x2, y2;
		sscanf(line, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
		if(!curr){
			curr = create_range(x1, y1, x2, y2);
			head = curr;
		} else {
			curr->next = create_range(x1, y1, x2, y2);
			curr = curr->next;
		}
	}

	init_map(map);
	process_horizontal_vertical(map, head);
	part1 = count_overlaps(map);
	process_diagonal(map, head);
	part2 = count_overlaps(map);

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
