#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void do_child_work(int pid)
{
	while(1)
	{
	alarm(1);
	if (kill(getppid(), SIGALRM) == 0)
		puts("Signal has been sent");
	else
		puts("There is an error sending the signal");
	}
	exit(0);
}

void do_parent_work(void)
{
	if(wait(0)<0)
		perror("wait");
}

int main(void)
{
	int pid = fork();
	if(pid < 0)
		perror("fork()");
	if(pid == 0)
		do_child_work(pid);
	do_parent_work();
	return 0;
}
