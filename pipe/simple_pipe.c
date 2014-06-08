#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 10

int main(int argc, char *argv[])
{
	int pfd[2];
	pid_t childpid;
	char buf[BUF_SIZE];
	ssize_t numRead;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s message\n",argv[0]);
		return 1;
	}

	if (pipe(pfd) == -1)
	{
		perror("Faile to setup pipe ");
		return 1;
	}

	childpid = fork();
	if (childpid == -1)
	{
		perror("Failed to fork\n");
		return 1;
	}

	if (childpid == 0)
	{
		if (close(pfd[1]) == -1)
		{
			perror("Child:Failed to close\n");
			return 1;
		}

		for (;;)
		{
			numRead = read(pfd[0], buf, BUF_SIZE);
			if (numRead == -1)
				return -1;
			if (numRead == 0)
				break;
			if (write(STDOUT_FILENO, buf, numRead) != numRead)
			{
				perror("Faile to write to STDOUT");
				return 1;
			}

		}

		write(STDOUT_FILENO, "\n", 1);
		if (close(pfd[0]) == -1)
		{
			perror("Faile to read");
			return 1;
		}

		return 0;

	}
	else
	{
                if (close(pfd[0]) == -1)
		{
			perror("Child:Failed to close\n");
			return 1;
		}

		if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
		{
			perror("Failed to wirte to pipe");
			return 1;
		}

                if (close(pfd[1]) == -1)
		{
			perror("Faile to close");
			return 1;
		}

		wait(NULL);

		return 0;
	}
}
