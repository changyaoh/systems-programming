#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_BARRIER 5

static pthread_cond_t bcond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
static int count = 0;
static int barrier = 0;
typedef struct barrier *barrier_pointer;
struct barrier
{
	int num;
	barrier_pointer link;
};
static barrier_pointer front = NULL;
static barrier_pointer tail = NULL;

int initbarriers(int n)
{
	int error;
	int i;
	barrier_pointer temp;

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

	temp = (barrier_pointer)malloc(sizeof(struct barrier));
	if (!temp)
		return -1;
	temp->num = n;
	temp->link = NULL;

	if (front)
		tail->link = temp
        else
		front = temp;
	tail = temp;

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
	int limits;
        barrier_pointer temp;
	int i;

	if (error = pthread_mutex_lock(&bmutex))
		return error;

	if (front == NULL)
	{
		pthread_mutex_unlock(&bmutex);
		return EINVAL;
	}
	else
	{
                temp = front;	
		for(i = 0; i < barrier; i++)
		{
			limits = temp->num;
			temp = temp->link;
		}

	}
	count++;
	while ((count < limits) && !berror)
		berror = pthread_cond_wait(&bcond, &bmutex);
	if (!berror)
		berror = pthread_cond_broadcast(&bcond);
	error = pthread_mutex_unlock(&bmutex);
	if (berror)
		return berror;
	return error;
		
}
