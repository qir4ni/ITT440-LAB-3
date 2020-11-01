#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//Function for sigint_handler()
void sigint_handler(int sig)
{
	printf("Jangan Kacau saya!\n");
}

int getNumber() {
	int number;

	//prompt number
	printf("Enter a number: ");

	//reads and stores number input
	scanf("%d", &number);

	return number;
}

int checkPrime(int number) {
	int n, i, flag = 0, status = 0;
	n = number;

	for (i = 2; i <= n / 2; ++i)	{
		//condition for non-prime
		if(n % i ==0) {
		  flag = 1;
		  printf("Flag = 1\n");
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

/*int getPIN()	{
	// use PPID and PID as the seed
	srand(getpid() + getppid());
	int secret = 1000 + rand() % 9000;
	return secret;
}*/

int main(void)	{
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
	printf("PID is %d\n", pid);

	//if child
	/*if(pid == 0) {
	  close(1);
	  close(fd[0]);
	  dup(fd[1]);

	  printf("Ini anak\n");
	  int number = getNumber();
	  write(fd[1], &number, sizeof(number));
	  exit(EXIT_SUCCESS);
	}*/

	//if parent
	if(pid > 0) {
	  close(0);
	  close(fd[1]);
	  dup(fd[0]);

	  int secretNumber;
	 // long int readyBytes = read(fd[0], &secretNumber, sizeof(secretNumber));

	  printf("Ini bapaknya\n");

	  printf("Waiting for PIN..\n");
	  wait(NULL);
	  //printf("Bytes read: %ld\n", readyBytes);
	  printf("PIN: %d\n", secretNumber);
	  int status = checkPrime(secretNumber);
	  printf("Status is %d\n", status);
	  if(status == 0)
		printf("Number entered is neither prime nor composite\n");
	  else if(status == 1)
		printf("%d is a prime number.\n", secretNumber);
	  else if(status == 2)
		printf("%d is not a prime number.\n", secretNumber);

	}
	//if child
	if(pid == 0) {
	  printf("Ini anak\n");
	  int number = getNumber();
	  write(fd[1], &number, sizeof(number));

	  close(1);
	  close(fd[0]);
	  dup(fd[1]);

	 // printf("Ini anak\n");
	 // int number = getNumber();
	 // write(fd[1], &number, sizeof(number));
	  exit(EXIT_SUCCESS);
	}

	return EXIT_SUCCESS;
}
