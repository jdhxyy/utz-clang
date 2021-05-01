// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 2��Extension Header Protocol(EHP)
// Authors: jdh99 <jdh821@163.com>

#include "utzehp.h"
#include "utznlv1.h"
#include "utzcommon.h"

#include "tzmalloc.h"
#include "lagan.h"

#include <string.h>

// UtzBytesToRouteHeader �ֽ���ת��Ϊ·��ͷ��
// offset��ת�����ֽ����µ�ƫ�Ƶ�ַ.���Ϊ0��ʾת��ʧ��.����Ҫ֪������дNULL
// ����ͷ��ָ��,ΪNULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
UtzRouteHeader* UtzBytesToRouteHeader(uint8_t* data, int dataLen, int* offset) {
    if (offset != NULL) {
        *offset = 0;
    }

    // ͷ�����ݱ�������
    if (dataLen < 3) {
        return NULL;
    }

    int routeNum = data[2] & 0x7f;
    UtzRouteHeader* header = (UtzRouteHeader*)TZMalloc(UtzGetMid(), (int)sizeof(UtzRouteHeader) + routeNum * UTZ_IA_LEN);
    if (header == NULL) {
        LE(UTZ_TAG, "bytes to route header failed!malloc failed!");
        return NULL;
    }

    header->NextHead = data[0];
    int headerPayloadLen = data[1];
    if (dataLen < 2 + headerPayloadLen) {
        return NULL;
    }

    // �ܳ��Ȳ�Ӧ��С��·�ɵ�ַ�ܳ���
    header->RouteNum = data[2] & 0x7f;
    header->IsStrict = (data[2] >> 7) == 0x1;
    if (dataLen < 3 + header->RouteNum * UTZ_IA_LEN) {
        return NULL;
    }

    int newOffset = 3;
    for (int i = 0; i < header->RouteNum; i++) {
        header->IAList[i] = UtzBytesToIA(data + newOffset);
        newOffset += UTZ_IA_LEN;
    }

    if (offset != NULL) {
        *offset = newOffset;
    }
    return header;
}

// UtzRouteHeaderToBytes ·��ͷ��ת��Ϊ�ֽ���
// ���ص����ֽ���.�����NULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
TZBufferDynamic* UtzRouteHeaderToBytes(UtzRouteHeader* header) {
    int dataLen = (int)sizeof(TZBufferDynamic) + header->RouteNum * UTZ_IA_LEN + 3;
    TZBufferDynamic* data = (TZBufferDynamic*)TZMalloc(UtzGetMid(), dataLen);
    if (data == NULL) {
        LE(UTZ_TAG, "route header to bytes failed!malloc failed!");
        return NULL;
    }

    int j = 0;
    data->buf[j++] = header->NextHead;
    // ͷ�����ݳ���
    data->buf[j++] = header->RouteNum * UTZ_IA_LEN + 1;

    uint8_t routeNum = header->RouteNum & 0x7f;
    if (header->IsStrict) {
        routeNum |= 0x80;
    }
    data->buf[j++] = routeNum;

    for (int i = 0; i < header->RouteNum; i++) {
        UtzIAToBytes(header->IAList[i], data->buf + j);
        j += UTZ_IA_LEN;
    }

    data->len = j;
    return data;
}

// UtzIsPayloadHeader �Ƿ��غ�ͷ��
bool UtzIsPayloadHeader(uint8_t head) {
    return (head == UTZ_HEADER_FLP || head == UTZ_HEADER_WTS || head == UTZ_HEADER_DUP || head == UTZ_HEADER_SFTPA ||
        head == UTZ_HEADER_SFTPB || head == UTZ_HEADER_STCP || head == UTZ_HEADER_ITCP || head == UTZ_HEADER_DAP ||
        head == UTZ_HEADER_COMPRESS_COMPLEX || head == UTZ_HEADER_STANDARD_COMPLEX || head == UTZ_HEADER_GUAAP ||
        head == UTZ_HEADER_SLP || head == UTZ_HEADER_DCOM || head == UTZ_HEADER_ISH);
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
