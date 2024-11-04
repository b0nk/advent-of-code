#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIGNAL_SIZE 10
#define OUTPUT_SIZE 4


typedef struct Node Node;
struct Node {
	char signal[SIGNAL_SIZE][8];
	char output[OUTPUT_SIZE][8];
	Node* next;
	Node* prev;
};

Node* create_node(char* line) {
	Node* node = malloc(sizeof(Node));

	int left = 1;
	int signal_idx = 0;
	int output_idx = 0;
	char* t1;
	char* pipe_tkn = strtok_r(line, "|", &t1);
	while(pipe_tkn) {
		char* t2;
		char* tkn = strtok_r(pipe_tkn, " ", &t2);
		while(tkn) {
			if (left) {
				snprintf(node->signal[signal_idx], sizeof(node->signal[signal_idx]), "%s", tkn);
                signal_idx++;
            } else {
            	snprintf(node->output[output_idx], sizeof(node->output[output_idx]), "%s", tkn);
                output_idx++;
            }
			tkn = strtok_r(NULL, " ", &t2);
		}
		pipe_tkn = strtok_r(NULL, "|", &t1);
		left = 0;
	}

	node->next = NULL;
	return node;
}

int find_unique_output(Node* head){
	int result = 0;
	Node* curr = head;
	while(curr){
		for(int i = 0; i < OUTPUT_SIZE; i++){
			int l = strlen(curr->output[i]);
			switch(l){
				case 2: result++; break;
				case 3: result++; break;
				case 4: result++; break;
				case 7: result++; break;
				default: break;
			}
		}
		curr = curr->next;
	}
	return result;
}

int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	Node* head = NULL;
	Node* curr = NULL;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		if(curr) {
			curr->next = create_node(line);
			curr->next->prev = curr;
			curr = curr->next;
		} else {
			curr = create_node(line);
			head = curr;
		}
	}

	part1 = find_unique_output(head);

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
