
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