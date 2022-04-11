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
uint32_t UtzBytesToIA(uint8_t* data);

// IAToBytes 将IA地址转换为字节流.字节流是大端
void UtzIAToBytes(uint32_t ia, uint8_t* data);

// UtzMemcpyReverse 翻转复制.比如src为小端存储.可以转换为大端存储在dst中
void UtzMemcpyReverse(uint8_t* dst, uint8_t* src, int size);

#endif
