#include <stdio.h>
#include <string.h>

#define D_SIZE 150


int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	char diagram[D_SIZE][D_SIZE] = {0};
	int lines = 0;
	int length = 0;
	char c_start = 'S';
	char c_beam = '|';
	char c_splitter = '^';

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		if(!length) {
			length = strlen(line);
		}
		memcpy(diagram[lines++], line, length);
	}

	int started = 0;
	for(int i = 0; i < lines - 1; i++) {
		for(int j = 0; j < length; j++) {

			if(diagram[i][j] == c_start) {
				started = 1;
				diagram[i + 1][j] = c_beam;
				break;
			}

			if(!started) {
				continue;
			}

			if(diagram[i - 1][j] == c_beam) {
				if(diagram[i][j] == c_splitter){
					diagram[i][j - 1] = c_beam;
					diagram[i][j + 1] = c_beam;
					part1++;
				} else {
					diagram[i][j] = c_beam;
				}
			}
		}
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}

