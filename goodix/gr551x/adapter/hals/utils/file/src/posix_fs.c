#include "errno.h"
#include "fcntl.h"
#include "unistd.h"
#include "hal_file.h"
#include "app_log.h"

int open(const char *path, int oflag, ...)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    return HalFileOpen(path, oflag, 0);
}

int close(int fd)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    return HalFileClose(fd);
}

ssize_t read(int fd, void *buf, size_t nbyte)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    return HalFileRead(fd, buf, nbyte);
}

ssize_t write(int fd, const void *buf, size_t nbyte)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    return HalFileWrite(fd, buf, nbyte);
}

int unlink(const char *path)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    return HalFileDelete(path);
}

off_t lseek(int fd, off_t offset, int whence)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    return HalFileSeek(fd, offset, whence);
}
