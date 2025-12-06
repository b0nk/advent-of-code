#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 10


typedef struct List List;
struct List{
	unsigned long value;
	List* next;
};

typedef struct Node Node;
struct Node{
	unsigned long left;
	unsigned long right;
	Node* next;
};

Node* create_node(unsigned long l, unsigned long r){
	Node* n = (Node*)malloc(sizeof(Node));
	n->left = l;
	n->right = r;
	return n;
}

List* create_list_node(unsigned long v){
	List* l = (List*)malloc(sizeof(List));
	l->value = v;
	return l;
}

List* find_invalids(Node* head){
	Node* curr = head;
	List* head_invalids = NULL;
	List* curr_invalids = NULL;

	while(curr){
		char id[STR_SIZE];
		for(unsigned long i = curr->left; i <= curr->right; i++){
			sprintf(id, "%lu", i);
			int str_length = strlen(id);
			
			if(str_length % 2 != 0){
				continue;
			}
			
			int half_point = str_length / 2;
			char left_str[STR_SIZE];
			strncpy(left_str, id, STR_SIZE);
			left_str[half_point] = '\0';
			char right_str[STR_SIZE];
			strncpy(right_str, &id[half_point], half_point);
			right_str[half_point] = '\0';
			
			if(strcmp(left_str, right_str) == 0){
				if(curr_invalids){
					curr_invalids->next = create_list_node(i);
					curr_invalids = curr_invalids->next;
				} else {
					curr_invalids = create_list_node(i);
					head_invalids = curr_invalids;
				}
			}
		}
		curr = curr->next;
	}
	return head_invalids;
}

int main(void){

	char line[BUFSIZ];
	unsigned long part1 = 0;
	int part2 = 0;
	Node* head = NULL;
	Node* curr = NULL;
	List* head_invalids = NULL;
	List* curr_invalids = NULL;
	char* tkn;
	unsigned long l = 0;
	unsigned long r = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		tkn = strtok(line, ",");
		while(tkn){
			sscanf(tkn, "%lu-%lu", &l, &r);
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

	head_invalids = find_invalids(head);
	curr_invalids = head_invalids;
	
	while(curr_invalids){
		part1 += curr_invalids->value;
		curr_invalids = curr_invalids->next;
	}

	printf("part1: %lu\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
