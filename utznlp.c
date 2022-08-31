// Copyright 2021-2022 The jdh99 Authors. All rights reserved.
// RFF 1：Network Layer Protocol(NLP)设计
// Authors: jdh99 <jdh821@163.com>

#include "utznlp.h"
#include "utzcommon.h"
#include "utz.h"

// UtzBytesToStandardHeader 字节流转换为标准头部.字节流是大端
// 字节流data必须大于标准头部长度
// 返回头部以及头部字节数.字节数为0表示转换失败
int UtzBytesToStandardHeader(uint8_t* data, int dataLen, UtzStandardHeader* header) {
    if (dataLen < UTZ_NLP_HEAD_LEN) {
        return 0;
    }

    int j = 0;
    header->SrcIA = UtzBytesToIA(data + j);
    j += UTZ_IA_LEN;
    header->DstIA = UtzBytesToIA(data + j);
    j += UTZ_IA_LEN;
    header->FrameIndex = data[j++];
    header->NextHead = data[j++];
    header->PayloadLen.Value = (data[j] << 8) + data[j + 1];
    j += 2;
    return j;
}

// UtzStandardHeaderToBytes 标准头部转换为字节流.字节流是大端
// 字节流data必须大于标准头部长度
// 返回值是转换后的字节流的长度.返回值是0表示转换失败
int UtzStandardHeaderToBytes(UtzStandardHeader* header, uint8_t* data, int dataSize) {
    if (dataSize < UTZ_NLP_HEAD_LEN) {
        return 0;
    }

    int j = 0;
    UtzMemcpyReverse(data + j, (uint8_t *)&(header->SrcIA), UTZ_IA_LEN);
    j += UTZ_IA_LEN;
    UtzMemcpyReverse(data + j, (uint8_t *)&(header->DstIA), UTZ_IA_LEN);
    j += UTZ_IA_LEN;
    data[j++] = header->FrameIndex;
    data[j++] = header->NextHead;
    data[j++] = header->PayloadLen.Value >> 8;
    data[j++] = header->PayloadLen.Value;
    return j;
}

// UtzIsGlobalIA 是否是全球单播地址
bool UtzIsGlobalIA(uint32_t ia) {
    return ((ia >> 30) & 0x3) == 0x1;
}

// IsConstantIA 是否是固定单播地址
bool UtzIsConstantIA(uint32_t ia) {
    return ((ia >> 30) & 0x3) == 0x2;
}

// UtzIsUniqueLocalIA 是否是唯一本地地址
bool UtzIsUniqueLocalIA(uint32_t ia) {
    return ((ia >> 16) & 0xffff) == 0xfffe;
}

// IsMulticastIA 是否是组播地址
bool UtzIsMulticastIA(uint32_t ia) {
    return ((ia >> 16) & 0xffff) == 0xffff;
}

// UtzIsAckCmd 是否应答命令
bool UtzIsAckCmd(uint8_t cmd) {
    return (cmd & 0x80) != 0;
}

// UtzGetAckCmd 得到应答命令字
uint8_t UtzGetAckCmd(uint8_t cmd) {
    return cmd | 0x80;
}

// UtzGetReqCmd 得到请求命令字
uint8_t UtzGetReqCmd(uint8_t cmd) {
    return cmd & 0x7f;
}

// UtzGetFrameLen 去除尾缀获取真实帧长
// 返回的是帧长.如果返回值是0表示获取失败
int UtzGetFrameLen(uint8_t* data, int dataLen) {
    if (dataLen < sizeof(UtzStandardHeader)) {
        return 0;
    }

    uint16_t payloadLen = (data[0] << 8) + data[1];
    if (dataLen < sizeof(UtzStandardHeader) + payloadLen) {
        return 0;
    }
    return sizeof(UtzStandardHeader) + payloadLen;
}

// UtzGetFrameIndex 获取帧序号
uint8_t UtzGetFrameIndex(void) {
    static uint8_t index = 0;
    index++;
    return adhoccIndex;
}
