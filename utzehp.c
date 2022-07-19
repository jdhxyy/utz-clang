// Copyright 2021-2022 The jdh99 Authors. All rights reserved.
// RFF 2��Extension Header Protocol(EHP)
// Authors: jdh99 <jdh821@163.com>

#include "utzehp.h"
#include "utznlp.h"
#include "utzcommon.h"

#include "tzmalloc.h"
#include "lagan.h"

#include <string.h>

// UtzBytesToRouteHeader �ֽ���ת��Ϊ·��ͷ��.�ֽ����Ǵ��
// �ֽ���data�������·��ͷ������
// ����ͷ���Լ�ͷ���ֽ���.ͷ��Ϊnil�����ֽ���Ϊ0��ʾת��ʧ��
int UtzBytesToRouteHeader(uint8_t* data, int dataLen, UtzRouteHeader* header) {
    // ͷ�����ݱ�������
    if (dataLen < 5) {
        return 0;
    }

    header->NextHead = data[0];
    header->IA = UtzBytesToIA(data + 1);
    return 5;
}

// UtzRouteHeader ·��ͷ��ת��Ϊ�ֽ���
// �ֽ���data�������·��ͷ������
// ����ֵ��ת������ֽ����ĳ���.����ֵ��0��ʾת��ʧ��
int UtzRouteHeaderToBytes(UtzRouteHeader* header, uint8_t* data, int dataSize) {
    if (dataSize < 5) {
        return 0;
    }
    data[0] = header->NextHead;
    UtzIAToBytes(header->IA, data + 1);
    return 5;
}

// UtzIsPayloadHeader �Ƿ��غ�ͷ��
bool UtzIsPayloadHeader(uint8_t head) {
    return (head == UTZ_HEADER_CCP || head == UTZ_HEADER_RP || head == UTZ_HEADER_FLP || head == UTZ_HEADER_WTS || 
        head == UTZ_HEADER_DUP || head == UTZ_HEADER_SFTPA || head == UTZ_HEADER_SFTPB || head == UTZ_HEADER_STCP || 
        head == UTZ_HEADER_ITCP || head == UTZ_HEADER_DAP || head == UTZ_HEADER_COMPRESS_COMPLEX || 
        head == UTZ_HEADER_STANDARD_COMPLEX || head == UTZ_HEADER_GUAAP || head == UTZ_HEADER_SLP || 
        head == UTZ_HEADER_DCOM || head == UTZ_HEADER_ISH);
    }

// UtzBytesToSimpleSecurityHeader �ֽ���ת��Ϊ�򵥰�ȫͷ��
// offset��ת�����ֽ����µ�ƫ�Ƶ�ַ.���Ϊ0��ʾת��ʧ��.����Ҫ֪������дNULL
// ����ͷ��ָ��,ΪNULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
UtzSimpleSecurityHeader* UtzBytesToSimpleSecurityHeader(uint8_t* data, int dataLen, int* offset) {
    if (offset != NULL) {
        *offset = 0;
    }

    // ͷ�����ݱ�������
    if (dataLen < 2) {
        return NULL;
    }
    int headerPayloadLen = data[1];
    if (dataLen < 2 + headerPayloadLen) {
        return NULL;
    }

    // ��1�ǿ��ǵ��������ַ���,C����ĩβ���'\0'
    UtzSimpleSecurityHeader* header = (UtzSimpleSecurityHeader*)TZMalloc(UtzGetMid(), 
        (int)sizeof(UtzSimpleSecurityHeader) + headerPayloadLen + 1);
    if (header == NULL) {
        LE(UTZ_TAG, "bytes to simple security header failed!malloc failed!");
        return NULL;
    }
    header->NextHead = data[0];
    header->PwdLen = (uint8_t)headerPayloadLen;
    memcpy(header->Pwd, data + 2, (uint64_t)headerPayloadLen);
    if (offset != NULL) {
        *offset = 2 + headerPayloadLen;
    }
    return header;
}

// SimpleSecurityHeaderToBytes �򵥰�ȫͷ��ת��Ϊ�ֽ���
// ���ص����ֽ���.�����NULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
TZBufferDynamic* UtzSimpleSecurityHeaderToBytes(UtzSimpleSecurityHeader* header) {
    return UtzSimpleSecurityHeaderDataToBytes(header->NextHead, (char*)header->Pwd);
}

// UtzSimpleSecurityHeaderDataToBytes �򵥰�ȫͷ������ת��Ϊ�ֽ���
// ���ص����ֽ���.�����NULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
TZBufferDynamic* UtzSimpleSecurityHeaderDataToBytes(uint8_t nextHead, char* pwd) {
    int pwdLen = (int)strlen(pwd);
    TZBufferDynamic* data = (TZBufferDynamic*)TZMalloc(UtzGetMid(), (int)sizeof(TZBufferDynamic) + pwdLen + 2);
    if (data == NULL) {
        LE(UTZ_TAG, "simple security header data to bytes failed!malloc failed!");
        return NULL;
    }

    int j = 0;
    data->buf[j++] = nextHead;
    // ͷ�����ݳ���
    data->buf[j++] = (uint8_t)pwdLen;

    memcpy(data->buf + j, pwd, (size_t)pwdLen);
    j += pwdLen;
    data->len = j;
    return data;
}

// UtzFragmentHeaderToBytes ��Ƭͷ��ת��Ϊ�ֽ���
// ����ֵ��ת������ֽ����ĳ���.����ֵ��0��ʾת��ʧ��
int UtzFragmentHeaderToBytes(UtzFragmentHeader* header, uint8_t* data, int dataSize) {
    if (dataSize < sizeof(UtzFragmentHeader)) {
        return 0;
    }

    int j = 0;
    data[j++] = header->Head;
    data[j++] = header->Flag >> 8;
    data[j++] = header->Flag;
    data[j++] = header->Offset.Value >> 8;
    data[j++] = header->Offset.Value;
    return j;
}

// UtzBytesToFragmentHeader �ֽ���ת��Ϊ��Ƭͷ��.�ֽ����Ǵ��
// ����ͷ���Լ�ͷ���ֽ���.�ֽ���Ϊ0��ʾת��ʧ��
int UtzBytesToFragmentHeader(uint8_t* data, int dataLen, UtzFragmentHeader* header) {
    if (dataLen < sizeof(UtzFragmentHeader)) {
        return 0;
    }

    int j = 0;
    header->Head = data[j++];
    header->Flag = (data[j] << 8) + data[j + 1];
    j += 2;
    header->Offset.Value = (data[j] << 8) + data[j + 1];
    j += 2;
    return j;
}
