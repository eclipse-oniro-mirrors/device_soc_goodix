/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: ����SDK APIͷ�ļ�
 */
#ifndef HILINK_BT_API_H
#define HILINK_BT_API_H

#include "ble_cfg_net_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ��������Э��ջ��־ */
#define BLE_DEINIT_FALG 0x1234ABCD

/* ��Ʒ��Ϣ����ṹ�� */
typedef struct {
    char *manuName;       /* �豸�����̣����ȷ�Χ��0,4] */
    char *devName;        /* �豸���� */
    char *productId;      /* �豸HiLink��֤�ţ����ȷ�Χ��0,5] */
    char *sn;             /* �豸Ψһ��ʶ������sn�ţ����ȷ�Χ��0,40] */
    char *mac;            /* �豸MAC��ַ���̶�32�ֽ� */
    char *subProductId;   /* �豸��productId */
    char *model;          /* �豸�ͺţ����ȷ�Χ��0,32] */
    char *devType;        /* �豸���ͣ����ȷ�Χ��0,4] */
    char *hiv;            /* �豸HilinkЭ��汾�����ȷ�Χ��0,32] */
    int protType;         /* �豸Э�����ͣ�ȡֵ��Χ[1,3] */
} HILINK_BT_DevInfo;

/* �����������ݻص��������� */
typedef int (*HILINK_BT_SendBtDataCallback)(const unsigned char *buf, unsigned int len);

/* ����ʵ��Э��ջʹ�ã�ע���������ݷ��ͽӿ� */
int HILINK_BT_RegisterBtDataSendCallback(HILINK_BT_SendBtDataCallback callback);

/* ����ʵ��Э��ջʹ�ã�ע������OTA���ݷ��ͽӿ� */
int HILINK_BT_RegisterOtaDataSendCallback(HILINK_BT_SendBtDataCallback callback);

/* ����ʵ��Э��ջʹ�ã������������� */
int HILINK_BT_ProcessBtData(const unsigned char *buf, unsigned int len);

/* ����ʵ��Э��ջʹ�ã���������OTA�Ŀ������� */
int HILINK_BT_ProcessOtaCtrl(const unsigned char *buf, unsigned int len);

/* ����ʵ��Э��ջʹ�ã���������OTA�Ĵ������� */
int HILINK_BT_ProcessOtaData(const unsigned char *buf, unsigned int len);

/* ����ʵ��Э��ջʹ�ã��Ͽ���������ʱ���ͷ�ͨ��ռ����Դ */
void HILINK_BT_DisconnectFreeResource(void);

/* ����ֵ0����֧�ֱ��ؿغͶ�������������ֵ����֧�� */
int HILINK_BT_SupportLocalControl(void);

/* �豸Ӳ����ʱ���̵��õĽӿ� */
int HILINK_BT_HardRevoke(void);

/*
 * ��ȡ�豸�������ǿ���źŷ��书��ǿ�ȣ���ǿ��λ�õ�ȷ���Լ����ʲ��Է�
 * ��������hilink��֤�����������ֹ������ü����Է���ָ���ĵ���powerΪ����
 * ����λdbm�������豸�������ǿ�ź�ǿ��ֵ��������̲���ʹ�������������ֹ�
 * �ܣ��ӿ�ֱ�ӷ�-1�������Ҫʹ�������������֣���ӿڷ���0�����輰ʱ��Ч����
 * ����HILINK_BT_StartAdvertise()���������㲥
 */
int HILINK_BT_GetDevSurfacePower(char *power);

/*
 * ��ȡ�豸�����ͺţ����ȹ̶������ֽ�
 * subProdIdΪ�������ͺŵĻ�������lenΪ�������ĳ���
 * �����Ʒ���������ͺţ����������ֽ����ͺţ�����'\0'����, ����0
 * û�ж������ͺţ��򷵻�-1
 * �ýӿ����豸������ʵ��
 * ��hilink sdk��ͬ���壬˫ģ��ģʽֻ��һ�ݣ����ṩ�����������ң��ݲ�����̹淶����
 */
int HILINK_GetSubProdId(char *subProdId, int len);

/*
 * ��ȡ�豸SN
 * ��hilink sdk��ͬ���壬˫ģ��ģʽֻ��һ�ݣ����ṩ�����������ң��ݲ�����̹淶����
 */
void HilinkGetDeviceSn(unsigned int len, char *sn);

/*
 * ��ȡ�豸��ذ汾��
 * ����0��ʾ�汾�Ż�ȡ�ɹ�������������ʾ�汾�Ż�ȡʧ��
 * ע�⣬�˽ӿ�ΪHiLink�ڲ����ú���
 * ��hilink sdk��ͬ���壬˫ģ��ģʽֻ��һ�ݣ����ṩ�����������ң��ݲ�����̹淶����
 */
int getDeviceVersion(char **firmwareVer, char **softwareVer, char **hardwareVer);

/*
 * ��������linuxϵͳ��д�ļ���·��,·�����Ȳ��ܳ���33���ֽ�,����������
 * Ҫ��洢·���Ƿ���ʧ�Եģ��汾������Ӱ���·���ļ�
 */
void HILINK_BT_SetConfigDirPath(const char *configDirPath);

/*
 * �����Զ����ʽ������ַ���
 * ����0��ʾʧ��,������ʾʵ��������ֽ���
 */
int HILINK_BT_Printf(const char *format, ...);

#ifdef __cplusplus
}
#endif
#endif
