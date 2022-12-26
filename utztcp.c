// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// RFF 27：TZ-STAR自组网系统设计
// Transmission Control Protocol(TCP):传输控制报文协议
// Authors: jdh99 <jdh821@163.com>

#include "utz.h"

// UtzBytesToTcpHeader 字节流转换为传输控制头部
// 返回头部以及头部字节数.字节数为0表示转换失败
int UtzBytesToTcpHeader(uint8_t* data, int dataLen, UtzTcpHeader* header) {
    // 头部数据必须完整
    if (dataLen < sizeof(UtzTcpHeader)) {
        return 0;
    }

    int j = 0;
    header->NextHead = data[j++];
    header->SrcIA = UtzBytesToIA(data + j);
    j += 4;
    header->DstIA = UtzBytesToIA(data + j);
    j += 4;
    header->ControlWord.Value = data[j++];
    header->AgingTime = data[j++];
    return j;
}

// UtzTcpHeaderToBytes 传输控制头部转换为字节流.转换后存储于bytes中
// 返回值是转换后的字节流的长度.返回值是0表示转换失败
int UtzTcpHeaderToBytes(UtzTcpHeader* header, uint8_t* data, int dataSize) {
    if (dataSize < sizeof(UtzTcpHeader)) {
        return 0;
    }

    int j = 0;
    data[j++] = header->NextHead;
    UtzMemcpyReverse(data + j, (uint8_t*)&(header->SrcIA), UTZ_IA_LEN);
    j += UTZ_IA_LEN;
    UtzMemcpyReverse(data + j, (uint8_t*)&(header->DstIA), UTZ_IA_LEN);
    j += UTZ_IA_LEN;
    data[j++] = header->ControlWord.Value;
    data[j++] = header->AgingTime;
    return j;
}

// UtzByteToAgingTime 字节转换为老化时间
// 老化时间单位:s
int UtzByteToAgingTime(uint8_t byte) {
    if (byte <= 0xf) {
        return byte;
    }
    if (byte <= 0x7f) {
        return (byte - 0xf) * 60 + 0xf;
    }
    return (byte - 0x7f) * 900 + (0x7f - 0xf) * 60 + 0xf;
}

// UtzAgingTimeToByte 老化时间转换为字节
// 老化时间单位:s
uint8_t UtzAgingTimeToByte(int agingTime) {
    if (agingTime < 0) {
        return 0;
    }

    int value = 0;
    int delta = agingTime - (0x7f - 0xf) * 60 - 0xf;
    if (delta > 0) {
        value += delta / 900;
        agingTime -= delta;
    }
    delta = agingTime - 0xf;
    if (delta > 0) {
        value += delta / 60;
        agingTime -= delta;
    }
    value += agingTime;
    if (value > 0xff) {
        return 0xff;
    } else {
        return value & 0xff;
    }
}
