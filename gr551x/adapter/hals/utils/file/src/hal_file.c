/*
 * Copyright (c) 2021 GOODIX.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "hal_file.h"
#include "utils_file.h"
#include "log.h"

#define LOG_E(fmt, ...)  HILOG_ERROR(HILOG_MODULE_APP, fmt, ##__VA_ARGS__)
#define LOG_I(fmt, ...)  HILOG_INFO(HILOG_MODULE_APP, fmt, ##__VA_ARGS__)

int HalFileOpen(const char *path, int oflag, int mode)
{
    int fd = open(path, oflag);
    if (fd < 0) {
        LOG_E("fopen file '%s' failed, %s\r\n", path, strerror(errno));
        return -1;
    }

    return fd;
}

int HalFileClose(int fd)
{
    printf("close fd=%d\r\n",  fd);

    return close(fd);
}

int HalFileRead(int fd, char *buf, unsigned int len)
{
    return read(fd, buf, len);
}

int HalFileWrite(int fd, const char *buf, unsigned int len)
{
    return write(fd, buf, len);
}

int HalFileDelete(const char *path)
{
    return unlink(path);
}

int HalFileStat(const char *path, unsigned int *fileSize)
{
    struct stat f_info;

    int ret = stat(path, &f_info);
    *fileSize = f_info.st_size;
    return ((ret == 0) ? 0 : -1);
}

int HalFileSeek(int fd, int offset, unsigned int whence)
{
    return lseek(fd, offset, whence);
}
