#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIGNAL_SIZE 10
#define OUTPUT_SIZE 4
#define SEGMENT_LENGTH 8


typedef struct Node Node;
struct Node {
	char signal[SIGNAL_SIZE][SEGMENT_LENGTH];
	char output[OUTPUT_SIZE][SEGMENT_LENGTH];
	Node* next;
	Node* prev;
};

int compare (const void* a, const void* b) {
	return *(char*)a - *(char*)b;
}

char* sort(char* str) {
	qsort(str, strlen(str), sizeof(char), compare);
	return str;
}

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
				snprintf(node->signal[signal_idx], sizeof(node->signal[signal_idx]), "%s", sort(tkn));
				signal_idx++;
			} else {
				snprintf(node->output[output_idx], sizeof(node->output[output_idx]), "%s", sort(tkn));
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

int find_unique_output(Node* head) {
	int result = 0;
	Node* curr = head;
	while(curr) {
		for(int i = 0; i < OUTPUT_SIZE; i++) {
			int l = strlen(curr->output[i]);
			switch(l) {
				case 2: result++; break;
				case 3: result++; break;
				case 4: result++; break;
				case 7: result++; break;
			}
		}
		curr = curr->next;
	}
	return result;
}

int contains_all(char* a, char* b){
	int a_length = strlen(a);
	int b_length = strlen(b);

	for(int i = 0; i < b_length; i++){
		int contains_all = 0;
		for(int j = 0; j < a_length; j++){
			if(b[i] == a[j]){
				contains_all = 1;
				break;
			}
		}
		if(!contains_all) return 0;
	}
	return 1;
}

int total_output(Node* head) {
	int result = 0;
	Node* curr = head;

	while(curr) {
		char* one = "";
		char* four = "";
		char* seven = "";
		char* eight = "";
		for(int i = 0; i < SIGNAL_SIZE; i++) {
			char* sig = curr->signal[i];
			int l = strlen(sig);
			switch(l) {
				case 2:	one = sig; break;
				case 3:	seven = sig; break;
				case 4:	four = sig; break;
				case 7:	eight = sig; break;
				default: break;
			}
		}

		char four_leg[3] = "";
		for(int i = 0; i < 4; i++){
			if(four[i] != one[0] && four[i] != one[1]){
				int pos = strlen(four_leg);
				four_leg[pos]= four[i];
			}
		}

		char* zero = "";
		char* two = "";
		char* three = "";
		char* five = "";
		char* six = "";
		char* nine = "";
		for(int i = 0; i < SIGNAL_SIZE; i++){
			char* sig = curr->signal[i];
			int l = strlen(sig);

			if(l == 5){
				if(contains_all(sig, four_leg)){
					five = sig;
				} else if(contains_all(sig, one)){
					three = sig;
				} else {
					two = sig;
				}
			}

			if (l == 6) {
				if (!contains_all(sig, one)) {
					six = sig;
				} else if (!contains_all(sig, four_leg)) {
					zero = sig;
				} else {
					nine = sig;
				}
			}
		}

		int multiplier = 1000;
		for (int j = 0; j < OUTPUT_SIZE; j++) {
			char *out = curr->output[j];
			if (strcmp(out, zero) == 0)	 result += 0 * multiplier;
			if (strcmp(out, one) == 0)	 result += 1 * multiplier;
			if (strcmp(out, two) == 0)	 result += 2 * multiplier;
			if (strcmp(out, three) == 0) result += 3 * multiplier;
			if (strcmp(out, four) == 0)	 result += 4 * multiplier;
			if (strcmp(out, five) == 0)	 result += 5 * multiplier;
			if (strcmp(out, six) == 0)	 result += 6 * multiplier;
			if (strcmp(out, seven) == 0) result += 7 * multiplier;
			if (strcmp(out, eight) == 0) result += 8 * multiplier;
			if (strcmp(out, nine) == 0)	 result += 9 * multiplier;
			multiplier /= 10;
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
	part2 = total_output(head);

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
