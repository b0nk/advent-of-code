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

unsigned long solve(Node* n){
	unsigned long result = 0;
	for(int i = 0; i < MAP_SIZE; i++){
		if(n->op == '+'){
			result += n->values[i];
		} else {
			result = result == 0 ? n->values[i] : result * n->values[i];
		}
	}
	return result;
}

int main(void) {

	char line[BUFSIZ];
	unsigned long part1 = 0;
	int part2 = 0;
	Node* head = NULL;
	Node* curr = NULL;
	char* tkn = NULL;
	unsigned long x = 0;
	int operations = 0;
	int first_line = 1;
	int i = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
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
				if(!first_line){
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
	while(curr){
		part1 += solve(curr);
		curr = curr->next;
	}

	printf("part1: %lu\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}

