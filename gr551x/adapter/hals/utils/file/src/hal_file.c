#include "hal_file.h"
#include "utils_file.h"
#include "app_lfs.h"
#include "string.h"
#include "stdio.h"
#include <cmsis_os2.h>
#include "app_log.h"

#define MaxOpenFile  32
#define FR_OK        0

typedef struct _File_Context {
    app_lfs_file_id_t file;
    unsigned char fd;
} File_Context;

static File_Context File[MaxOpenFile] = { 0 };
static osMutexId_t fs_mutex;

static int fs_lock(void)
{
    int ret = 0;

    ret = osMutexAcquire(fs_mutex, osWaitForever);
    if (ret != osOK) {
         APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>[LFS] lock failed!");
    }
    return ret;
}

static void fs_unlock(void)
{
    osMutexRelease(fs_mutex);
}

void FileSystemInit(void)
{
    int ret = 0;
    fs_mutex = osMutexNew(NULL);
    if (fs_mutex == NULL) {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>[LFS] File system mutex init failed!");
    }

    //app_lfs_format();
    ret = app_lfs_init(); {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>[LFS] File system init failed! ret=%d", ret);
    }
}

int ReadModeChange(int oflag)
{
    int ret = 0, buffer = 0;

    buffer = (oflag & 0x000f);
    if (buffer == O_RDONLY_FS) {
        ret = LFS_O_RDONLY;
    } else if (buffer == O_WRONLY_FS) {
        ret = LFS_O_WRONLY;
    } else if (buffer == O_RDWR_FS) {
        ret = LFS_O_RDWR;
    }

    buffer = (oflag & 0x00f0);
    if ((buffer & 0x0040) != 0) {
        ret |= LFS_O_CREAT;
    }

    if ((buffer & 0x0080) != 0) {
        ret |= LFS_O_EXCL;
    }

    buffer = (oflag & 0x0f00);
    if ((buffer & 0x0200) != 0) {
        ret |= LFS_O_TRUNC;
    }

    if ((buffer & 0x0400) != 0) {
        ret |= LFS_O_APPEND;
    }

    return ret;
}

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

static char *get_file_name(const char *path)
{
    char *colon;   
    char *tmp = (char *)path;

    colon = strchr(path, '/');
    if (colon != NULL) {
        while(1) {
            tmp = colon;
            colon = strchr(colon, '/');
            if (colon != NULL) {
                colon +=1;
                continue;
            } else {
                break;
            }
        }  
    }

    return tmp;
}

int HalFileOpen(const char *path, int oflag, int mode)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s---%s Entry!!! ", __FUNCTION__, path);
    int ret = 0;
    int fd  = 0;
    char *file_name;

    if (strlen(path) >= 40) {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>path name is too long!!!");
        return -1;
    }

    file_name = get_file_name(path);
    if (file_name == NULL) {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>[LFS] File name is NULL");
        return -1;
    }

    fs_lock();
    fd = Find_Free_Num();
    if (fd == 0) {
        APP_LOG_ERROR("NO enougn file Space!");
        fs_unlock();
        return -1;
    }

    // printf("Open file=%s", file_name);
    ret = app_lfs_file_open(&File[fd - 1].file, file_name, ReadModeChange(oflag));
    if (ret != FR_OK) {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>[LFS] File open failed! ret=%d", ret);
        fs_unlock();
        return -1;
    }

    File[fd - 1].fd = 1;
    fs_unlock();

    return fd;
}

int HalFileClose(int fd)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    if ((fd > MaxOpenFile) || (fd <= 0)) {
        return -1;
    }

    fs_lock();
    if (app_lfs_file_close(&File[fd - 1].file) != FR_OK) {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>[LFS] File close failed %d", fd);
        fs_unlock();
        return -1;
    }

    File[fd - 1].fd = 0;
    fs_unlock();

    return 0;
}

int HalFileRead(int fd, char *buf, unsigned int len)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    int ret = 0;

    if ((fd > MaxOpenFile) || (fd <= 0)) {
        return -1;
    }

    fs_lock();
    ret = app_lfs_file_read(&File[fd - 1].file, (uint8_t *)buf, len);
    fs_unlock();

    return ret;
}

int HalFileWrite(int fd, const char *buf, unsigned int len)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    int ret = 0;

    if ((fd > MaxOpenFile) || (fd <= 0)) {
        return -1;
    }

    fs_lock();
    ret = app_lfs_file_write(&File[fd - 1].file, (uint8_t *)buf, len);
    fs_unlock();

    return ret;
}

int HalFileDelete(const char *path)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    int ret = -1;
    char *file_name;

    if (strlen(path) >= APP_LFS_PATH_MAX) {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>path name is too long!!!");
        return -1;
    }

    file_name = get_file_name(path);
    if (file_name == NULL) {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>[LFS] File name is NULL");
        return -1;
    }

    fs_lock();
    ret = app_lfs_file_remove(file_name);
    fs_unlock();

    return ((ret == 0) ? 0 : -1);
}

int HalFileStat(const char *path, unsigned int *fileSize)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    int ret = -1;
    app_lfs_info_t info;
    char *file_name;

    if (strlen(path) >= APP_LFS_PATH_MAX) {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>path name is too long!!!");
        return -1;
    }

    file_name = get_file_name(path);
    if (file_name == NULL) {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>[LFS] File name is NULL");
        return -1;
    }

    fs_lock();
    ret = app_lfs_file_stat(file_name, &info);
    fs_unlock();

    *fileSize = info.size;

    return ((ret == 0) ? 0 : -1);
}

int HalFileSeek(int fd, int offset, unsigned int whence)
{
    APP_LOG_DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>%s--- Entry!!! ", __FUNCTION__);
    int ret = 0;
    unsigned int flags = 0;
    uint32_t file_size = 0;
    int cur_offs = 0;

    if ((fd > MaxOpenFile) || (fd <= 0)) {
        return -1;
    }

    fs_lock();
    file_size = app_lfs_file_size(&File[fd - 1].file);
    cur_offs  = app_lfs_file_tell(&File[fd - 1].file);

    if (whence == SEEK_SET_FS) {
        if (offset > file_size) {
            ret = -1;
            goto exit;
        }
        flags = LFS_SEEK_SET;
    } else if (whence == SEEK_CUR_FS) {
        int pos = cur_offs + offset;
        if (pos > file_size) {
            ret = -1;
            goto exit;
        }
        flags = LFS_SEEK_CUR;
    } else if (whence == SEEK_END_FS) {
        flags = LFS_SEEK_END;
    } else {
        APP_LOG_ERROR(">>>>>>>>>>>>>>>>>>>>>>>>>>unknown whence: %u", whence);
        ret =  -1;
        goto exit;
    }

    if (app_lfs_file_seek(&File[fd - 1].file, offset, flags) < 0) {
        ret = -1;
    }

exit:
    fs_unlock();
    return ret;
}

