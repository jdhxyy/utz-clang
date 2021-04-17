// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 2：Extension Header Protocol(EHP)
// Authors: jdh99 <jdh821@163.com>

#include "utzehp.h"
#include "utznlv1.h"
#include "utzcommon.h"

#include "tzmalloc.h"

#include <string.h>

// UtzBytesToRouteHeader 字节流转换为路由头部
// bytesNum是返回的转换头部的字节流字节数.如果为0表示转换失败
// 返回头部指针,为NULL表示转换失败.转换成功要注意释放指针
UtzRouteHeader* UtzBytesToRouteHeader(uint8_t* data, int dataLen, int* bytesNum) {
    *bytesNum = 0;

    // 头部数据必须完整
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

    // 总长度不应该小于路由地址总长度
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

// UtzRouteHeaderToBytes 路由头部转换为字节流
// 返回的是字节数.如果为0表示转换失败
int UtzRouteHeaderToBytes(UtzRouteHeader* header, uint8_t* data, int dataSize) {
    if (dataSize < header->RouteNum * UTZ_IA_LEN + 3) {
        return 0;
    }

    int j = 0;
    data[j++] = header->NextHead;
    // 头部数据长度
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

// UtzIsPayloadHeader 是否载荷头部
bool UtzIsPayloadHeader(uint8_t head) {
    return (head == UTZ_HEADER_FLP || head == UTZ_HEADER_WTS || head == UTZ_HEADER_DUP || head == UTZ_HEADER_SFTPA ||
        head == UTZ_HEADER_SFTPB || head == UTZ_HEADER_STCP || head == UTZ_HEADER_ITCP || head == UTZ_HEADER_DAP ||
        head == UTZ_HEADER_COMPRESS_COMPLEX || head == UTZ_HEADER_STANDARD_COMPLEX || head == UTZ_HEADER_GUAAP ||
        head == UTZ_HEADER_SLP || head == UTZ_HEADER_DCOM || head == UTZ_HEADER_ISH);
    }

// UtzBytesToSimpleSecurityHeader 字节流转换为简单安全头部
// bytesNum是返回的转换头部的字节流字节数.如果为0表示转换失败
// 返回头部指针,为NULL表示转换失败.转换成功要注意释放指针
UtzSimpleSecurityHeader* UtzBytesToSimpleSecurityHeader(uint8_t* data, int dataLen, int* bytesNum) {
    *bytesNum = 0;

    // 头部数据必须完整
    if (dataLen < 2) {
        return NULL;
    }
    int headerPayloadLen = data[1];
    if (dataLen < 2 + headerPayloadLen) {
        return NULL;
    }

    // 加1是考虑到密码是字符串,C语言末尾需加'\0'
    UtzSimpleSecurityHeader* header = (UtzSimpleSecurityHeader*)TZMalloc(Mid, (int)sizeof(UtzSimpleSecurityHeader) +
        headerPayloadLen + 1);
    header->NextHead = data[0];
    header->PwdLen = (uint8_t)headerPayloadLen;
    memcpy(header->Pwd, data + 2, (uint64_t)headerPayloadLen);
    *bytesNum = 2 + headerPayloadLen;
    return header;
}

// SimpleSecurityHeaderToBytes 简单安全头部转换为字节流
// 返回的是字节数.如果为0表示转换失败
int UtzSimpleSecurityHeaderToBytes(UtzSimpleSecurityHeader* header, uint8_t* data, int dataSize) {
    if (dataSize < header->PwdLen + 2) {
        return 0;
    }

    int j = 0;
    data[j++] = header->NextHead;
    // 头部数据长度
    data[j++] = header->PwdLen;

    memcpy(data + j, header->Pwd, header->PwdLen);
    j += header->PwdLen;
    return j;
}
