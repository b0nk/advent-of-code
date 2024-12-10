#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define LIMIT 1000
#define PATTERN "(mul\\(([0-9]+),([0-9]+)\\)|don't\\(\\)|do\\(\\))"


int main(void){

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;

	regex_t mul_regex;
	int mul_pat_error;
	mul_pat_error = regcomp(&mul_regex, PATTERN, REG_EXTENDED);
	if(mul_pat_error != 0){
		return mul_pat_error;
	}
	int mul_nmatch = 4;
	regmatch_t mul_match[mul_nmatch];

	int mul_enabled = 1;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		int end_index = 0;
		while(regexec(&mul_regex, &line[end_index], mul_nmatch, mul_match, 0) == 0){
			int i = 0;
			for(; i < mul_nmatch && mul_match[i].rm_so != -1; i++){
				char str[BUFSIZ] = {0};
				strncpy(str, line + end_index + mul_match[i].rm_so, mul_match[i].rm_eo - mul_match[i].rm_so);
				if((strncmp(str, "mul", 3) == 0)) {
					int x;
					int y;
					sscanf(str, "mul(%d,%d)", &x, &y);
					part1 += x * y;
					if(mul_enabled){
						part2 += x * y;
					}
					i += 3;
				} else if (strncmp(str, "do(", 3) == 0) {
					mul_enabled = 1;
					i += 1;
				} else if (strncmp(str, "don", 3) == 0) {
					mul_enabled = 0;
					i += 1;
				}
			}
			end_index += mul_match[i - 1].rm_eo;
		}
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
