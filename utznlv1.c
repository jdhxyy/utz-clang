// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 1：Network Layer Version 1(NLv1)
// Authors: jdh99 <jdh821@163.com>

#include "utznlv1.h"
#include "utzcommon.h"

static uint8_t generateFrameIndex = 0;

// UtzBytesToStandardHeader 字节流转换为标准头部.字节流是大端
// 字节流data必须大于标准头部长度
// 返回头部以及头部字节数.头部为nil或者字节数为0表示转换失败
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

// UtzStandardHeaderToBytes 标准头部转换为字节流.字节流是大端
// 字节流data必须大于标准头部长度
// 返回值是转换后的字节流的长度.返回值是0表示转换失败
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

// UtzIsGlobalIA 是否是全球单播地址
bool UtzIsGlobalIA(uint64_t ia) {
    return ((ia >> 61) & 0xff) == 0x1;
}

// IsConstantIA 是否是固定单播地址
bool UtzIsConstantIA(uint64_t ia) {
    return ((ia >> 61) & 0xff) == 0x2;
}

// UtzIsUniqueLocalIA 是否是唯一本地地址
bool UtzIsUniqueLocalIA(uint64_t ia) {
    return ((ia >> 48) & 0xff) == 0xfe;
}

// UtzIsEthernetIA 是否是以太地址
bool UtzIsEthernetIA(uint64_t ia) {
    return ((ia >> 48) & 0xff) == 0xfd;
}

// UtzGenerateFrameIndex 生成帧序号
uint8_t UtzGenerateFrameIndex(void) {
    generateFrameIndex++;
    return generateFrameIndex;
}
