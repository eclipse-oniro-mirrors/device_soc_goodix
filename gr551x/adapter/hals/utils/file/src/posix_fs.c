#include "errno.h"
#include "fcntl.h"
#include "unistd.h"
#include "hal_file.h"

int open(const char *path, int oflag, ...)
{
    return HalFileOpen(path, oflag, 0);
}

int close(int fd)
{
    return HalFileClose(fd);
}

ssize_t read(int fd, void *buf, size_t nbyte)
{
    return HalFileRead(fd, buf, nbyte);
}

ssize_t write(int fd, const void *buf, size_t nbyte)
{
    return HalFileWrite(fd, buf, nbyte);
}

int unlink(const char *path)
{
    return HalFileDelete(path);
}

off_t lseek(int fd, off_t offset, int whence)
{
    return HalFileSeek(fd, offset, whence);
}

