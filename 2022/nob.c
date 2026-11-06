#define NOB_IMPLEMENTATION
#include "nob.h"

#define CFLAGS "-Wall", "-Wextra", "-pedantic", "-O2"
#define CFLAGS_DEBUG "-Wall", "-Wextra", "-ggdb", "-pedantic"
#define CFLAGS_MATH "-lm"

int main(int argc, char **argv) {
	NOB_GO_REBUILD_URSELF(argc, argv);

	if (argc > 1 || argc < 5) { // ./nob day01 [d] [m]
		nob_shift_args(&argc, &argv);
		const char *program = nob_shift_args(&argc, &argv);
		Nob_Cmd cmd = {0};
		nob_cmd_append(&cmd, "cc");
		while (argc > 0) {
			const char *arg = nob_shift_args(&argc, &argv);
			if(strcmp(arg, "d") == 0){
				nob_cmd_append(&cmd, CFLAGS_DEBUG);
			}
			if(strcmp(arg, "m") == 0){
				nob_cmd_append(&cmd, CFLAGS_MATH);
				nob_cmd_append(&cmd, CFLAGS);
			} else {
				nob_cmd_append(&cmd, CFLAGS);
			}
			const char *filename = strcat(strdup(program), ".c");
			nob_cmd_append(&cmd, filename);
			if(!nob_cmd_run_sync(cmd)) return 1; //compile

			cmd.count = 0;

			nob_cmd_append(&cmd, "./a.out");
			if(!nob_cmd_run_sync(cmd)) return 1; //run
		}
	} else {
		nob_log(NOB_ERROR, "Missing arguments...");
	}
	return 0;
}
