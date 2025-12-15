#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node Node;
struct Node {
	unsigned long min;
	unsigned long max;
	Node* next;
	Node* prev;
};

Node* create_node(unsigned long x, unsigned long y) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->min = x;
	n->max = y;
	return n;
}

int in_range(unsigned long value, Node* range){
	return (value >= range->min) && (value <= range->max);
}

int is_fresh(unsigned long id, Node* head){
	Node* curr = head;
	while(curr){
		if(in_range(id, curr)){
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}

void merge_ranges(Node* head){
	int merged = 0;
	Node* curr1 = head;
	Node* curr2 = NULL;

	do{
		merged = 0;
		while(curr1){
			curr2 = curr1->next;
			while(curr2){
				if(in_range(curr2->min, curr1)
				|| in_range(curr2->max, curr1)
				|| in_range(curr1->min, curr2)
				|| in_range(curr1->max, curr2)
				){
					if(curr2->min < curr1->min){
						curr1->min = curr2->min;
					}
					if(curr2->max > curr1->max){
						curr1->max = curr2->max;
					}
					curr2->prev->next = curr2->next;
					if(curr2->next) {
						curr2->next->prev = curr2->prev;
					}
					merged = 1;
					break;
				}
				curr2 = curr2->next;
			}
			if(merged){
				break;
			}
			curr1 = curr1->next;
		}
	}while(merged);
}

int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	unsigned long part2 = 0;
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
				curr->next->prev = curr;
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

	merge_ranges(head);

	curr = head;
	while(curr){
		part2 += curr->max - curr->min + 1;
		curr = curr->next;
	}

	printf("part1: %d\n", part1);
	printf("part2: %lu\n", part2);

	return 0;
}

