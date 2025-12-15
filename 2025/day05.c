#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node Node;
struct Node {
	unsigned long min;
	unsigned long max;
	Node* next;
};

Node* create_node(unsigned long x, unsigned long y) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->min = x;
	n->max = y;
	return n;
}

int is_fresh(unsigned long id, Node* head){
	Node* curr = head;
	while(curr){
		if(id >= curr->min && id <= curr->max){
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}

int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	Node* head = NULL;
	Node* curr = NULL;
	unsigned long min = 0;
	unsigned long max = 0;
	unsigned long ingredient = 0;
	int ranges = 1;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		if(strlen(line) == 0){
			ranges = 0;
			continue;
		}
		if(ranges){
			sscanf(line, "%lu-%lu", &min, &max);
			if(curr){
				curr->next = create_node(min, max);
				curr = curr->next;
			} else {
				curr = create_node(min, max);
				head = curr;
			}
		} else {
			sscanf(line, "%lu", &ingredient);
			if(is_fresh(ingredient, head)){
				part1++;
			}
		}
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}

