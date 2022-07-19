// Copyright 2021-2022 The jdh99 Authors. All rights reserved.
// RFF 1��Network Layer Protocol(NLP)���
// Authors: jdh99 <jdh821@163.com>

#include "utznlp.h"
#include "utzcommon.h"
#include "utz.h"

// UtzBytesToStandardHeader �ֽ���ת��Ϊ��׼ͷ��.�ֽ����Ǵ��
// �ֽ���data������ڱ�׼ͷ������
// ����ͷ���Լ�ͷ���ֽ���.�ֽ���Ϊ0��ʾת��ʧ��
int UtzBytesToStandardHeader(uint8_t* data, int dataLen, UtzStandardHeader* header) {
    if (dataLen < UTZ_NLP_HEAD_LEN) {
        return 0;
    }

    int j = 0;
    header->PayloadLen.Value = (data[j] << 8) + data[j + 1];
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
    data[j++] = header->PayloadLen.Value >> 8;
    data[j++] = header->PayloadLen.Value;
    data[j++] = header->NextHead;

    UtzMemcpyReverse(data + j, (uint8_t *)&(header->SrcIA), UTZ_IA_LEN);
    j += UTZ_IA_LEN;
    UtzMemcpyReverse(data + j, (uint8_t *)&(header->DstIA), UTZ_IA_LEN);
    j += UTZ_IA_LEN;
    return j;
}

// UtzConvertPayloadLenMember �غɳ���ת���ɱ�׼ͷ���е��غɳ��ȳ�Ա
uint16_t UtzConvertPayloadLenMember(uint16_t payloadLen) {
    return (UTZ_NLP_VERSION << 12) + payloadLen;
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

// UtzIsAckCmd �Ƿ�Ӧ������
bool UtzIsAckCmd(uint8_t cmd) {
    return (cmd & 0x80) != 0;
}

// UtzGetAckCmd �õ�Ӧ��������
uint8_t UtzGetAckCmd(uint8_t cmd) {
    return cmd | 0x80;
}

// UtzGetReqCmd �õ�����������
uint8_t UtzGetReqCmd(uint8_t cmd) {
    return cmd & 0x7f;
}
