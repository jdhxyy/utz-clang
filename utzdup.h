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
// �ϱ��汾��Ϣ
#define UTZ_DUP_UPLOAD_VERSION 0x11
// ��ʼ����
#define UTZ_DUP_START 0x12
// ֹͣ����
#define UTZ_DUP_STOP 0x13
// ��ȡ�����ļ���Ϣ
#define UTZ_DUP_READ_FILE_INFO 0x14
// ��ȡ�����ļ�����
#define UTZ_DUP_READ_FILE_DATA 0x15

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

// UtzDupReqUploadVersion �ϱ��汾��Ϣ����
typedef struct {
    // �豸����
    uint16_t DeviceType;
    // ��ǰ�汾��
    uint8_t Version;
} UtzDupReqUploadVersion;

// UtzDupAckUploadVersion �ϱ��汾��ϢӦ��
typedef struct {
    // �豸����
    uint16_t DeviceType;
    // �����ļ��汾��
    uint8_t UpgradeFileVersion;
} UtzDupAckUploadVersion;

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

#pragma pack()

#endif
