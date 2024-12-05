#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define LIMIT 1000
#define PATTERN "mul\\(([0-9]+),([0-9]+)\\)"


typedef struct Node Node;
struct Node{
	int x;
	int y;
	Node* next;
};

Node* node_create(int x, int y){
	Node* node = malloc(sizeof(Node));
	node->x = x;
	node->y = y;
	node->next = NULL;
	return node;
}

int main(void){

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	regex_t regex;
	int pat_error;
	Node* head = NULL;
	Node* curr = NULL;
	pat_error = regcomp(&regex, PATTERN, REG_EXTENDED);
	if(pat_error != 0){
		return pat_error;
	}
	int nmatch = 3;
	regmatch_t match[nmatch + 1];
	int match_error = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		match_error = regexec(&regex, line, nmatch, match, 0);
		int end_index = 0;
		char value[BUFSIZ];
		while(match_error == 0){
			memset(value, 0, sizeof(value));
			strncpy(value, line + end_index + match[1].rm_so, match[1].rm_eo - match[1].rm_so);
			int x = atoi(value);
			memset(value, 0, sizeof(value));
			strncpy(value, line + end_index + match[2].rm_so, match[2].rm_eo - match[2].rm_so);
			int y = atoi(value);
			if(curr) {
				curr->next = node_create(x, y);
				curr = curr->next;
			} else {
				curr = node_create(x, y);
				head = curr;
			}
			end_index += match[0].rm_eo;
			match_error = regexec(&regex, &line[end_index], nmatch, match, 0);
		}
	}

	curr = head;
	while(curr){
		part1 += curr->x * curr->y;
		curr = curr->next;
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
