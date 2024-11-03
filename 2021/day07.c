#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 1000


int least_fuel(int** subs, int n_subs){
	int result = (unsigned int) -1 >> 1; //max int
	for(int i = 0; i < n_subs; i++){
		int fuel = 0;
		for(int j = n_subs - 1; j >= 0; j--){
			fuel += abs(*subs[j] - *subs[i]);
		}
		if(fuel < result){
			result = fuel;
		}
	}
	return result;
}

int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	int** subs = malloc(sizeof(int*) * LIMIT);
	int n_subs = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		char* tkn = strtok(line, ",");
		while(tkn){
			int v = atoi(tkn);
			subs[n_subs] = malloc(sizeof(int));
			memcpy(subs[n_subs++], &v, sizeof(int));
			tkn = strtok(NULL, ",");
		}
	}

	part1 = least_fuel(subs, n_subs);

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
