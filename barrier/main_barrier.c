#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "tbarrier.h"


void *computethread(void *arg)
{
	if (waitbarrier())
		perror("errors in waitbarrier()\n");
	printf("helloWorld\n");
	return NULL;
}

int main(int argc, char *argv[])
{
	int numthreads;
	int error;
	int i;
	pthread_t *tids;

	if (argc != 2)
	{
		fprintf(stderr,"Usage: %s numthread\n",argv[0]);
		return 1;
	}

	numthreads = atoi(argv[1]);

        if (initbarrier(numthreads))	
		perror("Failed to init barrier\n");

	if ((tids = (pthread_t *)calloc(numthreads, sizeof(pthread_t))) == NULL)
	{
		perror("Failed to allocate space for thread IDs");
		return 1;
	}

	for (i = 0; i < numthreads; i++)
	{
		if (error = pthread_create(tids + i, NULL, computethread, NULL))
		{
			fprintf(stderr, "Failed to start thread %d:%s\n", i, strerror(error));
			return 1;
		}
	}

	for (i = 0; i < numthreads; i++)
	{
		if (error = pthread_join(tids[i], NULL))
		{
			fprintf(stderr, "Failed to join thread %d:%s\n", i, strerror(error));
			return 1;
		}
	}

	return 0;


}
