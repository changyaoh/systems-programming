#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "doneflag.h"
#include "globalerror.h"
#include "randsafe.h"
#include "sharedsum.h"

#define TEN_MILLION 10000000L

void *computethread(void *arg1)
{
	int error;
	int localdone = 0;
	struct timespec sleeptime;
	double val;

	sleeptime.tv_sec = 0;
	sleeptime.tv_nsec = TEN_MILLION;

	while(!localdone)
	{
		if (error = randsafe(&val))
			break;
		if (error = add( sin(val) ))
			break;
		if (error = getdone(&localdone))
			break;
		nanosleep(&sleeptime, NULL);
	}

	seterror(error);
	return NULL;

}
