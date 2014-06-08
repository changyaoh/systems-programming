#include <unistd.h>
#include <stdio.h>
#include <error.h>
#include "read_write.h"

int main(int argc, char *argv[])
{
	int pfd[2];
	int i,j;
	int n;
	char a = '1',b;
	pid_t childpid;

	if (argc != 2)
	{
		fprintf(stderr,"Usage: %s num\n",argv[0]);
		return 1;
	}

	n = atoi(argv[1]);

	if (pipe(pfd) == -1)
	{
		perror("Faile to init pipe\n");
		return -1;
	}

	for (j = 0; j < n; j++)
	{
	        childpid = fork();
                if (childpid == -1)
                {
		        perror("Fail to fork()");
		        return -1;
	        }

	        if (childpid == 0)
	        {

		        if (close(pfd[1]) == -1)
			        return -1;

			if (saferead(pfd[0], &b, sizeof(b)) != 1)
				perror("Child fail to read synchronization charater");
		        printf("World\n");

		        return 0;

	        }
		else
			continue;
         }

	if (close(pfd[0]) == -1)
		return -1;

        printf("Hello\n");

	for (i = 0; i < n; i++)
		if (safewrite(pfd[1], &a, 1) != 1)
			{

				perror("Parent fail to write synchronization charater");
				return 1;

			}

	return 0;

}







