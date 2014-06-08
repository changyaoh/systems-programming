#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "tbarriers.h"

void *computethread(void *arg)
{
	if (waitbarriers((int)arg))
		perror("errors in waitbarriers\n");

	printf("helloworld\n"); /* do works*/

	pthread_exit((void *)arg);
}


int main(int argc, char *argv[])
{
	int numthreads;
	int barrier;
	int status;
	int error;
	int i;
	pthread_t *tids;

	if (argc != 2)
	{
		fprintf(stderr,"Usage: %s numthread \n",argv[0]);
		return 1;
	}

	numthreads = atoi(argv[1]);


	if ((barrier = initbarriers(numthreads)) < 0)
		perror("Failed to init barrier");


	if ((tids = (pthread_t *)calloc(numthreads, sizeof(pthread_t))) == NULL)
	{
		perror("Failed to allocate space for thread IDs\n");
		return 1;
	}

	for (i = 0; i < numthreads; i++)
	{
		if (error = pthread_create(tids + i, NULL, computethread, (void *)barrier ))
		{
			fprintf(stderr, "Failed to start thread %d:%s\n", i, strerror(error));
			return 1;
		}
	}

	for (i = 0; i < numthreads; i++)
	{
		if (error = pthread_join(tids[i], (void **)&status))
		{
			fprintf(stderr, "Failed to join thread %d:%s\n", i, strerror(error));
			return 1;
		}

		printf ("Thread %d status:%d\n",i,status);
	}

	return 0;

}


