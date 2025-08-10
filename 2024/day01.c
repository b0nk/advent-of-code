#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 1000


int sort_asc(const void *a, const void *b){
	return *(int*)a - *(int*)b;
}

int find_occurrences(int location, int list[LIMIT], int list_size){
	int result = 0;
	for(int i = 0; i < list_size && list[i] <= location; i++){
		if(list[i] == location){
			result++;
		}
	}
	return location * result;
}

int main(void){

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	int right_list[LIMIT];
	int right_n = 0;
	int left_list[LIMIT];
	int left_n = 0;

	int left, right;
	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		sscanf(line, "%d %d", &left, &right);
		left_list[left_n++] = left;
		right_list[right_n++] = right;
	}

	qsort(left_list, left_n, sizeof(int), sort_asc);
	qsort(right_list, right_n, sizeof(int), sort_asc);

	for(int i = 0; i < left_n; i++){
		part1 += abs(left_list[i] - right_list[i]);
		part2 += find_occurrences(left_list[i], right_list, right_n);
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
