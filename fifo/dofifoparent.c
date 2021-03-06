#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#define BUFSIZE 256 
#define FIFO_MODES O_RDONLY

ssize_t r_read(int fd, void *buf, size_t size);

int dofifoparent(const char *fifoname)
{
	char buf[BUFSIZE];
	int fd;
	int rval;

	fprintf(stderr, "[%ld]:(parent) about to open FIFO %s...\n", (long)getpid(), fifoname);
	while(((fd = open(fifoname, FIFO_MODES)) == -1) && (errno == EINTR));
	if (fd == -1)
	{
		fprintf(stderr, "[%ld]:failed to open named pipe %s for read: %s\n", (long)getpid(), fifoname, strerror(errno));
		return 1;
	}
	fprintf(stderr, "[%ld]:about to read...\n", (long)getpid());
	rval = r_read(fd, buf, BUFSIZE);
	if (rval == -1)
	{
		fprintf(stderr, "[%ld]:failed to read from pipe: %s\n", (long)getpid(), strerror(errno));
		return 1;
	}
	fprintf(stderr, "[%ld]:read %s\n", (long)getpid(), buf);
	return 0;
}

ssize_t r_read(int fd, void *buf, size_t size)
{
	ssize_t retval;
	while (retval = read(fd, buf, size), retval == -1 && errno == EINTR);
	return retval;
}
