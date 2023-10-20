#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	char buf[100];
	read(STDIN_FILENO, buf, 100);
	
	fprintf(stderr, "msg (prog): %s", buf);
	
	printf("prog --> stdio_pipe\n");
	
	return 0;
}
