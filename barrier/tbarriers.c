#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_BARRIER 5

static pthread_cond_t bcond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
static int count = 0;
static int barrier = 0;
static int limit[NUM_BARRIER];

int initbarriers(int n)
{
	int error;
	int i;

	if (error = pthread_mutex_lock(&bmutex))
	{
		printf("Can't lock\n");
		return -1;
	}
	if (barrier > NUM_BARRIER)
	{
		pthread_mutex_unlock(&bmutex);
		return EINVAL;
	}
	        limit[barrier] = n;
		barrier++;

	if (error =  pthread_mutex_unlock(&bmutex))
        {
		printf("Can't unlock\n");
		return -1;
	}

	return barrier - 1;
		
}


int waitbarriers(int barrier)
{
	int berror = 0;
	int error;

	if (error = pthread_mutex_lock(&bmutex))
		return error;
	if (limit[barrier] <= 0)
	{
		pthread_mutex_unlock(&bmutex);
		return EINVAL;
	}
	count++;
	while ((count < limit[barrier]) && !berror)
		berror = pthread_cond_wait(&bcond, &bmutex);
	if (!berror)
		berror = pthread_cond_broadcast(&bcond);
	error = pthread_mutex_unlock(&bmutex);
	if (berror)
		return berror;
	return error;
		
}
