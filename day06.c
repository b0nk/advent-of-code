#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DAYS 80
#define STARTING_TIMER 8
#define RESET_TIMER 6


typedef struct Node Node;
struct Node {
	int timer;
	Node* next;
};

Node* create_fish(int v){
	Node* fish = malloc(sizeof(Node));
	fish->timer = v;
	fish->next = NULL;
	return fish;
}

long count_fish(Node* head){
	long result = 0;
	Node* curr = head;
	while(curr){
		result += 1;
		curr = curr->next;
	}
	return result;
}

void process_80_days(Node* head){
	for(int i = 0; i < DAYS; i++){
		Node* curr = head;
		while(curr){
			curr->timer -= 1;
			curr = curr->next;
		}
		curr = head;
		int reset_count = 0;
		while(curr){
			if(curr->timer == -1){
				curr->timer = RESET_TIMER;
				reset_count++;
			}
			curr = curr->next;
		}
		curr = head;
		while(curr){
			if(!curr->next){
				for(int j = 0; j < reset_count; j++){
					curr->next = create_fish(STARTING_TIMER);
					curr = curr->next;
				}
			}
			curr = curr->next;
		}
		curr = head;
	}
}

int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	Node* head = NULL;
	Node* curr = NULL;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		char* tkn = strtok(line, ",");
		while(tkn){
			int v = atoi(tkn);
			if(!curr){
				curr = create_fish(v);
				head = curr;
			} else {
				curr->next = create_fish(v);
				curr = curr->next;
			}
			tkn = strtok(NULL, ",");
		}
	}

	process_80_days(head);
	part1 = count_fish(head);

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
