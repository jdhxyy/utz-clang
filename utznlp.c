// Copyright 2021-2022 The jdh99 Authors. All rights reserved.
// RFF 1��Network Layer Protocol(NLP)���
// Authors: jdh99 <jdh821@163.com>

#include "utznlp.h"
#include "utzcommon.h"

// UtzBytesToStandardHeader �ֽ���ת��Ϊ��׼ͷ��.�ֽ����Ǵ��
// �ֽ���data������ڱ�׼ͷ������
// ����ͷ���Լ�ͷ���ֽ���.�ֽ���Ϊ0��ʾת��ʧ��
int UtzBytesToStandardHeader(uint8_t* data, int dataLen, UtzStandardHeader* header) {
    if (dataLen < UTZ_NLP_HEAD_LEN) {
        return 0;
    }

    int j = 0;
    header->Version = (data[j] >> 4) & 0xf;
    header->PayloadLen = ((uint16_t)((data[j] << 8) + data[j + 1])) & 0xfff;
    j += 2;
    header->NextHead = data[j++];
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
    if (dataSize < UTZ_NLP_HEAD_LEN) {
        return 0;
    }

    int j = 0;
    uint16_t value = (header->Version << 12) + header->PayloadLen;
    data[j++] = value >> 8;
    data[j++] = value;
    data[j++] = header->NextHead;

    UtzMemcpyReverse(data + j, (uint8_t *)&(header->SrcIA), UTZ_IA_LEN);
    j += UTZ_IA_LEN;
    UtzMemcpyReverse(data + j, (uint8_t *)&(header->DstIA), UTZ_IA_LEN);
    j += UTZ_IA_LEN;
    return j;
}

// UtzIsGlobalIA �Ƿ���ȫ�򵥲���ַ
bool UtzIsGlobalIA(uint32_t ia) {
    return ((ia >> 30) & 0x3) == 0x1;
}

// IsConstantIA �Ƿ��ǹ̶�������ַ
bool UtzIsConstantIA(uint32_t ia) {
    return ((ia >> 30) & 0x3) == 0x2;
}

// UtzIsUniqueLocalIA �Ƿ���Ψһ���ص�ַ
bool UtzIsUniqueLocalIA(uint32_t ia) {
    return ((ia >> 16) & 0xffff) == 0xfffe;
}

// IsMulticastIA �Ƿ����鲥��ַ
bool UtzIsMulticastIA(uint32_t ia) {
    return ((ia >> 16) & 0xffff) == 0xffff;
}
