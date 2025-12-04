#include <stdio.h>
#include <string.h>


void rotate(char direction, int value, int* pos, int* part1, int* part2){
	if(direction == 'L'){
		int passes = (value + 99 - *pos) / 100;
		if(*pos == 0){
			passes -= 1;
		}
		*pos = (*pos - value) % 100;
		if(*pos < 0){
			*pos += 100;
		}
		if(*pos == 0){
			(*part2)++;
		}
		(*part2) += passes;
	} else {
		int passes = (*pos + value) / 100;
		*pos = (*pos + value) % 100;
		(*part2) += passes;
	}
	if(*pos == 0) {
		(*part1)++;
	}
}

int main(void){

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	int dial_pos = 50;
	char dir = '\0';
	int value = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		sscanf(line, "%c%d", &dir, &value);
		rotate(dir, value, &dial_pos, &part1, &part2);
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
