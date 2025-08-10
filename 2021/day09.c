#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 100


enum Direction{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

typedef struct {
	int x;
	int y;
} Point;

typedef struct PointNode PointNode;
struct PointNode{
	int size;
	Point p;
	PointNode* next;
	PointNode* visited;
};

PointNode* create_point(int x, int y){
	PointNode* p_node = malloc(sizeof(PointNode));
	Point p;
	p.x = x;
	p.y = y;
	
	p_node->size = 0;
	p_node->p = p;
	p_node->next = NULL;
	p_node->visited = NULL;
	
	return p_node;
}

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

int find_low_point_risk(int map[][MAP_SIZE], PointNode** head){
	int result = 0;
	PointNode* curr = *head;
	for(int i = 0; i < MAP_SIZE; i++){
		for(int j = 0; j < MAP_SIZE; j++){
			if(is_low_point(map, i, j)){
				result += 1 + map[i][j];
				if(curr){
					curr->next = create_point(i, j);
					curr = curr->next;
				} else {
					curr = create_point(i, j);
					*head = curr;
				}
			}
		}
	}
	
	return result;
}

int check_higher(int map[][MAP_SIZE], int x, int y, int direction){
	int current_height = map[x][y];
	switch(direction){
		case UP:
			if(x - 1 >= 0 && map[x - 1][y] > current_height && map[x - 1][y] != 9){
				return 1;
			}
			break;
		case DOWN:
			if(x + 1 <= MAP_SIZE && map[x + 1][y] > current_height && map[x + 1][y] != 9){
				return 1;
			}
			break;
		case LEFT:
			if(y - 1 >= 0 && map[x][y - 1] > current_height && map[x][y - 1] != 9){
				return 1;
			}
			break;
		case RIGHT:
			if(y + 1 <= MAP_SIZE && map[x][y + 1] > current_height && map[x][y + 1] != 9){
				return 1;
			}
			break;
	}
	
	return 0;
}

void add_to_visited(PointNode* p, int x, int y){
	PointNode* visited_head = p->visited;
	PointNode* visited_curr = visited_head;
	if(!visited_curr){
		p->visited = create_point(x, y);
		p->size += 1;
		return;
	}
	while(visited_curr){
		if(visited_curr->p.x == x && visited_curr->p.y == y){
			break;
		}
		if(!visited_curr->next){
			visited_curr->next = create_point(x, y);
			p->size += 1;
			break;
		}
		visited_curr = visited_curr->next;
	}
}

void get_basin_size(PointNode* p, int map[][MAP_SIZE], int x, int y){
	add_to_visited(p, x, y);
	
	if(check_higher(map, x, y, UP)){
		get_basin_size(p, map, x - 1, y);
	}
	if(check_higher(map, x, y, DOWN)){
		get_basin_size(p, map, x + 1, y);
	}
	if(check_higher(map, x, y, LEFT)){
		get_basin_size(p, map, x, y - 1);
	}
	if(check_higher(map, x, y, RIGHT)){
		get_basin_size(p, map, x, y + 1);
	}
}

void process_top3(int top[], int v){
	for(int i = 0; i < 3; i++){
		if(v > top[i]){
			for(int j = 3; j > i; j--){
				top[j] = top[j - 1];
			}
			top[i] = v;
			break;
		}
	}
}

int find_largest_basins(int map[][MAP_SIZE], PointNode** head){
	int top3[3] = {0};
	PointNode* curr = *head;
	while(curr){
		get_basin_size(curr, map, curr->p.x, curr->p.y);
		process_top3(top3, curr->size);
		curr = curr->next;
	}
	
	return top3[0] * top3[1] * top3[2];
}

int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	int map[MAP_SIZE][MAP_SIZE];
	PointNode* head = NULL;
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
