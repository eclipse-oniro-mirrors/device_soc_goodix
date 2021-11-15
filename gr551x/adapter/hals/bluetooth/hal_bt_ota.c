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

#include <stdint.h>
#include <stdbool.h>

int HilinkGetRebootFlag(void)
{
    return 1;
}

int HilinkNotifyOtaData(const unsigned char *data, unsigned int len, unsigned int offset)
{
    return 0;
}

int HilinkOtaStartProcess(int type)
{
    return 0;
}
int HilinkOtaEndProcess(int status)
{
    return 0;
}

void HILINK_OtaAdapterRestart(int flag)
{
    return;
}
int HilinkNotifyOtaStatus(int flag, unsigned int len, unsigned int type)
{
    return 0;
}

unsigned int HILINK_OtaAdapterFlashMaxSize(void)
{
    return 0;
}
bool HILINK_OtaAdapterFlashFinish(void)
{
    return true;
}

int HILINK_OtaAdapterFlashRead(unsigned int offset, unsigned char *buf, unsigned int buflen)
{
    return 0;
}

int HILINK_OtaAdapterFlashWrite(const unsigned char *buf, unsigned int buflen)
{
    return 0;
}

int HILINK_OtaAdapterFlashErase(unsigned int size)
{
    return 0;
}
unsigned int HILINK_OtaAdapterGetUpdateIndex(void)
{
    return 0;
}
bool HILINK_OtaAdapterFlashInit(void)
{
    return true;
}

int getDeviceVersion(char **firmwareVer, unsigned int inlen, unsigned int *outlen)
{
    return 0;
}

int HilinkGetMcuVersion(char *version,unsigned int inlen, unsigned int *outlen)
{
    return 0;
}