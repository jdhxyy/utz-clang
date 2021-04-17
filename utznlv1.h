// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 1��Network Layer Version 1(NLv1)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_NLV1_H
#define UTZ_NLV1_H

#include <stdint.h>
#include <stdbool.h>

// Э��汾
#define UTZ_NLV1_VERSION_NAME "1.1"

// ��׼ͷ������
#define UTZ_NLV1_HEAD_LEN 22

// �����ַ
// δָ����ַ
#define UTZ_IA_INVALID 0x0
// �ػ���ַ
#define UTZ_IA_LOOPBACK 0x1
// �㲥��ַ
#define UTZ_IA_BROADCAST 0xFFFFFFFFFFFFFFFF
// �㲥�̵�ַ
#define UTZ_SHORT_IA_BROADCAST 0xFFFFFFFF
// Э�����̵�ַ
#define UTZ_SHORT_IA_COORDINATOR 0x10

// IA��ַ�ֽ���
#define UTZ_IA_LEN 8
#define UTZ_SHORT_IA_LEN 4
#define UTZ_TINY_IA_LEN 2

// ��Ч��������
#define UTZ_HOPS_LIMIT_INVALID 255

// 4�ֽڶ̵�ַǰ׺
#define UTZ_SHORT_IA_PREFIX 0xFE00000000000000
// 2�ֽڶ̵�ַǰ׺
#define UTZ_TINY_IA_PREFIX 0xFE00000100000000
// 4�ֽڶ̵�ַ����
#define UTZ_SHORT_IA_MASK 0xFFFFFFFF
// 2�ֽڶ̵�ַ����
#define UTZ_TINY_IA_MASK 0xFFFF

// MTU
#define UTZ_NLV1_MTU 1280

#pragma pack(1)

// UtzStandardHeader ��׼ͷ��
typedef struct {    
    uint8_t Version;
    uint8_t FrameIndex;
    uint16_t PayloadLen;
    uint8_t NextHead;
    uint8_t HopsLimit;
    uint64_t SrcIA;
    uint64_t DstIA;
} UtzStandardHeader;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
#pragma pack()

// �ڴ����id
extern int UtzMid;

// UtzLoad ģ������
void UtzLoad(int mid);

// UtzBytesToStandardHeader �ֽ���ת��Ϊ��׼ͷ��.�ֽ����Ǵ��
// �ֽ���data������ڱ�׼ͷ������
// ����ͷ���Լ�ͷ���ֽ���.ͷ��Ϊnil�����ֽ���Ϊ0��ʾת��ʧ��
int UtzBytesToStandardHeader(uint8_t* data, int dataLen, UtzStandardHeader* header);

// UtzStandardHeaderToBytes ��׼ͷ��ת��Ϊ�ֽ���.�ֽ����Ǵ��
// �ֽ���data������ڱ�׼ͷ������
// ����ֵ��ת������ֽ����ĳ���.����ֵ��0��ʾת��ʧ��
int UtzStandardHeaderToBytes(UtzStandardHeader* header, uint8_t* data, int dataSize);

// UtzIsGlobalIA �Ƿ���ȫ�򵥲���ַ
bool UtzIsGlobalIA(uint64_t ia);

// UtzIsUniqueLocalIA �Ƿ���Ψһ���ص�ַ
bool UtzIsUniqueLocalIA(uint64_t ia);

// UtzIsEthernetIA �Ƿ�����̫��ַ
bool UtzIsEthernetIA(uint64_t ia);

// UtzGenerateFrameIndex ����֡���
uint8_t UtzGenerateFrameIndex(void);

#endif
