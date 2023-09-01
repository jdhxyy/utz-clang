// Copyright 2021-2023 The jdh99 Authors. All rights reserved.
// RFF 4：Control Message Protocol(CMP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_CMP_H
#define UTZ_CMP_H

#include <stdint.h>

// 版本
#define UTZ_CMP_VERSION_NAME "1.2"

#pragma pack(1)

// 复位设备
#define UTZ_CMP_RESET 0x22

// 设置本机网络参数
#define UTZ_CMP_SET_NET_PARAM 0x23

// UtzCmpReqSetNet 请求
typedef struct {
    // DHCP开关.0:关.1:开
    uint8_t Dhcp;
    uint32_t IP;
    uint32_t Mask;
    uint32_t Gateway;
    uint16_t Port;
    uint32_t Dns;
} UtzCmpReqSetNetParam;

// 读取本机网络参数
#define UTZ_CMP_GET_NET_PARAM 0x24

// UtzCmpAckSetNetParam 应答
typedef struct {
    // DHCP开关.0:关.1:开
    uint8_t Dhcp;
    uint32_t IP;
    uint32_t Mask;
    uint32_t Gateway;
    uint16_t Port;
    uint32_t Dns;
} UtzCmpAckGetNetParam;

// 申请从机
#define UTZ_CMP_APPLY_SLAVE 0x25

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

// 连接父路由
#define UTZ_CMP_CONNECT_PARENT 0x26

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

// 配置IA地址
#define UTZ_CMP_SET_IA 0x2C

// 请求
typedef struct {
    uint32_t IA;
} UtzCmpReqSetIA;

// 读取IA地址
#define UTZ_CMP_GET_IA 0x2D

// 应答
typedef struct {
    uint32_t IA;
} UtzCmpAckGetIA;

// 配置设备类型
#define UTZ_SET_DEVICE_TYPE 0x2E

// 请求
typedef struct {
    uint16_t DeviceType;
} UtzCmpReqSetDeviceType;

// 读取设备类型
#define UTZ_GET_DEVICE_TYPE 0x2F

// 应答
typedef struct {
    uint16_t DeviceType;
} UtzCmpAckGetDeviceType;

// 读取板卡类型
#define UTZ_CMP_GET_BOARD_TYPE 0x38

typedef struct {
    char BoardType[15];
} UtzCmpReqGetBoardType;

// 读取在线状态
#define UTZ_CMP_READ_ONLINE_STATE 0x3B

// UtzCmpReadOnlineState 读取在线状态应答
typedef struct {
    // 在线类型
    uint8_t OnlineType;
    // 父路由全球单播地址
    uint32_t IA;
} UtzCmpAckReadOnlineState;

// 在线类型
#define UTZ_CMP_ONLINE_TYPE_OFFLINE 0
#define UTZ_CMP_ONLINE_TYPE_ETH 1
#define UTZ_CMP_ONLINE_TYPE_WIFI 2
#define UTZ_CMP_ONLINE_TYPE_GPRS 3
#define UTZ_CMP_ONLINE_TYPE_RADIO 4
#define UTZ_CMP_ONLINE_TYPE_OTHER 5

// 推送在线状态
#define UTZ_CMP_PUSH_ONLINE_STATE 0x3C

// 推送在线状态请求
typedef struct {
    // 在线类型
    uint8_t OnlineType;
    // 父路由全球单播地址
    uint32_t IA;
} UtzCmpReqPushOnlineState;

// 配置WIFI参数
#define UTZ_CMP_SET_WIFI_PARAM 0x3F

// 配置wifi参数
typedef struct {
    // 序号.从0开始
    uint8_t Index;
    // 标志
    uint8_t Flag;
    // WIFI名称字节数
    uint8_t SsidLen;
    // WIFI密码字节数
    uint8_t PwdLen;
    // 数据
    uint8_t Data[];
} UtzCmpReqSetWifiParam;

typedef struct {
    // 结果
    uint8_t Result;
} UtzCmpAckSetWifiParam;

// 失败结果.成功为0
// 失败,其他
#define UTZ_CMP_SET_WIFI_PARAM_RESULT_OTHER 0x1
// 失败,已达配置上限
#define UTZ_CMP_SET_WIFI_PARAM_RESULT_TOO_MANY 0x2

// 读取WIFI参数
#define UTZ_CMP_GET_WIFI_PARAM 0x40

// 读取WIFI参数
typedef struct {
    // 序号.从0开始
    uint8_t Index;
} UtzCmpReqGetWifiParam;

typedef struct {
    // 结果
    uint8_t Result;

    // 序号.从0开始
    uint8_t Index;
    // 标志
    uint8_t Flag;
    // WIFI名称字节数
    uint8_t SsidLen;
    // WIFI密码字节数
    uint8_t PwdLen;
    // 数据
    uint8_t Data[];
} UtzCmpAckGetWifiParam;

// 失败结果.成功为0
// 失败,其他
#define UTZ_CMP_GET_WIFI_PARAM_RESULT_OTHER 0x1
// 失败,无此序号的WIFI热点
#define UTZ_CMP_GET_WIFI_PARAM_RESULT_NOT_EXIST 0x2

// 设置核心网参数
#define UTZ_CMP_SET_CORE_PARAM 0x41

typedef struct {
    // IA
    uint32_t IA;
    // 端口
    uint16_t Port;
    // IP
    uint32_t IP;
    // 域名长度
    uint8_t DomainNameLen;
    // 域名
    char DomainName[];
} UtzCmpReqSetCoreParam;

// 读取核心网参数
#define UTZ_CMP_GET_CORE_PARAM 0x42

typedef struct {
    // IA
    uint32_t IA;
    // 端口
    uint16_t Port;
    // IP
    uint32_t IP;
    // 域名长度
    uint8_t DomainNameLen;
    // 域名
    char DomainName[];
} UtzCmpAckGetCoreParam;

// 读取业务服务器地址
#define UTZ_CMP_GET_SERVER_IA 0x44

typedef struct {
    uint32_t IA;
} UtzCmpAckGetServerIA;

// 读取统计
#define UTZ_CMP_GET_STATISTICS 0x49

typedef struct {
    // 统计组序号.序号从0开始
    uint8_t Index;
} UtzCmpReqGetStatistics;

typedef struct {
    // 设备类型
    uint16_t DeviceType;
    // 软件版本
    uint8_t Version;
    // 统计组序号
    uint8_t Index;
    // 统计数据条目数
    uint8_t ItemNum;
    // 统计数据
    uint32_t Items[];
} UtzCmpAckGetStatistics;

// 清除统计
#define UTZ_CMP_CLEAR_STATISTICS 0x4A

// 推送统计
#define UTZ_CMP_PUSH_STATISTICS 0x4B

typedef struct {
    // 设备类型
    uint16_t DeviceType;
    // 软件版本
    uint8_t Version;
    // 统计组序号
    uint8_t Index;
    // 统计数据条目数
    uint8_t ItemNum;
    // 统计数据
    uint32_t Items[];
} UtzCmpReqPushStatistics;

#pragma pack()

#endif
