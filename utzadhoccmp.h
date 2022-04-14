// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 27：TZ-STAR自组网系统设计
// Ad Hoc Newwork Control Message Protocol(ADHOCCMP):自组网控制报文协议
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_ADHOCCHEADER_H
#define UTZ_ADHOCCHEADER_H

#include "utzcommon.h"

// 版本
#define UTZ_ADHOCCMP_VERSION_NAME "1.2"

// 自组网控制头部长度
#define HEADER_ADHOCC_LEN 15

// 命令
// 信标
#define UTZ_ADHOCCMP_BEACON 0x10
// 应答
#define UTZ_ADHOCCMP_ACK 0x11
// 请求推送
#define UTZ_ADHOCCMP_REQUIRE_PUSH 0x12

#pragma pack(1)

// UtzAdhoccHeaderControlWord 自组网控制头部控制字
typedef union {
    struct {
        // 序号
        uint8_t Index:4;
        // 服务质量.0: Qos0发送不需要应答 1:Qos1发送需要应答
        bool IsQos1:1;
        // 接收模式控制位.0: 立即发送.1: 应答式发送
        bool IsReceiveAckSend:1;
        // 连续发送控制位
        bool IsContinueSend:1;
        // 应答式发送控制位
        bool IsAckSend:1;
    } bit;
    uint8_t value;
} UtzAdhoccHeaderControlWord;

// UtzAdhoccHeader 自组网控制头部结构
typedef struct {
    uint8_t NextHead;
    // 控制字
    UtzAdhoccHeaderControlWord ControlWord;
    // 网络号
    uint32_t PanIA;
    // 中继源地址
    uint32_t SrcRelayIA;
    // 中继目的地址
    uint32_t DstRelayIA;
    // 老化时间
    uint8_t AgingTime;
} UtzAdhoccHeader;

// 通信结构体定义
// UtzAdhoccmpBeacon 信标
typedef struct {
    // 父节点地址
    uint32_t ParentIA;
    // 多跳数
    uint8_t Hops;
} UtzAdhoccmpBeacon;

// UtzAdhoccmpAck 应答
typedef struct {
    // 发送帧种的帧序号
    uint8_t Index;
} UtzAdhoccmpAck;

// UtzAdhoccmpRequirePush 请求推送
typedef struct {
    // 上次推送序号
    uint8_t LastPushIndex;
    // 上次推送源地址
    uint32_t LastPushSrcIA;
} UtzAdhoccmpRequirePush;

#pragma pack()

// UtzBytesToAdhoccHeader 字节流转换为自组网控制头部
// 返回头部以及头部字节数.头部为nil或者字节数为0表示转换失败
int UtzBytesToAdhoccHeader(uint8_t* data, int dataLen, UtzAdhoccHeader* header);

// UtzADHOCCHeaderToBytes 自组网控制头部转换为字节流.转换后存储于bytes中
// 返回值是转换后的字节流的长度.返回值是0表示转换失败
int UtzAdhoccHeaderToBytes(UtzAdhoccHeader* header, uint8_t* data, int dataSize);

// UtzGetAdhoccIndex 获取自组网帧序号
uint8_t UtzGetAdhoccIndex(void);

// UtzByteToAgingTime 字节转换为老化时间
// 老化时间单位:s
int UtzByteToAgingTime(uint8_t byte);

// UtzAgingTimeToByte 老化时间转换为字节
// 老化时间单位:s
uint8_t UtzAgingTimeToByte(int agingTime);

#endif
