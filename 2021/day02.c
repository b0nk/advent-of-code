#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FORWARD "forward"
#define UP "up"
#define DOWN "down"


typedef struct {
	int horizontal;
	int depth;
	int aim;
	int depth_direction;
}Sub;

Sub new_sub(){
	Sub sub = {0};
	sub.horizontal = 0;
	sub.depth = 0;
	sub.aim = 0;
	sub.depth_direction = 0;
	return sub;
}

int main(){

	char line[BUFSIZ];
	Sub sub = new_sub();
	char* command = malloc(sizeof(char*));
	int value;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		sscanf(line, "%s %d", command, &value);
		if(strcmp(command, FORWARD) == 0){
			sub.horizontal += value;
			if(sub.aim != 0){
				sub.depth_direction += sub.aim * value;
			}
		}
		else if(strcmp(command, UP) == 0){
			sub.depth -= value;
			sub.aim -= value;
		}
		else if(strcmp(command, DOWN) == 0){
			sub.depth += value;
			sub.aim += value;
		}
	}

	printf("part1: %d\n", sub.depth * sub.horizontal);
	printf("part2: %d\n", sub.depth_direction * sub.horizontal);

	return 0;
}
