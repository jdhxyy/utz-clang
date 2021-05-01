// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// 通用模块
// Authors: jdh99 <jdh821@163.com>

#ifndef UTZ_COMMON_H
#define UTZ_COMMON_H

#include <stdint.h>
#include <stdbool.h>

#define UTZ_TAG "utz"
#define UTZ_MALLOC_SIZE 4096

// UtzGetMid 读取内存id
int UtzGetMid(void);

// BytesToIA 从字节流中取出IA地址.字节流是大端
// 字节流长度必须保证大于IA_LEN
uint64_t UtzBytesToIA(uint8_t* data);

// IAToBytes 将IA地址转换为字节流.字节流是大端
void UtzIAToBytes(uint64_t ia, uint8_t* data);

// UtzMemcpyReverse 翻转复制.比如src为小端存储.可以转换为大端存储在dst中
void UtzMemcpyReverse(uint8_t* dst, uint8_t* src, int size);

// GetNextHeadLen 得到下一头部字节数
// 注意:下一头部不能是正文头部
// bytes是帧的完整字节流,size是帧的总字节数.offset是下一头部的偏移量
// 返回值是下一头部字节数.如果是0表示解析失败
int UtzGetNextHeadLen(uint8_t* bytes, int size, int offset);

// UtzIAStrToHex IA地址字符串转整型
bool UtzIAStrToHex(const char* src, uint64_t* dst);

// UtzIAToStr IA地址转字符串形式
// type：0：标准输出；1：前导0压缩；2：全0压缩输出
bool UtzIAHexToStr(uint64_t src, char* dst, int type);

#endif
