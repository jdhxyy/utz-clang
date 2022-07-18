// Copyright 2022-2022 The jdh99 Authors. All rights reserved.
// RFF 8��Device Upgrade Protocol(DUP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_DUP_H
#define UTZ_DUP_H

#include <stdint.h>

// Э��汾
#define UTZ_DUP_VERSION_NAME "1.3"

// ������
// ��ȡ�汾��Ϣ
#define UTZ_DUP_READ_VERSION 0x10
// ��ʼ����
#define UTZ_DUP_START 0x11
// ֹͣ����
#define UTZ_DUP_STOP 0x12
// ��ȡ�����ļ���Ϣ
#define UTZ_DUP_READ_FILE_INFO 0x13
// ��ȡ�����ļ�����
#define UTZ_DUP_READ_FILE_DATA 0x14

#pragma pack(1)

// ͨ�Žṹ�嶨��
// UtzDupAckReadVersion ��ȡ�汾��ϢӦ��
typedef struct {
    // �豸����
    uint16_t DeviceType;
    // �汾��
    uint8_t Version;
    // �����ļ��汾��
    uint8_t UpgradeFileVersion;
    // ��������.ȡֵ:0-100
    uint8_t UpgradeProgress;
} UtzDupAckReadVersion;

// UtzDupReqStart ��ʼ��������
typedef struct {
    // �豸����
    uint16_t DeviceType;
    // �����ļ��汾��
    uint8_t UpgradeFileVersion;
} UtzDupReqStart;

// UtzDupAckStart ��ʼ����Ӧ��
typedef struct {
    uint8_t Result;
} UtzDupAckStart;

// ���
// �ɹ�
#define UTZ_DUP_START_RESULT_OK 0x0
// ʧ��.����
#define UTZ_DUP_START_RESULT_OTHER 0x1
// ʧ��.�豸���Ͳ�ƥ��
#define UTZ_DUP_START_RESULT_WRONG_DEVICE_TYPE 0x2
// ʧ��.����汾����ͬ
#define UTZ_DUP_START_RESULT_SAME_VERSION 0x3

// UtzDupReqReadUpgradeFileInfo ��ȡ�����ļ���Ϣ����
typedef struct {
    // �豸����
    uint16_t DeviceType;
    // ��ǰ�汾��
    uint8_t Version;
} UtzDupReqReadUpgradeFileInfo;

// UtzDupAckReadUpgradeFileInfo ��ȡ�����ļ���ϢӦ��
typedef struct {
    // �ļ��豸����
    uint16_t FileDeviceType;
    // �ļ�����汾
    uint8_t FileVersion;
    // �ļ����ֽ���
    uint32_t FileTotalBytes;
    // У�鷽ʽ.0:MD5,1:CRC16,2:CRC32
    uint8_t CheckType;
    // �ļ�У����
    uint8_t FileCheckSum[16];
} UtzDupAckReadUpgradeFileInfo;

// У�鷽ʽ
#define UTZ_DUP_CHECK_TYPE_MD5 0
#define UTZ_DUP_CHECK_TYPE_CRC16 1
#define UTZ_DUP_CHECK_TYPE_CRC32 2

// UtzDupReqReadUpgradeFileData ��ȡ�����ļ���������
typedef struct {
    // �豸����
    uint16_t DeviceType;
    // �汾��
    uint8_t Version;
    // �����ļ��汾��
    uint8_t UpgradeFileVersion;
    // ƫ�Ƶ�ַ
    uint32_t Offset;
} UtzDupReqReadUpgradeFileData;

// UtzDupAckReadUpgradeFileData ��ȡ�����ļ�����Ӧ��
typedef struct {
    // �ļ��豸����
    uint16_t FileDeviceType;
    // �ļ�����汾
    uint8_t FileVersion;
    // ƫ�Ƶ�ַ
    uint32_t Offset;
    // ���ݳ���
    uint16_t DataLen;
    // ����
    uint8_t Data[];
} UtzDupAckReadUpgradeFileData;

#pragma pack()

#endif
