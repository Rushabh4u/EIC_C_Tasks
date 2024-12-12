#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

//extern char **environ;
static int gdata = 111;
int main(int argc, char *argv[]){
	//char **ep;
	//for(ep = environ; *ep != NULL; ep++)
		//printf("\n (%s)", *ep);
	//return 0;

/*	pid_t id;*/
/*	printf("Parent Process : Executed by parent process before fork() PID = (%d)\n", getpid());*/
/*	id = fork();*/

/*	printf("\nParent Process: I've createdd child process with ID = (%d)\n", id);*/
/*	return 0;*/

	int istack = 222;
	pid_t childPid;
	
	switch(childPid = fork()){
		case -1:
			printf("\n I am parent\n");
			exit(-1);
		case 0:
			printf("\n i am child\n");
			gdata *= 3;
			istack *= 3;
			printf("")
	}
}
