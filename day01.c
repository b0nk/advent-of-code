#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_window_value(int window[3]){
	int result = 0;
	for(int i = 0; i < 3; i++){
		result += window[i];
	}
	return result;
}

void add_to_window(int v, int window[3], int* idx, int* full){
	window[*idx] = v;
	*idx = *idx + 1;
	if(*idx == 3){
		*full = 1;
		*idx = 0;
	}
}

int main(){

	char line[BUFSIZ];
	int current;
	int previous = (unsigned int) - 1 >> 1; //max int
	int increased = 0;
	int window[3] = {0};
	int window_full = 0;
	int window_index = 0;
	int window_increased = 0;
	int window_previous = (unsigned int) - 1 >> 1; //max int

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		current = atoi(line);
		if(current > previous){
			increased++;
		}
		previous = current;

		add_to_window(current, window, &window_index, &window_full);
		if(window_full == 0){
			continue;
		}
		int window_current = get_window_value(window);
		if(window_current > window_previous){
			window_increased++;
		}
		window_previous = window_current;
	}

	printf("part1: %d\n", increased);
	printf("part2: %d\n", window_increased);

	return 0;
}
