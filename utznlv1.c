// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 1��Network Layer Version 1(NLv1)
// Authors: jdh99 <jdh821@163.com>

#include "utznlv1.h"
#include "utzcommon.h"

static uint8_t generateFrameIndex = 0;

// UtzBytesToStandardHeader �ֽ���ת��Ϊ��׼ͷ��.�ֽ����Ǵ��
// �ֽ���data������ڱ�׼ͷ������
// ����ͷ���Լ�ͷ���ֽ���.ͷ��Ϊnil�����ֽ���Ϊ0��ʾת��ʧ��
int UtzBytesToStandardHeader(uint8_t* data, int dataLen, UtzStandardHeader* header) {
    if (dataLen < UTZ_NLV1_HEAD_LEN) {
        return 0;
    }

    int j = 0;
    header->Version = data[j++];
    header->FrameIndex = data[j++];
    header->PayloadLen = (uint16_t)((data[j] << 8) + data[j + 1]);
    j += 2;
    header->NextHead = data[j++];
    header->HopsLimit = data[j++];
    header->SrcIA = UtzBytesToIA(data + j);
    j += UTZ_IA_LEN;
    header->DstIA = UtzBytesToIA(data + j);
    j += UTZ_IA_LEN;
    return j;
}

// UtzStandardHeaderToBytes ��׼ͷ��ת��Ϊ�ֽ���.�ֽ����Ǵ��
// �ֽ���data������ڱ�׼ͷ������
// ����ֵ��ת������ֽ����ĳ���.����ֵ��0��ʾת��ʧ��
int UtzStandardHeaderToBytes(UtzStandardHeader* header, uint8_t* data, int dataSize) {
    if (dataSize < UTZ_IA_LEN) {
        return 0;
    }

    int j = 0;
    data[j++] = header->Version;
    data[j++] = header->FrameIndex;
    data[j++] = header->PayloadLen >> 8;
    data[j++] = (uint8_t)header->PayloadLen;
    data[j++] = header->NextHead;
    data[j++] = header->HopsLimit;
    UtzMemcpyReverse(data + j, (uint8_t *)&(header->SrcIA), UTZ_IA_LEN);
    j += UTZ_IA_LEN;
    UtzMemcpyReverse(data + j, (uint8_t *)&(header->DstIA), UTZ_IA_LEN);
    j += UTZ_IA_LEN;
    return j;
}

// UtzIsGlobalIA �Ƿ���ȫ�򵥲���ַ
bool UtzIsGlobalIA(uint64_t ia) {
    return ((ia >> 61) & 0xff) == 0x1;
}

// IsConstantIA �Ƿ��ǹ̶�������ַ
bool UtzIsConstantIA(uint64_t ia) {
    return ((ia >> 61) & 0xff) == 0x2;
}

// UtzIsUniqueLocalIA �Ƿ���Ψһ���ص�ַ
bool UtzIsUniqueLocalIA(uint64_t ia) {
    return ((ia >> 48) & 0xff) == 0xfe;
}

// UtzIsEthernetIA �Ƿ�����̫��ַ
bool UtzIsEthernetIA(uint64_t ia) {
    return ((ia >> 48) & 0xff) == 0xfd;
}

// UtzGenerateFrameIndex ����֡���
uint8_t UtzGenerateFrameIndex(void) {
    generateFrameIndex++;
    return generateFrameIndex;
}
