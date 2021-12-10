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
#include "littlefs.h"
#include "gr55xx_hal.h"
#include "hal_flash.h"
#include "hdf_log.h"

static uint32_t g_lfs_start_addr;

int32_t littlefs_flash_init(const struct lfs_config *cfg)
{
    uint32_t flash_id;
    uint32_t flash_size;
    uint32_t nvds_start_addr;

    hal_flash_get_info(&flash_id, &flash_size);

    nvds_start_addr = EXFLASH_START_ADDR + flash_size - hal_flash_sector_size() * NVDS_NUM_SECTOR;
    g_lfs_start_addr  = nvds_start_addr - cfg->block_count * cfg->block_size;

    HDF_LOGI("littlefs flash start addr=0x%x, all size=%dKB", g_lfs_start_addr, cfg->block_count * cfg->block_size / 1024);

    return 0;
}

int32_t littlefs_block_read(const struct lfs_config *c, lfs_block_t block,
                            lfs_off_t off, void *buf, lfs_size_t size)
{
    uint32_t addr = g_lfs_start_addr + c->block_size * block + off;

    return size == hal_flash_read(addr, (uint8_t*)buf, size) ? LFS_ERR_OK : LFS_ERR_IO;
}

int32_t littlefs_block_write(const struct lfs_config *c, lfs_block_t block,
                             lfs_off_t off, const void *dst, lfs_size_t size)
{
    uint32_t addr = g_lfs_start_addr + c->block_size * block + off;

    return size == hal_flash_write(addr, (uint8_t*)dst, size) ? LFS_ERR_OK : LFS_ERR_IO;
}

int32_t littlefs_block_erase(const struct lfs_config *c, lfs_block_t block)
{
    uint32_t addr = g_lfs_start_addr + block * c->block_size;

    return hal_flash_erase (addr, c->block_size) ? LFS_ERR_OK : LFS_ERR_IO;
}

int32_t littlefs_block_sync(const struct lfs_config *c)
{
    return 0;
}
