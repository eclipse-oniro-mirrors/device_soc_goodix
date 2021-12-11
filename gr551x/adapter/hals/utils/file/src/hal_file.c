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

#define MaxOpenFile  32
#define ROOT_PATH    "/data"

typedef struct _File_Context {
    int fs_fd;
    unsigned char fd;
} File_Context;

static File_Context File[MaxOpenFile] = { 0 };

int Find_Free_Num(void)
{
    int i = MaxOpenFile;
    for (; i > 0; i--) {
        if (File[i - 1].fd == 0) {
            break;
        }
    }

    return i;
}

int HalFileOpen(const char *path, int oflag, int mode)
{
    char *file_path;
    int fd;

	if (strlen(path) >= 40) {
		LOG_E("path name is too long!!!\n");
		return -1;
	}

    fd = Find_Free_Num();
    if (fd == 0) {
        LOG_E("NO enougn file Space!!!\n");
        return -1;
    }

    file_path = (char *)malloc(strlen(path) + strlen(ROOT_PATH) + 2);
    if (file_path == NULL) {
        LOG_E("malloc path name buffer failed!\n");
        return -1;
    }
    strcpy(file_path, ROOT_PATH);
    strcat(file_path, "/");
    strcat(file_path, path);

    int fs_fd = open(file_path, oflag);
    if (fs_fd < 0) {
        LOG_E("open file '%s' failed, %s\r\n", file_path, strerror(errno));
        free(file_path);
        return -1;
    }

    File[fd - 1].fd = 1;
    File[fd - 1].fs_fd = fs_fd;
    free(file_path);

    return fd;
}

int HalFileClose(int fd)
{
    int ret;

    if ((fd > MaxOpenFile) || (fd <= 0)) {
        return -1;
    }

    ret = close(File[fd - 1].fs_fd);
    if (ret != 0) {
        return -1;
    }

    File[fd - 1].fd = 0;
    File[fd - 1].fs_fd = -1;

    return ret;
}

int HalFileRead(int fd, char *buf, unsigned int len)
{
    if ((fd > MaxOpenFile) || (fd <= 0)) {
        return -1;
    }

    return read(File[fd - 1].fs_fd, buf, len);
}

int HalFileWrite(int fd, const char *buf, unsigned int len)
{
    if ((fd > MaxOpenFile) || (fd <= 0)) {
        return -1;
    }

    return write(File[fd - 1].fs_fd, buf, len);
}

int HalFileDelete(const char *path)
{ 
    char *file_path;

	if (strlen(path) >= 40) {
		LOG_E("path name is too long!!!\n");
		return -1;
	}

    file_path = (char *)malloc(strlen(path) + strlen(ROOT_PATH) + 2);
    if (file_path == NULL) {
        LOG_E("malloc path name buffer failed!\n");
        return -1;
    }
    strcpy(file_path, ROOT_PATH);
    strcat(file_path, "/");
    strcat(file_path, path);

    int ret = unlink(file_path);
    free(file_path);

    return ret;
}

int HalFileStat(const char *path, unsigned int *fileSize)
{
    char *file_path;
    struct stat f_info;

	if (strlen(path) >= 40) {
		LOG_E("path name is too long!!!\n");
		return -1;
	}

    file_path = (char *)malloc(strlen(path) + strlen(ROOT_PATH) + 2);
    if (file_path == NULL) {
        LOG_E("malloc path name buffer failed!\n");
        return -1;
    }
    strcpy(file_path, ROOT_PATH);
    strcat(file_path, "/");
    strcat(file_path, path);

    int ret = stat(file_path, &f_info);
    *fileSize = f_info.st_size;
    free(file_path);

    return ((ret == 0) ? 0 : -1);
}

int HalFileSeek(int fd, int offset, unsigned int whence)
{
    int ret = 0;
    struct stat f_info;

    if ((fd > MaxOpenFile) || (fd <= 0)) {
        return -1;
    }

    ret = fstat(File[fd - 1].fs_fd, &f_info);
    if (ret != 0) {
        return -1;
    }

    if (whence == SEEK_SET_FS) {
        if (offset > f_info.st_size) {
            ret = -1;
        }
    }

    ret = lseek(File[fd - 1].fs_fd, offset, whence);
    if ((ret >  f_info.st_size) || (ret < 0)){
        return -1;
    }

    return ret;
}
