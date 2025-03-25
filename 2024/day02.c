#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 1000


typedef struct Node Node;
struct Node{
	int level;
	Node* next;
};

typedef struct{
	int safe;
	int levels_n;
	Node* levels;
} Report;

void report_add_level(Report* r, int v){
	Node* head = r->levels;
	Node* curr = head;
	do{
		if(!curr){
			curr = malloc(sizeof(Node));
			curr->level = v;
			r->levels_n += 1;
			r->levels = curr;
			break;
		}
		else if(curr->next == NULL){
			curr->next = malloc(sizeof(Node));
			curr->next->level = v;
			r->levels_n += 1;
			break;
		}
		curr = curr->next;
	}
	while(curr);
}

Report report_create(char* line){
	Report r;
	r.safe = 0;
	r.levels_n = 0;
	r.levels = NULL;
	char* tkn = strtok(line, " ");
	while(tkn){
		int v = atoi(tkn);
		report_add_level(&r, v);
		tkn = strtok(NULL, " ");
	}
	return r;
}

int is_all_increase_decrease(Report* report){
	Node* head = report->levels;
	int prev = head->level;
	Node* curr = head->next;

	int asc = 1;
	int desc = 1;
	while(curr){
		if(curr->level == prev){
			return 0;
		}
		if(curr->level > prev){
			asc = 0;
		} else if (curr->level < prev){
			desc = 0;
		}
		prev = curr->level;
		curr = curr->next;
	}
	return asc || desc;
}

int is_safe_diff(Report* report){
	Node* head = report->levels;
	int prev = head->level;
	Node* curr = head->next;
	while(curr){
		int diff = abs(curr->level - prev);
		if(diff > 3){
			return 0;
		}
		prev = curr->level;
		curr = curr->next;
	}
	return 1;
}

int determine_safety(Report* report){
	report->safe = is_all_increase_decrease(report) && is_safe_diff(report);
	return report->safe;
}

void remove_nth_level(Report* report, int index){
	int counter = 0;
	Node* curr = report->levels;
	Node* prev = curr;
	do{
		if(index == 0){
			report->levels = curr->next;
			break;
		} else if(index == counter){
			prev->next = curr->next;
			break;
		}
		counter++;
		prev = curr;
		curr = curr->next;
	} while(counter <= index);
}

Report* report_copy(Report* orig){
	Report* copy = malloc(sizeof(Report));
	copy->safe = orig->safe;
	copy->levels_n = orig->levels_n;
	Node* curr = orig->levels;
	while(curr){
		report_add_level(copy, curr->level);
		curr = curr->next;
	}
	return copy;
}

int determine_safety_dampener(Report* report){
	Report* temp = report_copy(report);
	for(int i = 0; i < report->levels_n; i++){
		remove_nth_level(temp, i);
		temp->safe = is_all_increase_decrease(temp) && is_safe_diff(temp);
		if(temp->safe){
			break;
		}
		free(temp);
		temp = report_copy(report);
	}
	report->safe = temp->safe;
	free(temp);
	return report->safe;
}

int main(void){

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	Report reports[LIMIT];
	int reports_n = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		reports[reports_n++] = report_create(line);
	}

	for(int i = 0; i < reports_n; i++){
		part1 += determine_safety(&reports[i]);
	}

	part2 = part1;
	for(int i = 0; i < reports_n; i++){
		if(!reports[i].safe){
			part2 += determine_safety_dampener(&reports[i]);
		}
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
