#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int fdAB[2];
int fdBA[2];

#define READAB fdAB[0]
#define WRITEAB fdAB[1]
#define READBA fdBA[0]
#define WRITEBA fdBA[1]

int main(int argc, char** argv) {
	
	if(pipe(fdAB) < 0){
		perror("piping failed");
		exit(1);
	}
	if(pipe(fdBA) < 0){
		perror("piping failed");
		exit(1);
	}
	
	pid_t pid = fork();
	
	if(pid<0){
		perror("fork failed");
		exit(1);
	}
	
	if(pid == 0){ //child 
		close(WRITEAB);	
		close(READBA);	
		
		dup2(READAB, STDIN_FILENO);
		close(READAB);
		
		dup2(WRITEBA, STDOUT_FILENO);
		close(WRITEBA);
			
		char *args[] = {"./prog", NULL};
		execvp("./prog",args);
		
		return 0;
	}else{
		close(READAB);
		close(WRITEBA);
		
		dup2(WRITEAB, STDOUT_FILENO);
		close(WRITEAB);
		
		dup2(READBA, STDIN_FILENO);
		close(READBA);
		
		printf("stdio_pipe --> prog\n");
		fflush(stdout);
		
		char buf[100];
		read(STDIN_FILENO, buf, 100);
		
		fprintf(stderr, "msg (stdio_pipe): %s", buf);
		
		wait(NULL);
	}
	
	return 0;
}
