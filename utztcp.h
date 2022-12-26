// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 27：TZ-STAR自组网系统设计
// Transmission Control Protocol(TCP):传输控制报文协议
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_TCP_H
#define UTZ_TCP_H

#include "utzcommon.h"

// 版本
#define UTZ_TCP_VERSION_NAME "1.3"

// 命令
// 信标
#define UTZ_TCP_BEACON 0x10
// 应答
#define UTZ_TCP_ACK 0x11
// 请求推送
#define UTZ_TCP_REQUIRE_PUSH 0x12

#pragma pack(1)

// UtzTcpHeaderControlWord 传输控制头部控制字
typedef union {
    struct {
        // 序号
        uint8_t Reserved:4;
        // 服务质量.0: Qos0发送不需要应答 1:Qos1发送需要应答
        bool IsQos1:1;
        // 接收模式控制位.0: 立即发送.1: 应答式发送
        bool IsReceiveAckSend:1;
        // 连续发送控制位
        bool IsContinueSend:1;
        // 应答式发送控制位
        bool IsAckSend:1;
    } Bit;
    uint8_t Value;
} UtzTcpHeaderControlWord;

// UtzTcpHeader 传输控制头部结构
typedef struct {
    uint8_t NextHead;
    // 中继源地址
    uint32_t SrcIA;
    // 中继目的地址
    uint32_t DstIA;
    // 控制字
    UtzTcpHeaderControlWord ControlWord;
    // 老化时间
    uint8_t AgingTime;
} UtzTcpHeader;

// 通信结构体定义
// UtzTcpBeacon 信标
typedef struct {
    // 网络地址
    uint32_t PanIA;
    // 父节点地址
    uint32_t ParentIA;
    // 多跳数
    uint8_t Hops;
    // 开销值
    uint8_t Cost;
} UtzTcpBeacon;

// UtzTcpAck 应答
typedef struct {
    // 发送帧中的帧序号
    uint8_t Index;
    // 发送帧的源地址
    uint32_t IA;
} UtzTcpAck;

// UtzTcpRequirePush 请求推送
typedef struct {
    // 上次推送序号
    uint8_t LastPushIndex;
    // 上次推送源地址
    uint32_t LastPushSrcIA;
} UtzTcpRequirePush;

#pragma pack()

// UtzBytesToTcpHeader 字节流转换为传输控制头部
// 返回头部以及头部字节数.字节数为0表示转换失败
int UtzBytesToTcpHeader(uint8_t* data, int dataLen, UtzTcpHeader* header);

// UtzTcpHeaderToBytes 传输控制头部转换为字节流.转换后存储于bytes中
// 返回值是转换后的字节流的长度.返回值是0表示转换失败
int UtzTcpHeaderToBytes(UtzTcpHeader* header, uint8_t* data, int dataSize);

// UtzByteToAgingTime 字节转换为老化时间
// 老化时间单位:s
int UtzByteToAgingTime(uint8_t byte);

// UtzAgingTimeToByte 老化时间转换为字节
// 老化时间单位:s
uint8_t UtzAgingTimeToByte(int agingTime);

#endif
