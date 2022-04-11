// Copyright 2021-2022 The jdh99 Authors. All rights reserved.
// RFF 4：Control Message Protocol(CMP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_CMP_H
#define UTZ_CMP_H

#include <stdint.h>

// 版本
#define UTZ_CMP_VERSION_NAME "1.2"

// 消息类型
// 申请从机
#define UTZ_CMP_APPLY_SLAVE 0x25
// 连接父路由
#define UTZ_CMP_CONNECT_PARENT 0x26

#pragma pack(1)

// 通信结构体定义
// UtzCmpReqApplySlave 申请从机帧请求
typedef struct {
    // 已分配的从机地址
    uint32_t AssignedSlaveIA;
} UtzCmpReqApplySlave;

// UtzCmpAckApplySlave 申请从机帧应答
typedef struct {
    // 结果
    uint8_t Result;
    // 从机地址
    uint32_t SlaveIA;
    // 从机的IP地址
    uint32_t SlaveIP;
    // 从机的端口号
    uint16_t SlavePort;
    // 从机的开销值
    uint8_t SlaveCost;
} UtzCmpAckApplySlave;

// 结果
// 成功
#define UTZ_CMP_APPLY_SLAVE_RESULT_OK 0x0
// 失败,其他
#define UTZ_CMP_APPLY_SLAVE_RESULT_OTHER 0x1
// 失败,无权限连接
#define UTZ_CMP_APPLY_SLAVE_RESULT_NO_PERMISSION 0x2
// 失败,无从机
#define UTZ_CMP_APPLY_SLAVE_RESULT_NO_SLAVE 0x3

// UtzCmpAckApplySlave 连接父路由应答
typedef struct {
    // 结果
    uint8_t Result;
    // 开销值
    uint8_t Cost;
} UtzCmpAckConnectParent;

// 结果
// 成功
#define UTZ_CMP_CONNECT_PARENT_RESULT_OK 0x0
// 失败,其他
#define UTZ_CMP_CONNECT_PARENT_RESULT_OTHER 0x1
// 失败,本机不是路由
#define UTZ_CMP_CONNECT_PARENT_RESULT_NOT_ROUTER 0x2
// 失败,无权限连接
#define UTZ_CMP_CONNECT_PARENT_RESULT_NO_PERSSION 0x3

#pragma pack()

#endif
