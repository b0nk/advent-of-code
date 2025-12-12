#include <stdio.h>
#include <string.h>

#define MAP_LENGTH 100
#define NUM_BATTERIES 12


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

void update_biggest(int* biggest, int index, int value) {
	biggest[index] = value;

	for (int i = index + 1; i < NUM_BATTERIES; i++) {
		biggest[i] = -1;
	}
}

unsigned long find_largest_joltage(int line[MAP_LENGTH]) {
	int biggest[NUM_BATTERIES] = {-1};
	unsigned long result = 0;

	for(int i = 0; i < MAP_LENGTH; i++) {
		int current = line[i];
		int end_offset = MAP_LENGTH - i;
		int high_number_index = 0;

		if(end_offset > NUM_BATTERIES) {
			high_number_index = 0;
		} else {
			high_number_index = NUM_BATTERIES - end_offset;
		}

		for(int j = high_number_index; j < NUM_BATTERIES; j++) {
			if(current > biggest[j]) {
				update_biggest(biggest, j, current);
				break;
			}
		}
	}

	for (int i = 0; i < NUM_BATTERIES; i++) {
		result = (result * 10) + biggest[i];
	}
	return result;
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
			part2 += find_largest_joltage(map);
			n_lines++;
		}
	}

	printf("part1: %d\n", part1);
	printf("part2: %lu\n", part2);

	return 0;
}

