#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#define BUFSIZE 256

ssize_t r_write(int fd, void *buf, size_t size);

int dofifochild(const char *fifoname, const char *idstring)
{
	char buf[BUFSIZE];
	int fd;
	int rval;
	ssize_t strsize;

	fprintf(stderr, "[%ld]: (child) about to open FIFO %s... \n", (long)getpid(), fifoname);
	while(((fd = open(fifoname, O_WRONLY)) == -1) && (errno == EINTR));
	if (fd == -1)
	{
		fprintf(stderr, "[%ld]:failed to open named pipe %s for write: %s\n",(long)getpid(), fifoname, strerror(errno));
		return 1;
	}
	rval = snprintf(buf, BUFSIZE, "[%ld]:%s\n", (long)getpid(), idstring);
	if (rval < 0)
	{
		fprintf(stderr, "[%ld]:failed to make the string:\n", (long)getpid());
		return 1;
	}
	strsize = strlen(buf) + 1;
	fprintf(stderr, "[%ld]:about to write...\n", (long)getpid());
	rval = r_write(fd, buf, strsize);
	if (rval != strsize)
	{
		fprintf(stderr, "[%ld]:failed to write to pipe: %s\n", (long)getpid(), strerror(errno));
		return 1;
	}
	fprintf(stderr, "[%ld]:finishing: %s", (long)getpid(), buf);
	return 0;

}


ssize_t r_write(int fd, void *buf, size_t size)
{
	char *bufp;
	size_t bytestowrite;
	ssize_t byteswritten;
	size_t totalbytes;

	for (bufp = buf, bytestowrite = size, totalbytes = 0; bytestowrite > 0; bufp += byteswritten, bytestowrite -= byteswritten) 
	{
		byteswritten = write(fd,bufp, bytestowrite);
		if ((byteswritten == -1) && (errno != EINTR))
			return -1;
		if (byteswritten == -1)
			byteswritten = 0;
		totalbytes += byteswritten;
	}
	return totalbytes;
}
