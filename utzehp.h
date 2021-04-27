// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 2：Extension Header Protocol(EHP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_EHP_H
#define UTZ_EHP_H

#include "tztype.h"

// 版本
#define UTZ_EHP_VERSION_NAME "1.1"

// 扩展头部
// 逐跳可选项头部
#define UTZ_HEADER_HOP_BY_HOP_OPTIONS 0x0
// 路由头部
#define UTZ_HEADER_ROUTE 0x1
// 分片头部
#define UTZ_HEADER_FRAGMENT 0x2
// 加密头部
#define UTZ_HEADER_ENCRYPTION 0x3
// FLP
#define UTZ_HEADER_FLP 0x4
// CMP
#define UTZ_HEADER_CMP 0x5
// WTS
#define UTZ_HEADER_WTS 0x6
// DUP
#define UTZ_HEADER_DUP 0x7
// SFTPA
#define UTZ_HEADER_SFTPA 0x8
// SFTPB
#define UTZ_HEADER_SFTPB 0x9
// STCP
#define UTZ_HEADER_STCP 0xA
// ITCP
#define UTZ_HEADER_ITCP 0xB
// DAP
#define UTZ_HEADER_DAP 0xC
// A类RSSI头部
#define UTZ_HEADER_RSSI_A 0xD
// B类RSSI头部
#define UTZ_HEADER_RSSI_B 0xE
// A类发送控制头部
#define UTZ_HEADER_RADIO_TX_CONTROL_A 0xF
// 125K激发RSSI头部
#define UTZ_HEADER_EXCITER_RSSI 0x10
// A类TOF定位头部
#define UTZ_HEADER_TOF_LOCATION_A 0x11
// A类DW1000接收头部
#define UTZ_HEADER_DW1000_RX_A 0x12
// A类DW1000发送完成头部
#define UTZ_HEADER_DW1000_TX_END_A 0x13
// A类坐标头部
#define UTZ_HEADER_COORDINATE_A 0x14
// 时间戳头部
#define UTZ_HEADER_TIMESTAMP 0x15
// 代理头部
#define UTZ_HEADER_AGENT 0x16
// 自组网控制头部
#define UTZ_HEADER_ADHOCC 0x17
// 压缩头部复合帧
#define UTZ_HEADER_COMPRESS_COMPLEX 0x18
// 标准头部复合帧
#define UTZ_HEADER_STANDARD_COMPLEX 0x19
// 全球单播地址分配服务器访问协议
#define UTZ_HEADER_GUAAP 0x1A
// 固定地址解析服务器访问协议
// 订阅服务器访问协议
// 简单安全头部
#define UTZ_HEADER_SIMPLE_SECURITY 0x1D
// 定长传输控制头部
#define UTZ_HEADER_FIXED_LENGTH_TRANSFER_CONTROL 0x1E
// 中继头部
#define UTZ_HEADER_REPEAT 0x1F
// 子分片头部
#define UTZ_HEADER_SUB_FRAGMENT 0x20
// 系统日志协议
#define UTZ_HEADER_SLP 0x22
// 设备间通信协议
#define UTZ_HEADER_DCOM 0x23
// 物联网终端协议
#define UTZ_HEADER_ISH 0x24

#pragma pack(1)

// RouteHeader 路由头部结构
typedef struct {    
    uint8_t NextHead;
    // 剩余路由数
    uint8_t RouteNum;
    // 是否严格源路由
    bool IsStrict;
    // 路由地址列表
    uint64_t IAList[];
} UtzRouteHeader;

// SimpleSecurityHeader 简单安全头部结构
typedef struct {
	uint8_t NextHead;
    uint8_t PwdLen;
    uint8_t Pwd[];
} UtzSimpleSecurityHeader;

#pragma pack()

// UtzBytesToRouteHeader 字节流转换为路由头部
// offset是转换后字节流新的偏移地址.如果为0表示转换失败.不需要知道可填写NULL
// 返回头部指针,为NULL表示转换失败.转换成功要注意释放指针
UtzRouteHeader* UtzBytesToRouteHeader(uint8_t* data, int dataLen, int* offset);

// UtzRouteHeaderToBytes 路由头部转换为字节流
// 返回的是字节流.如果是NULL表示转换失败.转换成功要注意释放指针
TZBufferDynamic* UtzRouteHeaderToBytes(UtzRouteHeader* header);

// UtzIsPayloadHeader 是否载荷头部
bool UtzIsPayloadHeader(uint8_t head);

// UtzBytesToSimpleSecurityHeader 字节流转换为简单安全头部
// bytesNum是返回的转换头部的字节流字节数.如果为0表示转换失败
// 返回头部指针,为NULL表示转换失败.转换成功要注意释放指针
UtzSimpleSecurityHeader* UtzBytesToSimpleSecurityHeader(uint8_t* data, int dataLen, int* bytesNum);

// SimpleSecurityHeaderToBytes 简单安全头部转换为字节流
// 返回的是字节数.如果为0表示转换失败
int UtzSimpleSecurityHeaderToBytes(UtzSimpleSecurityHeader* header, uint8_t* data, int dataSize);

#endif
