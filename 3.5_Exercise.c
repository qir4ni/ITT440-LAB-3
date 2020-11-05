#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//Function for sigint_handler()
void sigint_handler(int sig)
{
	printf("Ctrl + C dilarang!\n");
}

//Dapat input nombor
int getNumber() {
	int number;

	//prompt number
	printf("Masukkan nombor : ");

	//reads and stores number input
	scanf("%d", &number);

	return number;
}

//Periksa nombor itu prime atau tidak
int checkPrime(int number) {
	int n, i, flag = 0, status = 0;
	n = number;

	for (i = 2; i <= n / 2; ++i)	{
		//condition for non-prime
		if(n % i ==0) {
		  flag = 1;
		  //printf("Flag = 1\n");
		  break;
		}
	}

	if(n == 1) {
		status = 0;
	}
	else {
		if(flag == 0)
		  status = 1;
		else
		  status = 2;
	}

	return status;
}


int main(void)	{

	printf("\n-=[ Pemeriksa Nombor Perdana(Prime) ]=-\n");

	int fd[2];
	pipe(fd);
	pid_t pid = fork();


	//Signal
	void sigint_handler(int sig);

	//Detect SIGINT signal
	if(signal(SIGINT, sigint_handler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	//what PID
	//printf("PID is %d\n", pid);

	//if parent
	if(pid > 0) {

	  //tutup write
	  close(fd[1]);

	  int secretNumber;
	  read(fd[0], &secretNumber, sizeof(secretNumber));
	  //printf("Ini bapaknya\n");
	  close(fd[0]);

	  printf("Memproses nombornya..\n");
	  wait(NULL);
	  int status = checkPrime(secretNumber);
	  //printf("Status is %d\n", status);
	  if(status == 0)
		printf("Nombor yang dimasukkan bukan nombor perdana(prime) atau composite\n\n");
	  else if(status == 1)
		printf("%d ialah nombor perdana.\n\n", secretNumber);
	  else if(status == 2)
		printf("%d bukan nombor perdana.\n\n", secretNumber);

	}

	//if child
	if(pid == 0) {

	  //tutup read
	  close(fd[0]);

	  //printf("Ini anak\n");
	  int number = getNumber();
	  write(fd[1], &number, sizeof(number));
	  close(fd[1]);

	 // printf("Ini anak\n");
	  exit(EXIT_SUCCESS);
	}

	return EXIT_SUCCESS;
}
