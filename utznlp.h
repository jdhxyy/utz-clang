// Copyright 2021-2022 The jdh99 Authors. All rights reserved.
// RFF 1：Network Layer Protocol(NLP)设计
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_NLV1_H
#define UTZ_NLV1_H

#include <stdint.h>
#include <stdbool.h>

// 协议版本
#define UTZ_NLP_VERSION_NAME "2.1"

// 标准头部长度
#define UTZ_NLP_HEAD_LEN 12

// 特殊地址
// 未指定地址
#define UTZ_IA_INVALID 0x0
// 回环地址
#define UTZ_IA_LOOPBACK 0x1
// 广播地址
#define UTZ_IA_BROADCAST 0xFFFFFFFF
// 广播短地址
#define UTZ_SHORT_IA_BROADCAST 0xFFFFFFFF

// IA地址字节数
#define UTZ_IA_LEN 4

// MTU
#define UTZ_NLP_MTU 1280

#pragma pack(1)

// UtzStandardHeader 标准头部
typedef struct {
    uint32_t SrcIA;
    uint32_t DstIA;
    uint8_t FrameIndex;
    uint8_t NextHead;
    uint16_t PayloadLen;
} UtzStandardHeader;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
#pragma pack()

// UtzBytesToStandardHeader 字节流转换为标准头部.字节流是大端
// 字节流data必须大于标准头部长度
// 返回头部以及头部字节数.字节数为0表示转换失败
int UtzBytesToStandardHeader(uint8_t* data, int dataLen, UtzStandardHeader* header);

// UtzStandardHeaderToBytes 标准头部转换为字节流.字节流是大端
// 字节流data必须大于标准头部长度
// 返回值是转换后的字节流的长度.返回值是0表示转换失败
int UtzStandardHeaderToBytes(UtzStandardHeader* header, uint8_t* data, int dataSize);

// UtzIsGlobalIA 是否是全球单播地址
bool UtzIsGlobalIA(uint32_t ia);

// UtzIsUniqueLocalIA 是否是唯一本地地址
bool UtzIsUniqueLocalIA(uint32_t ia);

// IsMulticastIA 是否是组播地址
bool UtzIsMulticastIA(uint32_t ia);

// UtzIsAckCmd 是否应答命令
bool UtzIsAckCmd(uint8_t cmd);

// UtzGetAckCmd 得到应答命令字
uint8_t UtzGetAckCmd(uint8_t cmd);

// UtzGetReqCmd 得到请求命令字
uint8_t UtzGetReqCmd(uint8_t cmd);

// UtzGetFrameLen 去除尾缀获取真实帧长
// 返回的是帧长.如果返回值是0表示获取失败
int UtzGetFrameLen(uint8_t* data, int dataLen);

// UtzGetFrameIndex 获取帧序号
uint8_t UtzGetFrameIndex(void);

#endif
