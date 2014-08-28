#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	pid = fork();


	if (pid == -1){
		printf("error\n");
		exit(0);
	} else if (pid == 0){
		while(1)
		{
			printf("son\n");
			sleep(5);
		}
	} else {
		while(1)
		{
			printf("father\n");
			sleep(5);
		}
	}




	return 0;
}
