// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 2��Extension Header Protocol(EHP)
// Authors: jdh99 <jdh821@163.com>

#include "utzehp.h"
#include "utznlv1.h"
#include "utzcommon.h"

#include "tzmalloc.h"

#include <string.h>

// UtzBytesToRouteHeader �ֽ���ת��Ϊ·��ͷ��
// bytesNum�Ƿ��ص�ת��ͷ�����ֽ����ֽ���.���Ϊ0��ʾת��ʧ��
// ����ͷ��ָ��,ΪNULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
UtzRouteHeader* UtzBytesToRouteHeader(uint8_t* data, int dataLen, int* bytesNum) {
    *bytesNum = 0;

    // ͷ�����ݱ�������
    if (dataLen < 3) {
        return NULL;
    }

    int routeNum = data[2] & 0x7f;
    UtzRouteHeader* header = (UtzRouteHeader*)TZMalloc(Mid, (int)sizeof(UtzRouteHeader) + routeNum * UTZ_IA_LEN);
    if (header == NULL) {
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

    int offset = 3;
    for (int i = 0; i < header->RouteNum; i++) {
        header->IAList[i] = UtzBytesToIA(data + offset);
        offset += UTZ_IA_LEN;
    }
    *bytesNum = offset;
    return header;
}

// UtzRouteHeaderToBytes ·��ͷ��ת��Ϊ�ֽ���
// ���ص����ֽ���.���Ϊ0��ʾת��ʧ��
int UtzRouteHeaderToBytes(UtzRouteHeader* header, uint8_t* data, int dataSize) {
    if (dataSize < header->RouteNum * UTZ_IA_LEN + 3) {
        return 0;
    }

    int j = 0;
    data[j++] = header->NextHead;
    // ͷ�����ݳ���
    data[j++] = header->RouteNum * UTZ_IA_LEN + 1;

    uint8_t routeNum = header->RouteNum & 0x7f;
    if (header->IsStrict) {
        routeNum |= 0x80;
    }
    data[j++] = routeNum;

    for (int i = 0; i < header->RouteNum; i++) {
        UtzIAToBytes(header->IAList[i], data + j);
        j += UTZ_IA_LEN;
    }
    return j;
}

// UtzIsPayloadHeader �Ƿ��غ�ͷ��
bool UtzIsPayloadHeader(uint8_t head) {
    return (head == UTZ_HEADER_FLP || head == UTZ_HEADER_WTS || head == UTZ_HEADER_DUP || head == UTZ_HEADER_SFTPA ||
        head == UTZ_HEADER_SFTPB || head == UTZ_HEADER_STCP || head == UTZ_HEADER_ITCP || head == UTZ_HEADER_DAP ||
        head == UTZ_HEADER_COMPRESS_COMPLEX || head == UTZ_HEADER_STANDARD_COMPLEX || head == UTZ_HEADER_GUAAP ||
        head == UTZ_HEADER_SLP || head == UTZ_HEADER_DCOM || head == UTZ_HEADER_ISH);
    }

// UtzBytesToSimpleSecurityHeader �ֽ���ת��Ϊ�򵥰�ȫͷ��
// bytesNum�Ƿ��ص�ת��ͷ�����ֽ����ֽ���.���Ϊ0��ʾת��ʧ��
// ����ͷ��ָ��,ΪNULL��ʾת��ʧ��.ת���ɹ�Ҫע���ͷ�ָ��
UtzSimpleSecurityHeader* UtzBytesToSimpleSecurityHeader(uint8_t* data, int dataLen, int* bytesNum) {
    *bytesNum = 0;

    // ͷ�����ݱ�������
    if (dataLen < 2) {
        return NULL;
    }
    int headerPayloadLen = data[1];
    if (dataLen < 2 + headerPayloadLen) {
        return NULL;
    }

    // ��1�ǿ��ǵ��������ַ���,C����ĩβ���'\0'
    UtzSimpleSecurityHeader* header = (UtzSimpleSecurityHeader*)TZMalloc(Mid, (int)sizeof(UtzSimpleSecurityHeader) +
        headerPayloadLen + 1);
    header->NextHead = data[0];
    header->PwdLen = (uint8_t)headerPayloadLen;
    memcpy(header->Pwd, data + 2, (uint64_t)headerPayloadLen);
    *bytesNum = 2 + headerPayloadLen;
    return header;
}

// SimpleSecurityHeaderToBytes �򵥰�ȫͷ��ת��Ϊ�ֽ���
// ���ص����ֽ���.���Ϊ0��ʾת��ʧ��
int UtzSimpleSecurityHeaderToBytes(UtzSimpleSecurityHeader* header, uint8_t* data, int dataSize) {
    if (dataSize < header->PwdLen + 2) {
        return 0;
    }

    int j = 0;
    data[j++] = header->NextHead;
    // ͷ�����ݳ���
    data[j++] = header->PwdLen;

    memcpy(data + j, header->Pwd, header->PwdLen);
    j += header->PwdLen;
    return j;
}
