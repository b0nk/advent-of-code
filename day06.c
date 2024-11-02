#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DAYS 80
#define INFINITY 256
#define STARTING_TIMER 8
#define RESET_TIMER 6


typedef struct Node Node;
struct Node {
	int fish_timer;
	long fish_amount;
	Node* next;
	Node* prev;
};

Node* create_node(int timer){
	Node* node = malloc(sizeof(Node));
	node->fish_timer = timer;
	node->fish_amount = 0;
	node->next = NULL;
	return node;
}

Node* init_circular_buffer(){
	Node* head = create_node(-1);
	Node* curr = head;
	for(int i = 0; i <= STARTING_TIMER; i++){
		curr->next = create_node(i);
		curr->next->prev = curr;
		curr = curr->next;
	}
	head->prev = curr;
	curr->next = head;
	return head;
}

long count_fish(Node* head){
	long result = 0;
	Node* curr = head;
	do {
		result += curr->fish_amount;
		curr = curr->next;
	} while (curr->next != head);
	return result;
}

void shift_left(Node* head){
	Node* curr = head;
	int first_fish_amount = curr->fish_amount;

	do {
		curr->fish_amount = curr->next->fish_amount;
		curr = curr->next;
	} while (curr->next != head);

	curr->fish_amount = first_fish_amount;
}

void reset_timers(Node* head, long* fish_to_create){
	Node* curr = head;
	do {
		if(curr->fish_timer == -1){
			*fish_to_create = curr->fish_amount;
			curr->fish_amount = 0;
		}
		if(curr->fish_timer == 6){
			curr->fish_amount += *fish_to_create;
		}
		curr = curr->next;
	} while (curr != head);
}

void create_fish(Node* head, long amount){
	Node* curr = head;
	do {
		if(curr->fish_timer == 8){
			curr->fish_amount = amount;
		}
		curr = curr->next;
	} while (curr != head);
}

void process_80_days(Node* head){
	long fish_to_create = 0;
	for(int i = 0; i <= DAYS; i++){
		shift_left(head);
		reset_timers(head, &fish_to_create);
		create_fish(head, fish_to_create);
	}
}

void process_256_days(Node* head){
	long fish_to_create = 0;
	for(int i = DAYS; i < INFINITY; i++){
		shift_left(head);
		reset_timers(head, &fish_to_create);
		create_fish(head, fish_to_create);
	}
}

void insert_fish(Node* head, int timer){
	Node* curr = head;
	while(curr->fish_timer != timer){
		curr = curr->next;
	}
	curr->fish_amount += 1;
}

int main(void) {

	char line[BUFSIZ];
	long part1 = 0;
	long part2 = 0;
	Node* head = init_circular_buffer();

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		char* tkn = strtok(line, ",");
		while(tkn){
			int timer = atoi(tkn);
			insert_fish(head, timer);
			tkn = strtok(NULL, ",");
		}
	}

	process_80_days(head);
	part1 = count_fish(head);
	process_256_days(head);
	part2 = count_fish(head);

	printf("part1: %ld\n", part1);
	printf("part2: %ld\n", part2);

	return 0;
}
