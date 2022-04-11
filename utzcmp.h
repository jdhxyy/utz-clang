// Copyright 2021-2022 The jdh99 Authors. All rights reserved.
// RFF 4��Control Message Protocol(CMP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_CMP_H
#define UTZ_CMP_H

#include <stdint.h>

// �汾
#define UTZ_CMP_VERSION_NAME "1.2"

// ��Ϣ����
// ����ӻ�
#define UTZ_CMP_APPLY_SLAVE 0x25
// ���Ӹ�·��
#define UTZ_CMP_CONNECT_PARENT 0x26

#pragma pack(1)

// ͨ�Žṹ�嶨��
// UtzCmpReqApplySlave ����ӻ�֡����
typedef struct {
    // �ѷ���Ĵӻ���ַ
    uint32_t AssignedSlaveIA;
} UtzCmpReqApplySlave;

// UtzCmpAckApplySlave ����ӻ�֡Ӧ��
typedef struct {
    // ���
    uint8_t Result;
    // �ӻ���ַ
    uint32_t SlaveIA;
    // �ӻ���IP��ַ
    uint32_t SlaveIP;
    // �ӻ��Ķ˿ں�
    uint16_t SlavePort;
    // �ӻ��Ŀ���ֵ
    uint8_t SlaveCost;
} UtzCmpAckApplySlave;

// ���
// �ɹ�
#define UTZ_CMP_APPLY_SLAVE_RESULT_OK 0x0
// ʧ��,����
#define UTZ_CMP_APPLY_SLAVE_RESULT_OTHER 0x1
// ʧ��,��Ȩ������
#define UTZ_CMP_APPLY_SLAVE_RESULT_NO_PERMISSION 0x2
// ʧ��,�޴ӻ�
#define UTZ_CMP_APPLY_SLAVE_RESULT_NO_SLAVE 0x3

// UtzCmpAckApplySlave ���Ӹ�·��Ӧ��
typedef struct {
    // ���
    uint8_t Result;
    // ����ֵ
    uint8_t Cost;
} UtzCmpAckConnectParent;

// ���
// �ɹ�
#define UTZ_CMP_CONNECT_PARENT_RESULT_OK 0x0
// ʧ��,����
#define UTZ_CMP_CONNECT_PARENT_RESULT_OTHER 0x1
// ʧ��,��������·��
#define UTZ_CMP_CONNECT_PARENT_RESULT_NOT_ROUTER 0x2
// ʧ��,��Ȩ������
#define UTZ_CMP_CONNECT_PARENT_RESULT_NO_PERSSION 0x3

#pragma pack()

#endif
