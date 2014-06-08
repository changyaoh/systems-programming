#include <unistd.h>
#include <errno.h>

ssize_t saferead(int fd, void *buf, size_t count)
{
	size_t nread = 0;
	while (count > 0)
	{
		ssize_t r = read(fd, buf, count);
		if (r < 0 && errno == EINTR)
			continue;
		if (r < 0)
			return r;
		if (r == 0)
			return nread;
		buf = (char *)buf + r;
		count -= r;
		nread += r;
	}
	return nread;
}

ssize_t safewrite(int fd, void *buf, size_t count)
{
	size_t nwritten = 0;
	while (count > 0)
	{
		ssize_t r = write(fd, buf, count);
		if (r < 0 && errno == EINTR)
			continue;
		if (r < 0)
			return r;
		if (r == 0)
			return nwritten;
		buf = (char *)buf + r;
		count -= r;
		nwritten += r;
	}
	return nwritten;
}
