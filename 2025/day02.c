#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node Node;
struct Node{
	int left;
	int right;
	Node* next;
};

Node* create_node(int l, int r){
	Node* n = (Node*)malloc(sizeof(Node));
	n->left = l;
	n->right = r;
	return n;
}

int find_invalid(Node* head){
	int result = 0;
	Node* curr = head;

	while(curr){
		char id[12];
		for(int i = curr->left; i < curr->right; i++){
			sprintf(id, "%d", i);
			int half_point = strlen(id) / 2;
			for(int j = 0; j < half_point; j++){
				char left_str[12];
				strncpy(left_str, id, j + 1);
				left_str[j + 1] = '\0';
				char right_str[12];
				strncpy(right_str, &id[j + 1], j + 1);
				right_str[j + 1] = '\0';
				printf("comparing '%s' with '%s'\n", left_str, right_str);
				if(strcmp(left_str, right_str) == 0){

				}
			}
		}
		curr = curr->next;
	}

	return result;
}

int main(void){

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	Node* head = NULL;
	Node* curr = NULL;
	char* tkn;
	int l = 0;
	int r = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		tkn = strtok(line, ",");
		while(tkn){
			sscanf(tkn, "%d-%d", &l, &r);
			if(curr){
				curr->next = create_node(l, r);
				curr = curr->next;
			} else {
				curr = create_node(l, r);
				head = curr;
			}
			tkn = strtok(NULL, ",");
		}
	}

	part1 = find_invalid(head);

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
