// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// 通用模块
// Authors: jdh99 <jdh821@163.com>

#include "utzcommon.h"
#include "utznlv1.h"

// BytesToIA 从字节流中取出IA地址.字节流是大端
// 字节流长度必须保证大于IA_LEN
uint64_t UtzBytesToIA(uint8_t* data) {
    uint64_t ia = 0;
    UtzMemcpyReverse((uint8_t*)&ia, data, UTZ_IA_LEN);
    return ia;
}

// IAToBytes 将IA地址转换为字节流.字节流是大端
void UtzIAToBytes(uint64_t ia, uint8_t* data) {
    UtzMemcpyReverse(data, (uint8_t*)&ia, UTZ_IA_LEN);
}

// UtzMemcpyReverse 翻转复制.比如src为小端存储.可以转换为大端存储在dst中
void UtzMemcpyReverse(uint8_t* dst, uint8_t* src, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[size - 1 - i];
    }
}

// GetNextHeadLen 得到下一头部字节数
// 注意:下一头部不能是正文头部
// bytes是帧的完整字节流,size是帧的总字节数.offset是下一头部的偏移量
// 返回值是下一头部字节数.如果是0表示解析失败
int UtzGetNextHeadLen(uint8_t* bytes, int size, int offset) {
    if (size < offset+2) {
        return 0;
    }
    int nextHeadLen = bytes[offset+1] + 2;
    if (size < offset+nextHeadLen) {
        return 0;
    }
    return nextHeadLen;
}

// UtzHtons 2字节主机序转换为网络序
uint16_t UtzHtons(uint16_t n) {
    return (uint16_t)(((n & 0xff) << 8) | ((n & 0xff00) >> 8));
}

// UtzNtohs 2字节网络序转换为主机序
uint16_t UtzNtohs(uint16_t n) {
    return UtzHtons(n);
}

// UtzHtonl 4字节主机序转换为网络序
uint32_t UtzHtonl(uint32_t n) {
    return ((n & 0xff) << 24) |
        ((n & 0xff00) << 8) |
        ((n & 0xff0000UL) >> 8) |
        ((n & 0xff000000UL) >> 24);
}

// UtzNtohl 4字节网络序转换为主机序
uint32_t UtzNtohl(uint32_t n) {
    return UtzHtonl(n);
}

// UtzHtonll 8字节主机序转换为网络序
uint64_t UtzHtonll(uint64_t n) {
    return ((n & 0xff) << 56) |
        ((n & 0xff00) << 40) |
        ((n & 0xff0000) << 24) |
        ((n & 0xff000000) << 8) |
        ((n & 0xff00000000ULL) >> 8) |
        ((n & 0xff0000000000ULL) >> 24) |
        ((n & 0xff000000000000ULL) >> 40) |
        ((n & 0xff00000000000000ULL) >> 56);
}

// UtzNtohll 8字节网络序转换为主机序
uint64_t UtzNtohll(uint64_t n) {
    return UtzHtonll(n);
}
