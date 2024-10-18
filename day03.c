#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 1000


int main(){

	char line[BUFSIZ];
	char** diag = malloc(sizeof(char**) * LIMIT);
	int lines = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		diag[lines++] = strdup(line);
	}

	int ones = 0;
	int zeroes = 0;
	int length = strlen(diag[0]);
	int gamma = 0;
	int epsilon = 0;


	for(int i = 0; i < length; i++){
		for(int j = 0; j < lines; j++){
			if(diag[j][i] == '0'){
				zeroes++;
			} else {
				ones++;
			}
		}
		if(zeroes > ones){
			gamma <<= 1;
			epsilon = ~(~epsilon << 1); // left shift '1' (slower)
		} else {
			gamma = ~(~gamma << 1); // left shift '1' (slower)
			epsilon <<= 1;
		}
		zeroes = 0;
		ones = 0;
	}

	int o2_rating = 0;
	int co2_rating = 0;
	char** one_list = malloc(sizeof(char**) * LIMIT);
	int one_idx = 0;
	char** zero_list = malloc(sizeof(char**) * LIMIT);
	int zero_idx = 0;

	for(int i = 0; i < length; i++){
		for(int j = 0; j < lines; j++){
			if(diag[j][i] == '0'){
				zeroes++;
				zero_list[zero_idx++] = diag[j];
			} else {
				ones++;
				one_list[one_idx++] = diag[j];
			}
		}
		if(zeroes > ones){

		}
	}

	printf("part1: %d\n", gamma * epsilon);
	printf("part2: %d\n", 0);

	return 0;
}
