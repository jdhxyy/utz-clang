// Copyright 2021-2022 The jdh99 Authors. All rights reserved.
// RFF 2：Extension Header Protocol(EHP)
// Authors: jdh99 <jdh821@163.com>

#include "utzehp.h"
#include "utznlp.h"
#include "utzcommon.h"

#include "tzmalloc.h"
#include "lagan.h"

#include <string.h>

// UtzBytesToRouteHeader 字节流转换为路由头部.字节流是大端
// 字节流data必须大于路由头部长度
// 返回头部以及头部字节数.头部为nil或者字节数为0表示转换失败
int UtzBytesToRouteHeader(uint8_t* data, int dataLen, UtzRouteHeader* header) {
    // 头部数据必须完整
    if (dataLen < 5) {
        return 0;
    }

    header->NextHead = data[0];
    header->IA = UtzBytesToIA(data + 1);
    return 5;
}

// UtzRouteHeader 路由头部转换为字节流
// 字节流data必须大于路由头部长度
// 返回值是转换后的字节流的长度.返回值是0表示转换失败
int UtzRouteHeaderToBytes(UtzRouteHeader* header, uint8_t* data, int dataSize) {
    if (dataSize < 5) {
        return 0;
    }
    data[0] = header->NextHead;
    UtzIAToBytes(header->IA, data + 1);
    return 5;
}

// UtzIsPayloadHeader 是否载荷头部
bool UtzIsPayloadHeader(uint8_t head) {
    return (head == UTZ_HEADER_CCP || head == UTZ_HEADER_RP || head == UTZ_HEADER_FLP || head == UTZ_HEADER_WTS || 
        head == UTZ_HEADER_DUP || head == UTZ_HEADER_SFTPA || head == UTZ_HEADER_SFTPB || head == UTZ_HEADER_STCP || 
        head == UTZ_HEADER_ITCP || head == UTZ_HEADER_DAP || head == UTZ_HEADER_COMPRESS_COMPLEX || 
        head == UTZ_HEADER_STANDARD_COMPLEX || head == UTZ_HEADER_GUAAP || head == UTZ_HEADER_SLP || 
        head == UTZ_HEADER_DCOM || head == UTZ_HEADER_ISH);
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

// UtzFragmentHeaderToBytes 分片头部转换为字节流
// 返回值是转换后的字节流的长度.返回值是0表示转换失败
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

// UtzBytesToFragmentHeader 字节流转换为分片头部.字节流是大端
// 返回头部以及头部字节数.字节数为0表示转换失败
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
