#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAP_SIZE 4

typedef struct Node Node;
struct Node {
	unsigned long values[MAP_SIZE];
	char op;
	Node* next;
};

Node* create_node(unsigned long value) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->values[0] = value;
	return n;
}

unsigned long solve(Node* n) {
	unsigned long result = 0;
	for(int i = 0; i < MAP_SIZE; i++) {
		if(n->op == '+') {
			result += n->values[i];
		} else {
			result = result == 0 ? n->values[i] : result * n->values[i];
		}
	}
	return result;
}

unsigned long op_add(unsigned long a, unsigned long b) {
	return a + b;
}

unsigned long op_mul(unsigned long a, unsigned long b) {
	return a * b;
}

void adjust_lines(char** lines, int n, int length) {
	char padding[BUFSIZ] = {'\0'};
	for(int i = 0; i < n; i++) {
		memset(padding, ' ', length - strlen(lines[i]));
		lines[i] = strcat(lines[i], padding);
		memset(padding, '\0', BUFSIZ);
	}
}

int main(void) {

	char line[BUFSIZ];
	char** lines = malloc(sizeof(char*) * BUFSIZ);
	int n_lines = 0;
	unsigned long part1 = 0;
	unsigned long part2 = 0;
	Node* head = NULL;
	Node* curr = NULL;
	char* tkn = NULL;
	unsigned long x = 0;
	int operations = 0;
	int first_line = 1;
	int i = 0;
	int line_length = 0;
	int max_length = 0;
	char** map;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		line_length = strlen(line);
		if(line_length > max_length) {
			max_length = line_length;
		}
		lines[n_lines] = malloc(sizeof(char) * max_length);
		lines[n_lines++] = strdup(line);

		if(line[0] == '*' || line[0] == '+') {
			operations = 1;
		}
		if(operations) {
			curr = head;
			tkn = strtok(line, " ");
			while(tkn) {
				curr->op = tkn[0];
				curr = curr->next;
				tkn = strtok(NULL, " ");
			}
		} else {
			curr = head;
			tkn = strtok(line, " ");
			while(tkn) {
				sscanf(tkn, "%lu", &x);
				if(!first_line) {
					curr->values[i] = x;
					curr = curr->next;
				} else {
					if(curr) {
						curr->next = create_node(x);
						curr = curr->next;
					} else {
						curr = create_node(x);
						head = curr;
					}
				}
				tkn = strtok(NULL, " ");
			}
			first_line = 0;
			i++;
		}
	}

	curr = head;
	while(curr) {
		part1 += solve(curr);
		curr = curr->next;
	}

	map = malloc(sizeof(char*) * max_length);

	adjust_lines(lines, n_lines, max_length);

	for(int i = 0; i < max_length; i++) {
		map[i] = malloc(sizeof(char*) * n_lines);
		memset(map[i], ' ', n_lines);
	}

	for(int i = 0; i < n_lines; i++) {
		for(int j = 0; j < max_length; j++) {
			map[j][i] = lines[i][j];
		}
	}

	unsigned long rotated = 0;
	unsigned long result = 0;
	unsigned long temp = 0;
	unsigned long (*func)(unsigned long, unsigned long) = NULL;

	for(int i = 0; i < max_length; i++) {
		char op = map[i][n_lines - 1];
		if(op == '+') {
			func = &op_add;
			temp = 0;
		}
		if(op == '*') {
			func = &op_mul;
			temp = 1;
		}
		sscanf(map[i], "%lu", &rotated);

		if(rotated == 0) {
			result += temp;
		} else {
			temp = func(temp, rotated);
		}
		rotated = 0;
	}

	part2 = result + temp;

	printf("part1: %lu\n", part1);
	printf("part2: %lu\n", part2);

	return 0;
}

