#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 20


typedef struct List List;
struct List {
	unsigned long value;
	List* next;
};

typedef struct Node Node;
struct Node {
	unsigned long left;
	unsigned long right;
	Node* next;
};

Node* create_node(unsigned long l, unsigned long r) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->left = l;
	n->right = r;
	return n;
}

List* create_list_node(unsigned long v) {
	List* l = (List*)malloc(sizeof(List));
	l->value = v;
	return l;
}

List* find_invalids(Node* head) {
	Node* curr = head;
	List* head_invalids = NULL;
	List* curr_invalids = NULL;

	while(curr) {
		char id[STR_SIZE];
		for(unsigned long i = curr->left; i <= curr->right; i++) {
			sprintf(id, "%lu", i);
			int str_length = strlen(id);

			if(str_length % 2 != 0) {
				continue;
			}

			int half_point = str_length / 2;
			if (strncmp(id, id + half_point, half_point) == 0) {
				if(curr_invalids) {
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

List* find_invalids_p2(Node* head) {
	Node* curr = head;
	List* head_invalids = NULL;
	List* curr_invalids = NULL;

	while(curr) {
		char id[STR_SIZE];
		for(unsigned long i = curr->left; i <= curr->right; i++) {
			sprintf(id, "%lu", i);
			int str_length = strlen(id);
			int half_point = str_length / 2;
			int found_repeat = 0;

			for(int j = 1; j <= half_point; j++) {

				if(str_length % j != 0) {
					continue;
				}
				int repeat = 1;

				for(int k = j; k < str_length; k++) {
					if(id[k] != id[k % j]) {
						repeat = 0;
						break;
					}
				}

				if(repeat) {
					found_repeat = 1;
					break;
				}
			}

			if(found_repeat) {
				if(curr_invalids) {
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

int main(void) {

	char line[BUFSIZ];
	unsigned long part1 = 0;
	unsigned long part2 = 0;
	Node* head = NULL;
	Node* curr = NULL;
	List* head_invalids = NULL;
	List* curr_invalids = NULL;
	List* head_invalids_p2 = NULL;
	List* curr_invalids_p2 = NULL;
	char* tkn;
	unsigned long l = 0;
	unsigned long r = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		tkn = strtok(line, ",");
		while(tkn) {
			sscanf(tkn, "%lu-%lu", &l, &r);
			if(curr) {
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

	while(curr_invalids) {
		part1 += curr_invalids->value;
		curr_invalids = curr_invalids->next;
	}

	head_invalids_p2 = find_invalids_p2(head);
	curr_invalids_p2 = head_invalids_p2;

	while(curr_invalids_p2) {
		part2 += curr_invalids_p2->value;
		curr_invalids_p2 = curr_invalids_p2->next;
	}

	printf("part1: %lu\n", part1);
	printf("part2: %lu\n", part2);

	return 0;
}

