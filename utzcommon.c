// Copyright 2021-2021 The jdh99 Authors. All rights reserved.
// 通用模块
// Authors: jdh99 <jdh821@163.com>

#include "utzcommon.h"
#include "utznlp.h"
#include "tzbox.h"

#include "tzmalloc.h"
#include "lagan.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// 内存管理id
static int mid = -1;

// UtzGetMid 读取内存id
int UtzGetMid(void) {
    if (mid == -1) {
        mid = TZMallocRegister(0, UTZ_TAG, UTZ_MALLOC_SIZE);
        if (mid == -1) {
            LE(UTZ_TAG, "malloc register failed!");
        }
    }
    return mid;
}

// BytesToIA 从字节流中取出IA地址.字节流是大端
// 字节流长度必须保证大于IA_LEN
uint32_t UtzBytesToIA(uint8_t* data) {
    uint32_t ia = 0;
    UtzMemcpyReverse((uint8_t*)&ia, data, UTZ_IA_LEN);
    return ia;
}

// IAToBytes 将IA地址转换为字节流.字节流是大端
void UtzIAToBytes(uint32_t ia, uint8_t* data) {
    UtzMemcpyReverse(data, (uint8_t*)&ia, UTZ_IA_LEN);
}

// UtzMemcpyReverse 翻转复制.比如src为小端存储.可以转换为大端存储在dst中
void UtzMemcpyReverse(uint8_t* dst, uint8_t* src, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[size - 1 - i];
    }
}
