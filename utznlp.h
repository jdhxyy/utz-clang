// Copyright 2021-2022 The jdh99 Authors. All rights reserved.
// RFF 1��Network Layer Protocol(NLP)���
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_NLV1_H
#define UTZ_NLV1_H

#include <stdint.h>
#include <stdbool.h>

// Э��汾
#define UTZ_NLP_VERSION_NAME "2.0"

// ��׼ͷ������
#define UTZ_NLP_HEAD_LEN 11

// �����ַ
// δָ����ַ
#define UTZ_IA_INVALID 0x0
// �ػ���ַ
#define UTZ_IA_LOOPBACK 0x1
// �㲥��ַ
#define UTZ_IA_BROADCAST 0xFFFFFFFF
// �㲥�̵�ַ
#define UTZ_SHORT_IA_BROADCAST 0xFFFFFFFF

// IA��ַ�ֽ���
#define UTZ_IA_LEN 4

// MTU
#define UTZ_NLP_MTU 1280

#pragma pack(1)

typedef union {
    struct {
        // ƫ����
        uint16_t Len:12;
        // ���һƬ��ʶ
        uint16_t Version:4;
    } Bit;
    uint16_t Value;
} UtzStandardHeaderPayloadLen;

// UtzStandardHeader ��׼ͷ��
typedef struct {    
    UtzStandardHeaderPayloadLen PayloadLen;
    uint8_t NextHead;
    uint32_t SrcIA;
    uint32_t DstIA;
} UtzStandardHeader;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
#pragma pack()

// UtzBytesToStandardHeader �ֽ���ת��Ϊ��׼ͷ��.�ֽ����Ǵ��
// �ֽ���data������ڱ�׼ͷ������
// ����ͷ���Լ�ͷ���ֽ���.�ֽ���Ϊ0��ʾת��ʧ��
int UtzBytesToStandardHeader(uint8_t* data, int dataLen, UtzStandardHeader* header);

// UtzStandardHeaderToBytes ��׼ͷ��ת��Ϊ�ֽ���.�ֽ����Ǵ��
// �ֽ���data������ڱ�׼ͷ������
// ����ֵ��ת������ֽ����ĳ���.����ֵ��0��ʾת��ʧ��
int UtzStandardHeaderToBytes(UtzStandardHeader* header, uint8_t* data, int dataSize);

// UtzConvertPayloadLenMember �غɳ���ת���ɱ�׼ͷ���е��غɳ��ȳ�Ա
uint16_t UtzConvertPayloadLenMember(uint16_t payloadLen);

// UtzIsGlobalIA �Ƿ���ȫ�򵥲���ַ
bool UtzIsGlobalIA(uint32_t ia);

// UtzIsUniqueLocalIA �Ƿ���Ψһ���ص�ַ
bool UtzIsUniqueLocalIA(uint32_t ia);

// IsMulticastIA �Ƿ����鲥��ַ
bool UtzIsMulticastIA(uint32_t ia);

// UtzIsAckCmd �Ƿ�Ӧ������
bool UtzIsAckCmd(uint8_t cmd);

// UtzGetAckCmd �õ�Ӧ��������
uint8_t UtzGetAckCmd(uint8_t cmd);

// UtzGetReqCmd �õ�����������
uint8_t UtzGetReqCmd(uint8_t cmd);

#endif
