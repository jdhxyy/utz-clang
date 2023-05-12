// Copyright 2022-2022 The jdh99 Authors. All rights reserved.
// RFF 8：Device Upgrade Protocol(DUP)
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_DUP_H
#define UTZ_DUP_H

#include <stdint.h>

// 协议版本
#define UTZ_DUP_VERSION_NAME "1.3"

// 命令字
// 读取版本信息
#define UTZ_DUP_READ_VERSION 0x10
// 开始升级
#define UTZ_DUP_START 0x11
// 停止升级
#define UTZ_DUP_STOP 0x12
// 读取升级文件信息
#define UTZ_DUP_READ_FILE_INFO 0x13
// 读取升级文件数据
#define UTZ_DUP_READ_FILE_DATA 0x14

#pragma pack(1)

// 通信结构体定义
// UtzDupAckReadVersion 读取版本信息应答
typedef struct {
    // 设备类型
    uint16_t DeviceType;
    // 版本号
    uint8_t Version;
    // 升级文件版本号
    uint8_t UpgradeFileVersion;
    // 升级进度.取值:0-100
    uint8_t UpgradeProgress;
} UtzDupAckReadVersion;

// UtzDupReqStart 开始升级请求
typedef struct {
    // 设备类型
    uint16_t DeviceType;
    // 升级文件版本号
    uint8_t UpgradeFileVersion;
} UtzDupReqStart;

// UtzDupAckStart 开始升级应答
typedef struct {
    uint8_t Result;
} UtzDupAckStart;

// 结果
// 成功
#define UTZ_DUP_START_RESULT_OK 0x0
// 失败.其他
#define UTZ_DUP_START_RESULT_OTHER 0x1
// 失败.设备类型不匹配
#define UTZ_DUP_START_RESULT_WRONG_DEVICE_TYPE 0x2
// 失败.软件版本号相同
#define UTZ_DUP_START_RESULT_SAME_VERSION 0x3

// UtzDupReqReadUpgradeFileInfo 读取升级文件信息请求
typedef struct {
    // 设备类型
    uint16_t DeviceType;
    // 当前版本号
    uint8_t Version;
} UtzDupReqReadUpgradeFileInfo;

// UtzDupAckReadUpgradeFileInfo 读取升级文件信息应答
typedef struct {
    // 文件设备类型
    uint16_t FileDeviceType;
    // 文件软件版本
    uint8_t FileVersion;
    // 文件总字节数
    uint32_t FileTotalBytes;
    // 校验方式.0:MD5,1:CRC16,2:CRC32
    uint8_t CheckType;
    // 文件校验码
    uint8_t FileCheckSum[16];
} UtzDupAckReadUpgradeFileInfo;

// 校验方式
#define UTZ_DUP_CHECK_TYPE_MD5 0
#define UTZ_DUP_CHECK_TYPE_CRC16 1
#define UTZ_DUP_CHECK_TYPE_CRC32 2

// UtzDupReqReadUpgradeFileData 读取升级文件数据请求
typedef struct {
    // 设备类型
    uint16_t DeviceType;
    // 版本号
    uint8_t Version;
    // 升级文件版本号
    uint8_t UpgradeFileVersion;
    // 偏移地址
    uint32_t Offset;
    // 升级数据最大字节数
    uint16_t DataLenMax;
} UtzDupReqReadUpgradeFileData;

// UtzDupAckReadUpgradeFileData 读取升级文件数据应答
typedef struct {
    // 文件设备类型
    uint16_t FileDeviceType;
    // 文件软件版本
    uint8_t FileVersion;
    // 偏移地址
    uint32_t Offset;
    // 数据长度
    uint16_t DataLen;
    // 数据
    uint8_t Data[];
} UtzDupAckReadUpgradeFileData;

#pragma pack()

#endif
