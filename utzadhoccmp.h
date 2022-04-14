// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 27��TZ-STAR������ϵͳ���
// Ad Hoc Newwork Control Message Protocol(ADHOCCMP):���������Ʊ���Э��
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_ADHOCCHEADER_H
#define UTZ_ADHOCCHEADER_H

#include "utzcommon.h"

// �汾
#define UTZ_ADHOCCMP_VERSION_NAME "1.2"

// ����������ͷ������
#define HEADER_ADHOCC_LEN 15

// ����
// �ű�
#define UTZ_ADHOCCMP_BEACON 0x10
// Ӧ��
#define UTZ_ADHOCCMP_ACK 0x11
// ��������
#define UTZ_ADHOCCMP_REQUIRE_PUSH 0x12

#pragma pack(1)

// UtzAdhoccHeaderControlWord ����������ͷ��������
typedef union {
    struct {
        // ���
        uint8_t Index:4;
        // ��������.0: Qos0���Ͳ���ҪӦ�� 1:Qos1������ҪӦ��
        bool IsQos1:1;
        // ����ģʽ����λ.0: ��������.1: Ӧ��ʽ����
        bool IsReceiveAckSend:1;
        // �������Ϳ���λ
        bool IsContinueSend:1;
        // Ӧ��ʽ���Ϳ���λ
        bool IsAckSend:1;
    } bit;
    uint8_t value;
} UtzAdhoccHeaderControlWord;

// UtzAdhoccHeader ����������ͷ���ṹ
typedef struct {
    uint8_t NextHead;
    // ������
    UtzAdhoccHeaderControlWord ControlWord;
    // �����
    uint32_t PanIA;
    // �м�Դ��ַ
    uint32_t SrcRelayIA;
    // �м�Ŀ�ĵ�ַ
    uint32_t DstRelayIA;
    // �ϻ�ʱ��
    uint8_t AgingTime;
} UtzAdhoccHeader;

// ͨ�Žṹ�嶨��
// UtzAdhoccmpBeacon �ű�
typedef struct {
    // ���ڵ��ַ
    uint32_t ParentIA;
    // ������
    uint8_t Hops;
} UtzAdhoccmpBeacon;

// UtzAdhoccmpAck Ӧ��
typedef struct {
    // ����֡�ֵ�֡���
    uint8_t Index;
} UtzAdhoccmpAck;

// UtzAdhoccmpRequirePush ��������
typedef struct {
    // �ϴ��������
    uint8_t LastPushIndex;
    // �ϴ�����Դ��ַ
    uint32_t LastPushSrcIA;
} UtzAdhoccmpRequirePush;

#pragma pack()

// UtzBytesToAdhoccHeader �ֽ���ת��Ϊ����������ͷ��
// ����ͷ���Լ�ͷ���ֽ���.ͷ��Ϊnil�����ֽ���Ϊ0��ʾת��ʧ��
int UtzBytesToAdhoccHeader(uint8_t* data, int dataLen, UtzAdhoccHeader* header);

// UtzADHOCCHeaderToBytes ����������ͷ��ת��Ϊ�ֽ���.ת����洢��bytes��
// ����ֵ��ת������ֽ����ĳ���.����ֵ��0��ʾת��ʧ��
int UtzAdhoccHeaderToBytes(UtzAdhoccHeader* header, uint8_t* data, int dataSize);

// UtzGetAdhoccIndex ��ȡ������֡���
uint8_t UtzGetAdhoccIndex(void);

// UtzByteToAgingTime �ֽ�ת��Ϊ�ϻ�ʱ��
// �ϻ�ʱ�䵥λ:s
int UtzByteToAgingTime(uint8_t byte);

// UtzAgingTimeToByte �ϻ�ʱ��ת��Ϊ�ֽ�
// �ϻ�ʱ�䵥λ:s
uint8_t UtzAgingTimeToByte(int agingTime);

#endif
