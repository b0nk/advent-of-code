#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node Node;
struct Node {
	char* c;
	Node* prev;
	Node* next;
};

void print_nodes(Node *head) {
	Node *curr = head;
	while (curr != NULL) {
		printf("%s, ", curr->c);
		curr = curr->next;
	}
	printf("\n");
}

Node* create_node(char* line) {
	Node* new_node = malloc(sizeof(Node));
	new_node->c = strdup(line);
	new_node->next = NULL;
	return new_node;
}

Node* duplicate_nodes(Node* original) {
	Node* copy = NULL;
	while(original) {
		if(!copy) {
			copy = create_node(original->c);
		} else {
			copy->next = create_node(original->c);
			copy->next->prev = copy;
			copy = copy->next;
		}
		original = original->next;
	}
	while(copy->prev) {
		copy = copy->prev;
	}
	return copy;
}

int convert_to_binary(char* line) {
	int length = strlen(line);
	int result = 0;
	for(int i = 0; i < length; i++) {
		if(line[i] == '0') {
			result <<= 1;
		} else {
			result = ~(~result << 1); // left shift '1' (slower)
		}
	}
	return result;
}

Node* remove_node(Node* root, Node* elem) {
	if(root == elem) {
		elem->next->prev = elem->prev;
		return elem->next;
	}
	Node* node = root;
	while(node) {
		if(node == elem) {
			elem->prev->next = elem->next;
			if(elem->next) {
				elem->next->prev = elem->prev;
			}
			return root;
		}
		node = node->next;
	}
	return NULL;
}

int get_life_support_rating(Node* node, int pos, int most) {
	if(!node->next) {
		return convert_to_binary(node->c);
	}
	int zeroes = 0;
	int ones = 0;
	Node* root = node;
	while(node) {
		if(node->c[pos] == '0') {
			zeroes++;
		} else {
			ones++;
		}
		node = node->next;
	}
	node = root;
	char most_common_bit = (most ? (zeroes > ones ? '0' : '1') : (zeroes <= ones ? '0' : '1'));
	while (node) {
		if (node->c[pos] != most_common_bit) {
			root = remove_node(root, node);
			node = root;
		} else {
			node = node->next;
		}
	}
	return get_life_support_rating(root, ++pos, most);
}

int main(void) {

	char line[BUFSIZ];
	Node* list = NULL;
	Node* head = NULL;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		if(!list) {
			list = create_node(line);
			head = list;
		}
		else {
			list->next = create_node(line);
			list->next->prev = list;
			list = list->next;
		}
	}

	int ones = 0;
	int zeroes = 0;
	int length = strlen(head->c);
	int gamma = 0;
	int epsilon = 0;

	list = head;
	for(int i = 0; i < length; i++) {
		while(list) {
			if(list->c[i] == '0') {
				zeroes++;
			} else {
				ones++;
			}
			list = list->next;
		}
		if(zeroes > ones) {
			gamma <<= 1;
			epsilon = (epsilon << 1) | 1; // left shift '1' (slower)
		} else {
			gamma = (gamma << 1) | 1; // left shift '1' (slower)
			epsilon <<= 1;
		}
		zeroes = 0;
		ones = 0;
		list = head;
	}

	int o2_rating = 0;
	int co2_rating = 0;

	Node* root1 = duplicate_nodes(head);
	Node* root2 = duplicate_nodes(head);

	o2_rating = get_life_support_rating(root1, 0, 1);
	co2_rating = get_life_support_rating(root2, 0, 0);

	printf("part1: %d\n", gamma * epsilon);
	printf("part2: %d\n", o2_rating * co2_rating);

	return 0;
}
