// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 1：Network Layer Version 1(NLv1)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_NLV1_H
#define UTZ_NLV1_H

#include <stdint.h>
#include <stdbool.h>

// 协议版本
#define UTZ_NLV1_VERSION_NAME "1.1"

// 标准头部长度
#define UTZ_NLV1_HEAD_LEN 22

// 特殊地址
// 未指定地址
#define UTZ_IA_INVALID 0x0
// 回环地址
#define UTZ_IA_LOOPBACK 0x1
// 广播地址
#define UTZ_IA_BROADCAST 0xFFFFFFFFFFFFFFFF
// 广播短地址
#define UTZ_SHORT_IA_BROADCAST 0xFFFFFFFF
// 协调器短地址
#define UTZ_SHORT_IA_COORDINATOR 0x10

// IA地址字节数
#define UTZ_IA_LEN 8
#define UTZ_SHORT_IA_LEN 4
#define UTZ_TINY_IA_LEN 2

// 无效跳数限制
#define UTZ_HOPS_LIMIT_INVALID 255

// 4字节短地址前缀
#define UTZ_SHORT_IA_PREFIX 0xFE00000000000000
// 2字节短地址前缀
#define UTZ_TINY_IA_PREFIX 0xFE00000100000000
// 4字节短地址掩码
#define UTZ_SHORT_IA_MASK 0xFFFFFFFF
// 2字节短地址掩码
#define UTZ_TINY_IA_MASK 0xFFFF

// MTU
#define UTZ_NLV1_MTU 1280

#pragma pack(1)

// UtzStandardHeader 标准头部
typedef struct {    
    uint8_t Version;
    uint8_t FrameIndex;
    uint16_t PayloadLen;
    uint8_t NextHead;
    uint8_t HopsLimit;
    uint64_t SrcIA;
    uint64_t DstIA;
} UtzStandardHeader;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
#pragma pack()

// 内存管理id
extern int UtzMid;

// UtzLoad 模块载入
void UtzLoad(int mid);

// UtzBytesToStandardHeader 字节流转换为标准头部.字节流是大端
// 字节流data必须大于标准头部长度
// 返回头部以及头部字节数.头部为nil或者字节数为0表示转换失败
int UtzBytesToStandardHeader(uint8_t* data, int dataLen, UtzStandardHeader* header);

// UtzStandardHeaderToBytes 标准头部转换为字节流.字节流是大端
// 字节流data必须大于标准头部长度
// 返回值是转换后的字节流的长度.返回值是0表示转换失败
int UtzStandardHeaderToBytes(UtzStandardHeader* header, uint8_t* data, int dataSize);

// UtzIsGlobalIA 是否是全球单播地址
bool UtzIsGlobalIA(uint64_t ia);

// UtzIsUniqueLocalIA 是否是唯一本地地址
bool UtzIsUniqueLocalIA(uint64_t ia);

// UtzIsEthernetIA 是否是以太地址
bool UtzIsEthernetIA(uint64_t ia);

// UtzGenerateFrameIndex 生成帧序号
uint8_t UtzGenerateFrameIndex(void);

#endif
