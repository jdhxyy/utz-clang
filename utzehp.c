// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 2：Extension Header Protocol(EHP)
// Authors: jdh99 <jdh821@163.com>

#include "utzehp.h"
#include "utznlv1.h"
#include "utzcommon.h"

#include "tzmalloc.h"
#include "lagan.h"

#include <string.h>

// UtzBytesToRouteHeader 字节流转换为路由头部
// offset是转换后字节流新的偏移地址.如果为0表示转换失败.不需要知道可填写NULL
// 返回头部指针,为NULL表示转换失败.转换成功要注意释放指针
UtzRouteHeader* UtzBytesToRouteHeader(uint8_t* data, int dataLen, int* offset) {
    if (offset != NULL) {
        *offset = 0;
    }

    // 头部数据必须完整
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

    // 总长度不应该小于路由地址总长度
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

// UtzRouteHeaderToBytes 路由头部转换为字节流
// 返回的是字节流.如果是NULL表示转换失败.转换成功要注意释放指针
TZBufferDynamic* UtzRouteHeaderToBytes(UtzRouteHeader* header) {
    int dataLen = (int)sizeof(TZBufferDynamic) + header->RouteNum * UTZ_IA_LEN + 3;
    TZBufferDynamic* data = (TZBufferDynamic*)TZMalloc(UtzGetMid(), dataLen);
    if (data == NULL) {
        LE(UTZ_TAG, "route header to bytes failed!malloc failed!");
        return NULL;
    }

    int j = 0;
    data->buf[j++] = header->NextHead;
    // 头部数据长度
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

// UtzIsPayloadHeader 是否载荷头部
bool UtzIsPayloadHeader(uint8_t head) {
    return (head == UTZ_HEADER_FLP || head == UTZ_HEADER_WTS || head == UTZ_HEADER_DUP || head == UTZ_HEADER_SFTPA ||
        head == UTZ_HEADER_SFTPB || head == UTZ_HEADER_STCP || head == UTZ_HEADER_ITCP || head == UTZ_HEADER_DAP ||
        head == UTZ_HEADER_COMPRESS_COMPLEX || head == UTZ_HEADER_STANDARD_COMPLEX || head == UTZ_HEADER_GUAAP ||
        head == UTZ_HEADER_SLP || head == UTZ_HEADER_DCOM || head == UTZ_HEADER_ISH);
    }

// UtzBytesToSimpleSecurityHeader 字节流转换为简单安全头部
// offset是转换后字节流新的偏移地址.如果为0表示转换失败.不需要知道可填写NULL
// 返回头部指针,为NULL表示转换失败.转换成功要注意释放指针
UtzSimpleSecurityHeader* UtzBytesToSimpleSecurityHeader(uint8_t* data, int dataLen, int* offset) {
    if (offset != NULL) {
        *offset = 0;
    }

    // 头部数据必须完整
    if (dataLen < 2) {
        return NULL;
    }
    int headerPayloadLen = data[1];
    if (dataLen < 2 + headerPayloadLen) {
        return NULL;
    }

    // 加1是考虑到密码是字符串,C语言末尾需加'\0'
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

// SimpleSecurityHeaderToBytes 简单安全头部转换为字节流
// 返回的是字节流.如果是NULL表示转换失败.转换成功要注意释放指针
TZBufferDynamic* UtzSimpleSecurityHeaderToBytes(UtzSimpleSecurityHeader* header) {
    return UtzSimpleSecurityHeaderDataToBytes(header->NextHead, (char*)header->Pwd);
}

// UtzSimpleSecurityHeaderDataToBytes 简单安全头部数据转换为字节流
// 返回的是字节流.如果是NULL表示转换失败.转换成功要注意释放指针
TZBufferDynamic* UtzSimpleSecurityHeaderDataToBytes(uint8_t nextHead, char* pwd) {
    int pwdLen = (int)strlen(pwd);
    TZBufferDynamic* data = (TZBufferDynamic*)TZMalloc(UtzGetMid(), (int)sizeof(TZBufferDynamic) + pwdLen + 2);
    if (data == NULL) {
        LE(UTZ_TAG, "simple security header data to bytes failed!malloc failed!");
        return NULL;
    }

    int j = 0;
    data->buf[j++] = nextHead;
    // 头部数据长度
    data->buf[j++] = (uint8_t)pwdLen;

    memcpy(data->buf + j, pwd, (size_t)pwdLen);
    j += pwdLen;
    data->len = j;
    return data;
}
