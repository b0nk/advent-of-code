#include <stdio.h>
#include <string.h>

#define MAP_LENGTH 100


int find_best_batteries(int line[MAP_LENGTH]) {
	int biggest = 0;

	for(int i = 0; i < MAP_LENGTH; i++) {

		for(int j = i + 1; j < MAP_LENGTH; j++) {
			int value = line[i] * 10 + line[j];

			if(value > biggest) {
				biggest = value;
			}
		}
	}
	return biggest;
}

int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	unsigned long part2 = 0;

	int map[MAP_LENGTH] = {0};
	int n_lines = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		if(*line) {
			for(int i = 0; i < MAP_LENGTH; i++) {
				map[i] = line[i] - '0';
			}
			part1 += find_best_batteries(map);
			n_lines++;
		}
	}

	printf("part1: %d\n", part1);
	printf("part2: %lu\n", part2);

	return 0;
}

