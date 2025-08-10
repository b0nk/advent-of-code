#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 5


typedef struct {
	int value;
	int marked;
} Number;

typedef struct {
	Number n[5][5];
	int total_sum;
} Board;

typedef struct Node Node;
struct Node {
	Board* b;
	Node* prev;
	Node* next;
};

int is_bingo(Board* b) {
	int row_marked = 0;
	int col_marked = 0;
	for(int row = 0; row < 5; row++) {
		row_marked = 0;
		col_marked = 0;
		for(int col = 0; col < 5; col++) {
			row_marked += b->n[row][col].marked;
			col_marked += b->n[col][row].marked;
		}
		if(row_marked == 5 || col_marked == 5) {
			return 1;
		}
	}
	return 0;
}

void mark_number(Board* b, int d, int row, int col) {
	b->n[row][col].marked = 1;
	b->total_sum -= d;
}

void unmark_number(Board* b, int row, int col) {
	b->n[row][col].marked = 0;
	b->total_sum += b->n[row][col].value;
}

int find_first_winning_board(int draws, int** draw, Node* head) {
	int result = 0;
	for(int i = 0; i < draws; i++) {
		int d = *draw[i];
		Node* node = head;
		while(node) {
			for(int row = 0; row < 5; row++) {
				int found = 0;
				for(int col = 0; col < 5; col++) {
					if(d == node->b->n[row][col].value) {
						mark_number(node->b, d, row, col);
						found = 1;
						break;
					}
				}
				if(found) {
					break;
				}
			}
			if(i >= 5) {
				if(is_bingo(node->b)) {
					result = d * node->b->total_sum;
					break;
				}
			}
			node = node->next;
		}
		if(result > 0) {
			break;
		}
	}
	return result;
}

Node* remove_board(Node* root, Node* elem) {
	if(root == elem) {
		elem->next->prev = elem->prev;
		return elem->next;
	}
	Node* node = root;
	while(node) {
		if(node == elem) {
			elem->prev->next = elem->next;
			if(elem->next) {
				elem->next->prev = elem->prev;
			}
			return root;
		}
		node = node->next;
	}
	return NULL;
}

int find_last_winning_board(int draws, int** draw, Node* head) {
	for(int i = 0; i < draws; i++) {
		int d = *draw[i];
		Node* node = head;
		while(node) {
			for(int row = 0; row < 5; row++) {
				int found = 0;
				for(int col = 0; col < 5; col++) {
					if(d == node->b->n[row][col].value) {
						mark_number(node->b, d, row, col);
						found = 1;
						break;
					}
				}
				if(found) {
					break;
				}
			}
			node = node->next;
		}
		node = head;
		while(node) {
			if(i >= 5) {
				if(is_bingo(node->b)) {
					if(!node->prev && !node->next) {
						return node->b->total_sum * d;
					}
					head = remove_board(head, node);
					node = head;
				}
			}
			node = node->next;
		}
	}
	return 0;
}

void reset_boards(Node* root) {
	Node* node = root;
	while(node) {
		node->b->total_sum = 0;
		for(int row = 0; row < 5; row++) {
			for(int col = 0; col < 5; col++) {
				unmark_number(node->b, row, col);
			}
		}
		node = node->next;
	}
}

Node* create_board() {
	Node* board = malloc(sizeof(Node));
	board->b = malloc(sizeof(Board));
	board->b->total_sum = 0;
	return board;
}

int main(void) {

	char line[BUFSIZ];
	Node* head = NULL;
	Node* list = NULL;
	int** draw = malloc(sizeof(int*) * 200);
	int draws = 0;
	int row = 0;
	int part1 = 0;
	int part2 = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		if(draws == 0) {
			char* tkn = strtok(line, ",");
			while(tkn != NULL) {
				int v = atoi(tkn);
				draw[draws] = malloc(sizeof(int));
				memcpy(draw[draws++], &v, sizeof(int));
				tkn = strtok(NULL, ",");
			}
			continue;
		}
		if(strlen(line) == 0) {
			if(!list) {
				list = create_board();
				head = list;
			} else {
				list->next = create_board();
				list->next->prev = list;
				list = list->next;
			}
			row = 0;
			continue;
		}
		char* tkn = strtok(line, " ");
		int col = 0;
		while(tkn != NULL) {
			int v = atoi(tkn);
			list->b->n[row][col].value = v;
			list->b->n[row][col++].marked = 0;
			list->b->total_sum += v;
			tkn = strtok(NULL, " ");
		}
		row++;
	}

	part1 = find_first_winning_board(draws, draw, head);
	reset_boards(head);
	part2 = find_last_winning_board(draws, draw, head);

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
