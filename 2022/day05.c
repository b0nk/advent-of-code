#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

char** stacks;
char** stacks_9001;
char** temp_stacks;
int n_stacks;

int is_digit(char c){
	return c >= 48 && c <= 57;
}

char* strrev(char* str) {
	if (!str || ! *str){
		return str;
	}

	int i = strlen(str) - 1, j = 0;
	char ch;

	while (i > j){
		ch = str[i];
		str[i] = str[j];
		str[j] = ch;
		i--;
		j++;
	}
	return str;
}

void add_to_stack(int x, int y, char c, char** s){
	for(int i = 0; i < y; i++){
		if(s[x][i] == '\0'){
			s[x][i] = ' ';
		}
	}
	s[x][y] = c;
	s[x][y+1] = '\0';
}

void convert_stack(){
	char c;
	for(int i = 0; i < n_stacks; i++){
		for(int j = n_stacks - 1; j >= 0; j--){
			c = temp_stacks[i][j];
			if(c == '\0'){
				continue;
			}
			add_to_stack(j, i, c, stacks);
			add_to_stack(j, i, c, stacks_9001);
		}
	}
	for(int k = 0; k < n_stacks; k++){
		stacks[k] = strrev(strtok(strdup(stacks[k]), " "));
		stacks_9001[k] = strrev(strtok(strdup(stacks_9001[k]), " "));
	}
}

char* get_top_of_crates(char** stack){
	char* res = malloc(sizeof(char) * n_stacks);
	char c;
	for(int i = 0, j = 0; i < n_stacks; i++){
		c = stack[i][strlen(stack[i]) - 1];
		if(c != '\0'){
			res[j++] = c;
		}
	}
	return res;
}

void stack_operation(int qty, int from, int to){
	int pos = strlen(stacks[from]) - qty;
	char* carry = strrev(strdup(&stacks[from][pos]));
	char* tmp = malloc(sizeof(**stacks) * STACK_SIZE);
	tmp = strncpy(tmp, stacks[from], pos);
	stacks[from] = tmp;
	tmp = strdup(strcat(stacks[to], carry));
	stacks[to] = tmp;
}

void stack_operation_9001(int qty, int from, int to){
	int pos = strlen(stacks_9001[from]) - qty;
	char* carry = strdup(&stacks_9001[from][pos]);
	char* tmp = malloc(sizeof(**stacks_9001) * STACK_SIZE);
	tmp = strncpy(tmp, stacks_9001[from], pos);
	stacks_9001[from] = tmp;
	tmp = strdup(strcat(stacks_9001[to], carry));
	stacks_9001[to] = tmp;
}

int main(void){

	int j = 0;
	int n = 0;
	int qty = 0;
	int from = 0;
	int to = 0;
	int count = 0;

	temp_stacks = malloc(sizeof(*temp_stacks) * STACK_SIZE);
        for(int i = 0; i < STACK_SIZE; i++){
		temp_stacks[i] = malloc(sizeof(**temp_stacks) * STACK_SIZE);
        }

	int stack_line_length;
	char* n_stack_line;

	char element[3];

	char line[BUFSIZ];

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		if(line[0] == 'm'){
			strtok(line, " ");
			qty = atoi(strtok(NULL, " "));
			strtok(NULL, " ");
			from = atoi(strtok(NULL, " "));
			strtok(NULL, " ");
			to = atoi(strtok(NULL, " "));
			stack_operation(qty, from - 1, to - 1);
			stack_operation_9001(qty, from - 1, to - 1);
		}
		else if(line[0] == '\n'){
			stacks = malloc(sizeof(*stacks) * n_stacks);
			for(int i = 0; i < n_stacks; i++){
				stacks[i] = malloc(sizeof(**stacks) * STACK_SIZE);
			}
			stacks_9001 = malloc(sizeof(*stacks_9001) * n_stacks);
			for(int i = 0; i < n_stacks; i++){
				stacks_9001[i] = malloc(sizeof(**stacks_9001) * STACK_SIZE);
			}
			convert_stack();
			free(temp_stacks);
		}
		else {
			if(line[0] == ' ' && is_digit(line[1])){
				n_stack_line = strtok(line, " ");
				while(n_stack_line != NULL){
					n = atoi(n_stack_line);
					if(n > n_stacks){
						n_stacks = n;
					}
					n_stack_line = strtok(NULL, " ");
				}
			}
			else {
				char* curr_line = strdup(line);
				while(strlen(curr_line) >= 4){
					memcpy(element, curr_line, 3);
					if(element[1] != ' '){
						add_to_stack(j, count, element[1], temp_stacks);
					}
					if(strlen(curr_line) == 4){
						curr_line = NULL;
						break;
					}
					count++;
					curr_line = strdup(&curr_line[4]);
				}
				j++;
				count = 0;
			}
		}
	}

	char* top_of_crates = get_top_of_crates(stacks);
	char* top_of_crates_9001 = get_top_of_crates(stacks_9001);

	printf("part1: %s\n", top_of_crates);
	printf("part2: %s\n", top_of_crates_9001);

	return 0;
}
