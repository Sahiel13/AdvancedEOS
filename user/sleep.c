#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
	int seconds;

	if (argc == 1){
		printf("Takes one more argument");
		exit();
	}	
	if (argc > 2){
		printf("Exceeds the number of arguments");
		exit();
	}

	seconds = atoi(argv[1]);
	if (seconds > 0){
		sleep(seconds);
	} else {
		printf("Enter valid number of seconds \n");
	}
	exit();
}
