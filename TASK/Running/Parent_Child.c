#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t id;
	//int status = 0;
	id = fork();
	if(id < 0)
		exit(-1);
		
	if(id == 0){				//child process
		printf("\nchild executing first its pid is (%d)\n", getpid());
		sleep(20);
		printf("child pid = (%d)\n", getpid());
		exit(2);
		
	}
	else{				//parent process
		sleep(15);
		printf("\n  have created a child process with ID = (%d)\n", id);
		printf("\nParent exited\n");
		//cpid = wait(NULL);
		// cpid = wait(&status);
/*		printf("\n Wait() in parent done \n Parent pid = %d\n", getpid());*/
/*		printf("\n status is (%d)\n", status);*/
	}
		return 0;
}
