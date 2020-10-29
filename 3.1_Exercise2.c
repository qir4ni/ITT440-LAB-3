#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <signal.h>


int main(void)
{

	//void sigint_handler(int sig);
	//void sigtstp_handler(int sig);
	//void sigquit_handler(int sig);
	void sig_handler(int sig);

	char s[200];

	//if(signal(SIGINT, sigint_handler) == SIG_ERR)	{
	//	perror("signal");
	//	exit(1);
	//}

	if(signal(SIGINT, sig_handler) == SIG_ERR)	{
		perror("signal");
		exit(1);
	}
	else if(signal(SIGTSTP, sig_handler) == SIG_ERR)	{
		perror("signal");
		exit(1);
	}
	else if(signal(SIGQUIT, sig_handler) == SIG_ERR)	{
		perror("signal");
		exit(1);
	}

	printf("Enter a string:\n");

	if(fgets(s, 200, stdin) == NULL)
		perror("gets");
	else
		printf("you entered: %s\n", s);

	return 0;

}

/*void sigint_handler(int sig)
{
	printf("Jangan Kacau saya!\n");
}*/

void sig_handler(int sig)
{
	if(sig == 2)
		printf("This is a special signal handler for SIGINT\n");
	else if(sig == 20)
		printf("This is a special signal handler for SIGTSTP\n");
	else if(sig == 3)
		printf("This is a special signal handler for SIGQUIT\n");
	
	//printf("Jangan Kacau saya!%d\n", sig);

}
