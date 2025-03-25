#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 100
#define MAP_ROWS 5
#define MAP_COLS 10


typedef struct {
	int x;
	int y;
} Point;

typedef struct PointNode PointNode;
struct PointNode{
	Point p;
	PointNode* prev;
	PointNode* next;
};

typedef struct {
	Point pos;
	PointNode* points_to_visit;
} Basin;

typedef struct BasinNode BasinNode;
struct BasinNode{
	Basin b;
	BasinNode* prev;
	BasinNode* next;
};

BasinNode* create_basin(int x, int y){
	BasinNode* b_node = malloc(sizeof(BasinNode));
	Basin b;
	Point pos;
	pos.x = x;
	pos.y = y;
	b.pos = pos;

	b_node->b = b;
	b_node->next = NULL;
	
	return b_node;
}

int is_low_point(int map[][MAP_COLS], int row, int col){
	int low_count = 0;

	//up
	if(map[row][col] < (row != 0 ? map[row - 1][col] : 10)){
		low_count++;
	}
	//down
	if(map[row][col] < ((row != (MAP_ROWS - 1)) ? map[row + 1][col] : 10)){
		low_count++;
	}
	//left
	if(map[row][col] < (col != 0 ? map[row][col - 1] : 10)){
		low_count++;
	}
	//right
	if(map[row][col] < ((col != (MAP_COLS - 1)) ? map[row][col + 1] : 10)){
		low_count++;
	}

	return low_count == 4 ? 1 : 0;
}

int find_low_point_risk(int map[][MAP_COLS], BasinNode** head){
	int result = 0;
	BasinNode* curr = *head;
	for(int i = 0; i < MAP_ROWS; i++){
		for(int j = 0; j < MAP_COLS; j++){
			if(is_low_point(map, i, j)){
				result += 1 + map[i][j];
				if(curr){
					curr->next = create_basin(i, j);
					curr->next->prev = curr;
					curr = curr->next;
				} else {
					curr = create_basin(i, j);
					*head = curr;
				}
			}
		}
	}
	return result;
}

int find_largest_basins(int map[][MAP_COLS], BasinNode** head){
	int top3[3] = {0};
	BasinNode* curr = *head;
	while(curr){
		curr = curr->next;
	}
	return 0;
}

int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	int map[MAP_ROWS][MAP_COLS];
	BasinNode* head = NULL;
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

	part1 = find_low_point_risk(map, &head);
	part2 = find_largest_basins(map, &head);

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
