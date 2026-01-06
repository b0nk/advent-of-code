#include <stdio.h>
#include <string.h>


#define D_SIZE 150

typedef struct Grid Grid;
struct Grid {
	char c;
	unsigned long ways;
};

int main(void) {

	char line[BUFSIZ];
	int part1 = 0;
	unsigned long part2 = 0;
	Grid diagram[D_SIZE][D_SIZE] = {0};
	int lines = 0;
	int length = 0;
	char c_start = 'S';
	char c_beam = '|';
	char c_empty = '.';

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		if(!length) {
			length = strlen(line);
		}
		for(int i = 0; i < length; i++) {
			diagram[lines][i].c = line[i];
		}
		lines++;
	}

	for (int x = 0; x < length; x++) {
		if (diagram[0][x].c == c_start) {
			diagram[0][x].c = c_beam;
			diagram[0][x].ways = 1;
			break;
		}
	}

	for (int y = 0; y < lines - 1; y++) {
		for (int x = 0; x < length; x++) {

			if (diagram[y][x].c != c_beam) {
				continue;
			}

			switch (diagram[y + 1][x].c) {
			case '.':
				diagram[y + 1][x].c = c_beam;
				diagram[y + 1][x].ways += diagram[y][x].ways;
				break;
			case '|':
				diagram[y + 1][x].ways += diagram[y][x].ways;
				break;
			case '^': {
				int splits = 0;

				if (x > 0) {
					if (diagram[y + 1][x - 1].c == c_empty) {
						diagram[y + 1][x - 1].c = c_beam;
						diagram[y + 1][x - 1].ways += diagram[y][x].ways;
					} else if (diagram[y + 1][x - 1].c == c_beam) {
						diagram[y + 1][x - 1].ways += diagram[y][x].ways;
					}
					splits++;
				}

				if (x < length - 1) {
					if (diagram[y + 1][x + 1].c == c_empty) {
						diagram[y + 1][x + 1].c = c_beam;
						diagram[y + 1][x + 1].ways += diagram[y][x].ways;
					} else if (diagram[y + 1][x + 1].c == c_beam) {
						diagram[y + 1][x + 1].ways += diagram[y][x].ways;
					}
					splits++;
				}

				if (splits) {
					part1++;
				}
				break;
			}
			default:
				break;
			}
		}
	}

	for(int i = 0; i < length; i++) {
		part2 += diagram[lines - 1][i].ways;
	}

	printf("part1: %d\n", part1);
	printf("part2: %lu\n", part2);

	return 0;
}

